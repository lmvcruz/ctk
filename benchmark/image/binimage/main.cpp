#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>

#include "ctk/image/binary_image.h"
#include "ctk/matrix/numeric_matrix.h"

const int LARGE_RANGE_MIN = 8;
const int LARGE_RANGE_MAX = 8<<2;
const double NUMERIC_SCALAR = 1000.0;


//
// Auxiliar Function
//
void CreateBinaryImage(ctk::BinaryImage &bm, int w, int h) {
    bm.Create(w, h);
    for (auto x=0; x<w; x++) {
        for (auto y=0; y<h; y++) {
            bm.Set(x,y, std::rand() % 2 == 0);
        }
    }
}

#if 1
//
// BinaryImage Creation
//

static void BINIMG_CreateBinaryImage(benchmark::State& state) {
    for (auto _ : state) {
        ctk::BinaryImage bm;
        CreateBinaryImage(bm, state.range(0), state.range(1));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BINIMG_CreateBinaryImage)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BINIMG_CreateStdVector(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<bool> vec;
        vec.resize(state.range(0)*state.range(1));
        for (int i=0; i<vec.size(); i++) vec[i] = (std::rand() % 2 == 0);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BINIMG_CreateStdVector)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BINIMG_Vec2BinaryImage(benchmark::State& state) {
    std::vector<bool> vec;
    vec.resize(state.range(0)*state.range(1));
    for (int i=0; i<vec.size(); i++) vec[i] = (std::rand() % 2 == 0);
    //
    for (auto _ : state) {
        ctk::BinaryImage bm;
        bm.Create(state.range(0), state.range(1), vec);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BINIMG_Vec2BinaryImage)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BINIMG_CreateMat(benchmark::State& state) {
    for (auto _ : state) {
        cv::Mat mat(state.range(1),state.range(0),CV_8U);
        for (int x=0; x<state.range(0); x++) {
            for(int y=0; y<state.range(1); y++) {
                mat.at<uchar>(y,x) = (std::rand() % 2==0)*255;
            }
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BINIMG_CreateMat)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BINIMG_CvMat2BinaryImage(benchmark::State& state) {
    cv::Mat mat(state.range(1),state.range(0),CV_8U);
    for (int x=0; x<state.range(0); x++) {
        for(int y=0; y<state.range(1); y++) {
            mat.at<uchar>(y,x) = (std::rand() % 2==0)*255;
        }
    }
    for (auto _ : state) {
        ctk::BinaryImage bm(mat);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BINIMG_CvMat2BinaryImage)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();
#endif

#if 1
//
// BinaryImage Counting
//

static void BINIMG_CountTrues(benchmark::State& state) {
    ctk::BinaryImage bm;
    CreateBinaryImage(bm, state.range(0), state.range(0));
    for (auto _ : state) {
        bm.CountTrues();
    }
    state.SetComplexityN(bm.GetSize());
}
BENCHMARK(BINIMG_CountTrues)
                ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
                ->Complexity(benchmark::oN);

static void BINIMG_CountFalses(benchmark::State& state) {
    ctk::BinaryImage bm;
    CreateBinaryImage(bm, state.range(0), state.range(0));
    for (auto _ : state) {
        bm.CountFalses();
    }
    state.SetComplexityN(bm.GetSize());
}
BENCHMARK(BINIMG_CountFalses)
                ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
                ->Complexity(benchmark::oN);

static void BINIMG_CountTrues2(benchmark::State& state) {
    ctk::BinaryImage bm;
    CreateBinaryImage(bm, state.range(0), state.range(1));
    for (auto _ : state) {
        bm.CountTrues();
    }
}
BENCHMARK(BINIMG_CountTrues2)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}});
#endif

#if 1
//
// Logical Operations
//

static void BINIMG_Not(benchmark::State& state) {
    ctk::BinaryImage m1;
    CreateBinaryImage(m1, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryImage m2 = m1.Not();
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(BINIMG_Not)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);

static void BINIMG_And(benchmark::State& state) {
    ctk::BinaryImage m1, m2;
    CreateBinaryImage(m1, state.range(0), state.range(1));
    CreateBinaryImage(m2, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryImage m3 = m1.And(m2);
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(BINIMG_And)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);


static void BINIMG_Or(benchmark::State& state) {
    ctk::BinaryImage m1, m2;
    CreateBinaryImage(m1, state.range(0), state.range(1));
    CreateBinaryImage(m2, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryImage m3 = m1.Or(m2);
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(BINIMG_Or)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);


static void BINIMG_Xor(benchmark::State& state) {
    ctk::BinaryImage m1, m2;
    CreateBinaryImage(m1, state.range(0), state.range(1));
    CreateBinaryImage(m2, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryImage m3 = m1.Xor(m2);
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(BINIMG_Xor)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);
#endif

BENCHMARK_MAIN();
