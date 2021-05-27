#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>

#include "ctk/image/rgb_image.h"
#include "ctk/matrix/numeric_matrix.h"

const int LARGE_RANGE_MIN = 8;
const int LARGE_RANGE_MAX = 8<<2;
const double NUMERIC_SCALAR = 1000.0;


//
// Auxiliar Function
//
void CreateRgbImage(ctk::RgbImage &img, int w, int h) {
    img.Create(w, h);
    for (auto x=0; x<w; x++) {
        for (auto y=0; y<h; y++) {
            int r = std::rand() % 255;
            int g = std::rand() % 255;
            int b = std::rand() % 255;
            img.Set(x, y, r, g, b);
        }
    }
}

#if 1
//
// RgbImage Creation
//

static void RGBIMG_CreateRgbImage(benchmark::State& state) {
    for (auto _ : state) {
        ctk::RgbImage img;
        CreateRgbImage(img, state.range(0), state.range(1));
    }
    state.SetComplexityN(state.range(0)*state.range(1));
}
BENCHMARK(RGBIMG_CreateRgbImage)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

// TODO: add constructor from vector
// static void RGBIMG_CreateStdVector(benchmark::State& state) {
//     for (auto _ : state) {
//         std::vector<bool> vec;
//         vec.resize(state.range(0)*state.range(1));
//         for (int i=0; i<vec.size(); i++) vec[i] = (std::rand() % 2 == 0);
//     }
//     state.SetComplexityN(state.range(0));
// }
// BENCHMARK(RGBIMG_CreateStdVector)
//                 ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
//                          {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
//                 ->Complexity();
//
// static void RGBIMG_Vec2RgbImage(benchmark::State& state) {
//     std::vector<bool> vec;
//     vec.resize(state.range(0)*state.range(1)*3);
//     for (int i=0; i<vec.size(); i++) vec[i] = std::rand() % 255;
//     //
//     for (auto _ : state) {
//         ctk::RgbImage img;
//         img.Create(state.range(0), state.range(1), vec);
//     }
//     state.SetComplexityN(state.range(0));
// }
// BENCHMARK(RGBIMG_Vec2RgbImage)
//                 ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
//                          {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
//                 ->Complexity();

static void RGBIMG_CreateMat(benchmark::State& state) {
    // Random numbers are generated before benchmarking
    std::vector<int> numbers;
    numbers.resize(state.range(0) * state.range(1) * 3);
    for (auto &v: numbers) v = std::rand() % 255;
    // This loop will be benchmarked
    for (auto _ : state) {
        int i = -1;
        cv::Mat mat(state.range(1), state.range(0), CV_8UC3);
        for (int x=0; x<state.range(0); x++) {
            for(int y=0; y<state.range(1); y++) {
                mat.at<cv::Vec3b>(y,x)[0] = numbers[++i];
                mat.at<cv::Vec3b>(y,x)[1] = numbers[++i];
                mat.at<cv::Vec3b>(y,x)[2] = numbers[++i];
            }
        }
    }
    state.SetComplexityN(state.range(0)*state.range(1));
}
BENCHMARK(RGBIMG_CreateMat)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void RGBIMG_CvMat2RgbImage(benchmark::State& state) {
    ctk::RgbImage rgb;
    CreateRgbImage(rgb, state.range(0), state.range(1));
    cv::Mat mat = rgb.GetData().clone();
    for (auto _ : state) {
        ctk::RgbImage img(mat);
    }
    state.SetComplexityN(state.range(0)*state.range(1));
}
BENCHMARK(RGBIMG_CvMat2RgbImage)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();
#endif

BENCHMARK_MAIN();
