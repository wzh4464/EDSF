//
// Created by xiaowuga on 2021/11/24.
//

#ifndef CYLINDERPOSETRACKING_TESTTOOLS_H
#define CYLINDERPOSETRACKING_TESTTOOLS_H

#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief 测试两个二值图像的重叠部分。
 * 
 * @param gt Ground truth 图像，类型为 cv::Mat1b。
 * @param test 测试图像，类型为 cv::Mat1b。
 * @param th 阈值，用于确定重叠区域的比例。
 * @return 如果重叠区域超过阈值，返回 true；否则返回 false。
 */
bool TestOverlap(const cv::Mat1b& gt, const cv::Mat1b& test, float th);

/**
 * @brief 评估两个椭圆集合之间的相似度。
 * 
 * @param ellGt Ground truth 椭圆集合，类型为 std::vector<cv::RotatedRect>。
 * @param ellTest 测试椭圆集合，类型为 std::vector<cv::RotatedRect>。
 * @param th_score 阈值分数，用于评估相似度。
 * @param h 图像的高度。
 * @param w 图像的宽度。
 * @return 包含评估结果的 cv::Vec3f，具体评估标准由实现决定。
 */
cv::Vec3f ell_evaluate(std::vector<cv::RotatedRect>& ellGt,
                       std::vector<cv::RotatedRect>& ellTest, float th_score, int h, int w);

#endif // CYLINDERPOSETRACKING_TESTTOOLS_H
