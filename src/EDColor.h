/**************************************************************************************************************
* Color Edge Drawing (ED) and Color Edge Drawing Parameter Free (EDPF) source codes.
* Copyright (c) 2017, Cuneyt Akinlar & Cihan Topal
* E-mails of the authors: cuneytakinlar@gmail.com, cihant@anadolu.edu.tr
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.

* By using this library you are implicitly assumed to have accepted all of the above statements,
* and accept to cite the following papers:
*
* [1] C. Topal and C. Akinlar, “Edge Drawing: A Combined Real-Time Edge and Segment Detector,” 
*     Journal of Visual Communication and Image Representation, 23(6), 862-872, doi:10.1016/j.jvcir.2012.05.004 (2012).
*
* [2] C. Akinlar and C. Topal, “EDPF: A Real-time Parameter-free Edge Segment Detector with a False Detection Control,” 
*     International Journal of Pattern Recognition and Artificial Intelligence, 26(1), doi:10.1142/S0218001412550026 (2012).
*
* [3] C. Akinlar, C. Topal, "ColorED: Color Edge and Segment Detection by Edge Drawing (ED),"
*     submitted to the Journal of Visual Communication and Image Representation (2017).
**************************************************************************************************************/
#pragma once
#ifndef _EDColor_
#define _EDColor_

#include <opencv2/opencv.hpp>

// Look up table size for fast color space conversion
#define LUT_SIZE (1024*4096)

// Special defines
#define EDGE_VERTICAL   1
#define EDGE_HORIZONTAL 2
#define EDGE_45         3
#define EDGE_135        4

#define MAX_GRAD_VALUE 128*256
#define EPSILON 1.0
#define MIN_PATH_LEN 10

class EDColor {
public:
    // 构造函数：初始化带有源图像和其他参数的 EDColor 对象
    EDColor(cv::Mat srcImage, int gradThresh = 20, int anchor_thresh = 4, double sigma = 1.5, bool validateSegments = false);
    
    // 返回边缘图像
    cv::Mat getEdgeImage();
    
    // 返回所有段的向量
    std::vector<std::vector<cv::Point>> getSegments();
    
    // 返回段的数量
    int getSegmentNo();
    
    // 返回图像宽度
    int getWidth();
    
    // 返回图像高度
    int getHeight();
    
    // 输入图像
    cv::Mat inputImage;

private:
    // 用于存储 Lab 颜色空间分量
    uchar* L_Img;
    uchar* a_Img;
    uchar* b_Img;

    // 用于存储平滑后的 Lab 颜色空间分量
    uchar* smooth_L;
    uchar* smooth_a;
    uchar* smooth_b;

    // 方向图像和梯度图像
    uchar* dirImg;
    short* gradImg;

    // 边缘图像和边缘图像数据指针
    cv::Mat edgeImage;
    uchar* edgeImg;

    // 输入图像的 RGB 分量指针
    const uchar* blueImg;
    const uchar* greenImg;
    const uchar* redImg;

    // 图像宽度和高度
    int width;
    int height;

    // 用于测试段的参数
    double divForTestSegment;
    double* H;
    int np;
    int segmentNo;

    // 段的向量
    std::vector<std::vector<cv::Point>> segments;

    // 快速颜色空间转换的查找表
    static double LUT1[LUT_SIZE + 1];
    static double LUT2[LUT_SIZE + 1];
    static bool LUT_Initialized;

    // 私有成员函数：快速将 RGB 转换为 Lab 颜色空间
    void MyRGB2LabFast();
    
    // 通过 DiZenzo 算法计算梯度图
    void ComputeGradientMapByDiZenzo();
    
    // 平滑通道
    void smoothChannel(uchar* src, uchar* smooth, double sigma);
    
    // 验证边缘段
    void validateEdgeSegments();
    
    // 测试段
    void testSegment(int i, int index1, int index2);
    
    // 提取新段
    void extractNewSegments();
    
    // 计算概率
    double NFA(double prob, int len);

    // 修复边缘段
    static void fixEdgeSegments(std::vector<std::vector<cv::Point>> map, int noPixels);

    // 初始化 ColorED 库
    static void InitColorEDLib();
};

#endif // !_EDColor_
