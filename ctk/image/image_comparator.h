#pragma once

#include "abstract_image.h"

namespace ctk {

template<class T>
bool CompareAbsoluteImages(AbstractImage<T>& img1, AbstractImage<T>& img2) {    
    if (img1.GetWidth() != img2.GetWidth() or 
        img1.GetHeight() != img2.GetHeight() or
        img1.GetChannels() != img2.GetChannels() ) 
    {
        return false;
    }
    // TODO: investigate a more efficient way for data comparison
    for (int x = 0; x < img1.GetWidth(); ++x) {
        for (int y = 0; y < img1.GetHeight(); ++y) {
            if (img1.Get(x, y) != img2.Get(x, y))
                return false;
        }
    }
    return true;
}

template<class T>
int CountDifferentPixels(AbstractImage<T>& img1, AbstractImage<T>& img2) {
    int maxWidth = std::max(img1.GetWidth(), img2.GetWidth());
    int minWidth = std::min(img1.GetWidth(), img2.GetWidth());
    int maxHeight = std::max(img1.GetHeight(), img2.GetHeight());
    int minHeight = std::min(img1.GetHeight(), img2.GetHeight());
    if (img1.GetChannels() != img2.GetChannels() ) {
        return maxWidth * maxHeight;
    }
    // TODO: investigate a more efficient way for data comparison
    int diff = 0;
    for (int x = 0; x < maxWidth; ++x) {
        for (int y = 0; y < maxHeight; ++y) {
            if (x >= minWidth or y >= minHeight 
                or img1.Get(x, y) != img2.Get(x, y)) {
                diff++;
            }
        }
    }
    return diff;
}

template<class T>
float CompareRelativeImages(AbstractImage<T>& img1, AbstractImage<T>& img2) {
    int maxWidth = std::max(img1.GetWidth(), img2.GetWidth());
    int maxHeight = std::max(img1.GetHeight(), img2.GetHeight());
    int full_size = maxWidth * maxHeight;
    int correct = full_size - CountDifferentPixels(img1, img2);
    return static_cast<double>(correct) / static_cast<double>(full_size);
}

template<class T>
bool IsEquals(AbstractImage<T>& img1, AbstractImage<T>& img2) {
    return CompareAbsoluteImages(img1, img2);
}

int PixelL1Distance(cv::Vec3b px1, cv::Vec3b px2) {
    int r = abs(px1[0] - px2[0]);
    int g = abs(px1[1] - px2[1]);
    int b = abs(px1[2] - px2[2]);
    return r + g + b;
}

int PixelL1Distance(uchar px1, uchar px2) {
    return abs(static_cast<float>(px1 - px2));
}

int PixelL1Distance(bool px1, bool px2) {
    return static_cast<float>(px1 xor px2);
}

int GetDefaultDistance(cv::Vec3b) {
    return 255.0 * 3.0;
}

int GetDefaultDistance(uchar) {
    return 255.0;
}

int GetDefaultDistance(bool) {
    return 1.0;
}

template<class T>    
int ComparePixelAbsoluteDistance(AbstractImage<T>& img1, AbstractImage<T>& img2) {
    int maxWidth = std::max(img1.GetWidth(), img2.GetWidth());
    int minWidth = std::min(img1.GetWidth(), img2.GetWidth());
    int maxHeight = std::max(img1.GetHeight(), img2.GetHeight());
    int minHeight = std::min(img1.GetHeight(), img2.GetHeight());
    if (minWidth*minHeight < 1) {
        return maxWidth*maxHeight;
    }
    int pixel = GetDefaultDistance(img1.Get(0,0));
    // TODO: investigate a more efficient way for data comparison
    int diff = 0.0;
    for (int x = 0; x < maxWidth; ++x) {
        for (int y = 0; y < maxHeight; ++y) {
            if (x >= minWidth or y >= minHeight) {
                diff += pixel;
            }
            else if (img1.Get(x, y) != img2.Get(x, y)) {
                diff += PixelL1Distance(img1.Get(x, y), img2.Get(x, y));
            }
        }
    }
    return diff;
}

template<class T>    
double ComparePixelRelativeDistance(AbstractImage<T>& img1, AbstractImage<T>& img2) {
    int maxWidth = std::max(img1.GetWidth(), img2.GetWidth());
    int minWidth = std::min(img1.GetWidth(), img2.GetWidth());
    int maxHeight = std::max(img1.GetHeight(), img2.GetHeight());
    int minHeight = std::min(img1.GetHeight(), img2.GetHeight());
    if (minWidth*minHeight < 1) {
        return maxWidth*maxHeight;
    }
    int full_size = maxWidth * maxHeight * GetDefaultDistance(img1.Get(0,0));
    int absDist = ComparePixelAbsoluteDistance(img1, img2);
    return static_cast<double>(absDist) / static_cast<double>(full_size);
}
}