/**************************************************************************************************************
* Edge Drawing (ED) and Edge Drawing Parameter Free (EDPF) source codes.
* Copyright (C) 2016, Cuneyt Akinlar & Cihan Topal
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
*     Journal of Visual Communication and Image Representation, 23(6), 862-872, DOI: 10.1016/j.jvcir.2012.05.004 (2012).
*
* [2] C. Akinlar and C. Topal, “EDPF: A Real-time Parameter-free Edge Segment Detector with a False Detection Control,” 
*     International Journal of Pattern Recognition and Artificial Intelligence, 26(1), DOI: 10.1142/S0218001412550026 (2012).
**************************************************************************************************************/
#pragma once
#ifndef _ED_
#define _ED_

#include <opencv2/opencv.hpp>
#include "EDColor.h"

/// Special defines
#define EDGE_VERTICAL   1
#define EDGE_HORIZONTAL 2

#define ANCHOR_PIXEL  254
#define EDGE_PIXEL    255

#define LEFT  1
#define RIGHT 2
#define UP    3
#define DOWN  4

enum GradientOperator { PREWITT_OPERATOR = 101, SOBEL_OPERATOR = 102, SCHARR_OPERATOR = 103, LSD_OPERATOR = 104 };

struct StackNode {
    int r, c;   // starting pixel
    int parent; // parent chain (-1 if no parent)
    int dir;    // direction where you are supposed to go
};

// Used during Edge Linking
struct Chain {
    int dir;                   // Direction of the chain
    int len;                   // # of pixels in the chain
    int parent;                // Parent of this node (-1 if no parent)
    int children[2];           // Children of this node (-1 if no children)
    cv::Point* pixels;         // Pointer to the beginning of the pixels array
};

class ED {
public:
    // 构造函数：初始化带有源图像和其他参数的 ED 对象
    ED(cv::Mat _srcImage, GradientOperator _op = PREWITT_OPERATOR, int _gradThresh = 20, int _anchorThresh = 0, int _scanInterval = 1, int _minPathLen = 20, double _sigma = 1.0, bool _sumFlag = true);
    // 拷贝构造函数
    ED(const ED& cpyObj);
    // 构造函数：初始化带有梯度图像和方向图像的 ED 对象
    ED(short* gradImg, uchar* dirImg, int _width, int _height, int _gradThresh, int _anchorThresh, int _scanInterval = 1, int _minPathLen = 10, bool selectStableAnchors = true);
    // 从 EDColor 对象初始化 ED 对象
    ED(EDColor& cpyObj);
    // 默认构造函数
    ED();

    // 返回边缘图像
    cv::Mat getEdgeImage();
    // 返回锚点图像
    cv::Mat getAnchorImage();
    // 返回平滑后的图像
    cv::Mat getSmoothImage();
    // 返回梯度图像
    cv::Mat getGradImage();

    // 返回段的数量
    int getSegmentNo();
    // 返回锚点的数量
    int getAnchorNo();

    // 返回锚点的向量
    std::vector<cv::Point> getAnchorPoints();
    // 返回所有段的向量
    std::vector<std::vector<cv::Point>> getSegments();
    // 返回排序后的段的向量
    std::vector<std::vector<cv::Point>> getSortedSegments();

    // 根据给定的段列表绘制特定的段
    cv::Mat drawParticularSegments(std::vector<int> list);

protected:
    int width;  // 源图像的宽度
    int height; // 源图像的高度
    uchar* srcImg; // 源图像数据的指针
    std::vector<std::vector<cv::Point>> segmentPoints; // 段的点的二维数组
    double sigma; // 高斯模糊的 sigma 值
    cv::Mat smoothImage; // 平滑后的图像
    uchar* edgeImg; // 边缘图像数据的指针
    uchar* smoothImg; // 平滑图像数据的指针
    int segmentNos; // 段的数量
    int minPathLen; // 最小路径长度
    cv::Mat srcImage; // 源图像

public:
    // 计算梯度图像
    void ComputeGradient();
    // 计算锚点
    void ComputeAnchorPoints();
    // 使用排序后的锚点连接锚点
    void JoinAnchorPointsUsingSortedAnchors();
    // 根据梯度值对锚点进行排序
    void sortAnchorsByGradValue();
    // 返回根据梯度值排序的锚点数组
    int* sortAnchorsByGradValue1();

    // 返回从根节点开始的最长链
    static int LongestChain(Chain* chains, int root);
    // 检索链编号
    static int RetrieveChainNos(Chain* chains, int root, int chainNos[]);

    int anchorNos; // 锚点数量
    std::vector<cv::Point> anchorPoints; // 锚点点列表
    std::vector<cv::Point> edgePoints; // 边缘点列表

    cv::Mat edgeImage; // 边缘图像
    cv::Mat gradImage; // 梯度图像

    uchar* dirImg; // 方向图像数据的指针
    short* gradImg; // 梯度图像数据的指针

    GradientOperator op; // 用于梯度计算的操作
    int gradThresh; // 梯度阈值
    int anchorThresh; // 锚点阈值
    int scanInterval; // 扫描间隔
    bool sumFlag; // 总和标志
};

#endif
