#include <iostream>
#include <filesystem>
#include "EDLib.h"
#include "CED.h"
#include <opencv2/core/utils/logger.hpp>

namespace fs = std::filesystem;

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    
    std::string imgDir = "/home/zihan/dataset/test-img/";
    std::string outputDir = "/home/zihan/dataset/test-img/EDSF/";

    // 检查图像目录是否存在
    if (!fs::exists(imgDir) || !fs::is_directory(imgDir)) {
        std::cerr << "Error: The input directory does not exist." << std::endl;
        return -1;
    }

    // 确保输出目录存在
    fs::create_directories(outputDir);

    // 遍历目录中的所有图像文件
    for (const auto& entry : fs::directory_iterator(imgDir)) {
        if (entry.is_regular_file()) {
            std::string imgPath = entry.path().string();

            // 仅处理图像文件（根据需要添加更多图像扩展名）
            if (imgPath.ends_with(".jpg") || imgPath.ends_with(".png") || imgPath.ends_with(".jpeg")) {
                std::cout << "Processing: " << imgPath << std::endl;

                // 开始计时
                double start = cv::getTickCount();
                cv::Mat img = cv::imread(imgPath);
                if (img.empty()) {
                    std::cerr << "Error: Could not load image " << imgPath << std::endl;
                    continue;
                }

                CED ced = CED(img);
                ced.run_CED();
                cv::Mat sss = ced.drawEdgeSegments();
                cv::Mat ellMapCluster = ced.drawEllipsesAfterCluster(img);
                // 结束计时
                double time = (cv::getTickCount() - start) / cv::getTickFrequency();

                std::cout << "Time: " << time << "s" << std::endl;

                // 获取文件名（不带路径和扩展名）
                std::string fileName = entry.path().stem().string();

                // 输出检测到的椭圆参数
                std::vector<cv::RotatedRect> ellipses = ced.getEllipsesAfterCluster();
                for (const auto& ellipse : ellipses) {
                    std::cout << "Center: (" << ellipse.center.x << ", " << ellipse.center.y << ")";
                    std::cout << ", Size: (" << ellipse.size.width << ", " << ellipse.size.height << ")";
                    std::cout << ", Angle: " << ellipse.angle << std::endl;
                }

                // 保存结果图像，命名格式为 EDSF_result_xxxx.jpg
                cv::imwrite(outputDir + "EDSF_" + fileName + ".jpg", ellMapCluster);
            }
        }
    }

    std::cout << "All images processed. Results saved in " << outputDir << std::endl;
    return 0;
}
