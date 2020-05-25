#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>
#include <algorithm>

#include "ctkmath.h"
#include "ctkbinarymatrix.h"
#include "ctknumericmatrix.h"

const int LARGE_RANGE_MIN = 8;
const int LARGE_RANGE_MAX = 8<<2;

const double NUMERIC_SCALAR = 1000.0;


//
// Auxiliar Function
//
void CreateBinaryMatrix(ctk::BinaryMatrix &bm, int w, int h) {
    bm.Create(w, h);
    for (auto x=0; x<w; x++) {
        for (auto y=0; y<h; y++) {
            bm.set(x,y, std::rand() % 2 == 0);
        }
    }
}

#if 0
//
// BinaryMatrix Creation
//

static void BM_CreateBinaryMatrix(benchmark::State& state) {
    for (auto _ : state) {
        ctk::BinaryMatrix bm;
        CreateBinaryMatrix(bm, state.range(0), state.range(1));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_CreateBinaryMatrix)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BM_CreateStdVector(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<bool> vec;
        vec.resize(state.range(0)*state.range(1));
        for (int i=0; i<vec.size(); i++) vec[i] = (std::rand() % 2 == 0);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_CreateStdVector)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BM_Vec2BinaryMatrix(benchmark::State& state) {
    std::vector<bool> vec;
    vec.resize(state.range(0)*state.range(1));
    for (int i=0; i<vec.size(); i++) vec[i] = (std::rand() % 2 == 0);
    //
    for (auto _ : state) {
        ctk::BinaryMatrix bm;
        bm.Create(state.range(0), state.range(1), vec);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_Vec2BinaryMatrix)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BM_CreateMat(benchmark::State& state) {
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
BENCHMARK(BM_CreateMat)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void BM_CvMat2BinaryMatrix(benchmark::State& state) {
    cv::Mat mat(state.range(1),state.range(0),CV_8U);
    for (int x=0; x<state.range(0); x++) {
        for(int y=0; y<state.range(1); y++) {
            mat.at<uchar>(y,x) = (std::rand() % 2==0)*255;
        }
    }
    for (auto _ : state) {
        ctk::BinaryMatrix bm(mat);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_CvMat2BinaryMatrix)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();
#endif

#if 0
//
// BinaryMatrix Counting
//

static void BM_CountTrues(benchmark::State& state) {
    ctk::BinaryMatrix bm;
    CreateBinaryMatrix(bm, state.range(0), state.range(0));
    for (auto _ : state) {
        bm.countTrues();
    }
    state.SetComplexityN(bm.size());
}
BENCHMARK(BM_CountTrues)
                ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
                ->Complexity(benchmark::oN);

static void BM_CountFalses(benchmark::State& state) {
    ctk::BinaryMatrix bm;
    CreateBinaryMatrix(bm, state.range(0), state.range(0));
    for (auto _ : state) {
        bm.countFalses();
    }
    state.SetComplexityN(bm.size());
}
BENCHMARK(BM_CountFalses)
                ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
                ->Complexity(benchmark::oN);

static void BM_CountTrues2(benchmark::State& state) {
    ctk::BinaryMatrix bm;
    CreateBinaryMatrix(bm, state.range(0), state.range(1));
    for (auto _ : state) {
        bm.countTrues();
    }
}
BENCHMARK(BM_CountTrues2)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}});
#endif

#if 0
//
// Logical Operations
//

static void BM_Not(benchmark::State& state) {
    ctk::BinaryMatrix m1;
    CreateBinaryMatrix(m1, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryMatrix m2 = m1.Not();
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(BM_Not)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);

static void BM_And(benchmark::State& state) {
    ctk::BinaryMatrix m1, m2;
    CreateBinaryMatrix(m1, state.range(0), state.range(1));
    CreateBinaryMatrix(m2, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryMatrix m3 = m1.And(m2);
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(BM_And)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);


static void BM_Or(benchmark::State& state) {
    ctk::BinaryMatrix m1, m2;
    CreateBinaryMatrix(m1, state.range(0), state.range(1));
    CreateBinaryMatrix(m2, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryMatrix m3 = m1.Or(m2);
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(BM_Or)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);


static void BM_Xor(benchmark::State& state) {
    ctk::BinaryMatrix m1, m2;
    CreateBinaryMatrix(m1, state.range(0), state.range(1));
    CreateBinaryMatrix(m2, state.range(0), state.range(1));
    for (auto _ : state) {
        ctk::BinaryMatrix m3 = m1.Xor(m2);
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(BM_Xor)
            ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                     {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
            ->Complexity(benchmark::oN);
#endif

//
// Auxiliar Functions
//

void CreateNumericMatrix(ctk::NumericMatrix &m, int w, int h)
{
    m.Create(w, h);
    for (auto x=0; x<w; x++) {
        for (auto y=0; y<h; y++) {
            m.set(x,y, std::rand());
        }
    }
}

void CreateNumericMat(cv::Mat &m, int w, int h)
{
    m = cv::Mat(h,w,CV_64F);
    for (int x=0; x<w; x++) {
        for(int y=0; y<h; y++) {
            m.at<double>(y,x) = std::rand();
        }
    }
}

#if 0
//
// NumericMatrix Creation
//

static void NM_CreateNumericMatrix(benchmark::State& state) {
    for (auto _ : state) {
        ctk::NumericMatrix m;
        CreateNumericMatrix(m, state.range(0), state.range(1));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(NM_CreateNumericMatrix)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void NM_CreateStdVector(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> vec;
        vec.resize(state.range(0)*state.range(1));
        for (int i=0; i<vec.size(); i++) vec[i] = std::rand();
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(NM_CreateStdVector)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void NM_Vec2NumericMatrix(benchmark::State& state) {
    std::vector<double> vec;
    vec.resize(state.range(0)*state.range(1));
    for (int i=0; i<vec.size(); i++) vec[i] = std::rand();
    //
    for (auto _ : state) {
        ctk::NumericMatrix m;
        m.Create(state.range(0), state.range(1), vec);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(NM_Vec2NumericMatrix)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void NM_CreateMat(benchmark::State& state) {
    for (auto _ : state) {
        cv::Mat mat;
        CreateNumericMat(mat, state.range(0),state.range(1));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(NM_CreateMat)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();

static void NM_CvMat2NumericMatrix(benchmark::State& state) {
    cv::Mat mat;
    CreateNumericMat(mat, state.range(0),state.range(1));
    for (auto _ : state) {
        ctk::NumericMatrix m(mat);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(NM_CvMat2NumericMatrix)
                ->Ranges({{LARGE_RANGE_MIN, LARGE_RANGE_MAX},
                         {LARGE_RANGE_MIN, LARGE_RANGE_MAX}})
                ->Complexity();
#endif


#if 0
//
// Arithmetic operations: by Matrix and returning result
//
static void NM_Sum(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m3 = m1 + m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_Sum)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSum(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m3 = m1 + m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSum)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_Diff(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m3 = m1 - m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_Diff)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatDiff(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m3 = m1 - m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatDiff)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_Mult(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m3 = m1 * m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_Mult)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatMult(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m3 = m1 * m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatMult)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_Div(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m3 = m1 / m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_Div)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatDiv(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m3 = m1 / m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatDiv)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

#endif

#if 0
//
// Arithmetic operations: by Matrix and Self
//
static void NM_SelfSum(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 += m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfSum)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfSum(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 += m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfSum)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_SelfDiff(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 -= m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfDiff)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfDiff(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 -= m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfDiff)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_SelfMult(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 *= m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfMult)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_MatSelfMult(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 *= m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfMult)
    ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
    ->Complexity(benchmark::oN);

static void NM_SelfDiv(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    CreateNumericMatrix(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 /= m2;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfDiv)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfDiv(benchmark::State& state) {
    cv::Mat m1, m2;
    CreateNumericMat(m1, state.range(0), state.range(0));
    CreateNumericMat(m2, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 /= m2;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfDiv)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

#endif


#if 0
//
// Arithmetic operations: by Scalar and returning result
//
static void NM_SumScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1 + NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SumScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSumScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m2 = m1 + NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSumScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_DiffScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1 - NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_DiffScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatDiffScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m2 = m1 - NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatDiffScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_MultScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1 * NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_MultScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatMultScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m2 = m1 * NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatMultScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_DivScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1 / NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_DivScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatDivScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::Mat m2 = m1 / NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatDivScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);
#endif


#if 1
//
// Arithmetic operations: by Scalar and Self
//
static void NM_SelfSumScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 += NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfSumScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfSumScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 += NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfSumScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_SelfDiffScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 -= NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfDiffScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfDiffScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 -= NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfDiffScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_SelfMultScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 *= NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfMultScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfMultScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 *= NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfMultScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_SelfDivScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 /= NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.size());
}
BENCHMARK(NM_SelfDivScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfDivScalar(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 /= NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfDivScalar)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

#endif





#if 0
//
// Sum
//
bool NumericMatrixScalarSum(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m3 = m1 + m2;
    return m3.rows()==d;
}

static void NM_NumericMatrixScalarSum(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixScalarSum(state.range(0));
}
BENCHMARK(NM_NumericMatrixScalarSum)->Range(8, 1000);

bool MatScalarSum(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m3 = m1 + m2;
    return m3.rows==d;
}

static void NM_MatScalarSum(benchmark::State& state) {
    for (auto _ : state)
        MatScalarSum(state.range(0));
}
BENCHMARK(NM_MatScalarSum)->Range(8, 1000);

bool NumericMatrixSelfScalarSum(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    m1 += m2;
    return m1.rows()==d;
}

static void NM_NumericMatrixSelfScalarSum(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixSelfScalarSum(state.range(0));
}
BENCHMARK(NM_NumericMatrixSelfScalarSum)->Range(8, 1000);

bool MatSelfScalarSum(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    m1 += m2;
    return m1.rows==d;
}

static void NM_MatSelfScalarSum(benchmark::State& state) {
    for (auto _ : state)
        MatSelfScalarSum(state.range(0));
}
BENCHMARK(NM_MatSelfScalarSum)->Range(8, 1000);

//
// Diff
//
bool NumericMatrixScalarDiff(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m3 = m1 - m2;
    return m3.rows()==d;
}

static void NM_NumericMatrixScalarDiff(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixScalarDiff(state.range(0));
}
BENCHMARK(NM_NumericMatrixScalarDiff)->Range(8, 1000);

bool MatScalarDiff(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m3 = m1 - m2;
    return m3.rows==d;
}

static void NM_MatScalarDiff(benchmark::State& state) {
    for (auto _ : state)
        MatScalarDiff(state.range(0));
}
BENCHMARK(NM_MatScalarDiff)->Range(8, 1000);

bool NumericMatrixSelfScalarDiff(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    m1 -= m2;
    return m1.rows()==d;
}

static void NM_NumericMatrixSelfScalarDiff(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixSelfScalarDiff(state.range(0));
}
BENCHMARK(NM_NumericMatrixSelfScalarDiff)->Range(8, 1000);

bool MatSelfScalarDiff(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    m1 -= m2;
    return m1.rows==d;
}

static void NM_MatSelfScalarDiff(benchmark::State& state) {
    for (auto _ : state)
        MatSelfScalarDiff(state.range(0));
}
BENCHMARK(NM_MatSelfScalarDiff)->Range(8, 1000);

//
// Mult
//
bool NumericMatrixScalarMult(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m3 = m1 * m2;
    return m3.rows()==d;
}

static void NM_NumericMatrixScalarMult(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixScalarMult(state.range(0));
}
BENCHMARK(NM_NumericMatrixScalarMult)->Range(8, 1000);

bool MatScalarMult(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m3 = m1 * m2;
    return m3.rows==d;
}

static void NM_MatScalarMult(benchmark::State& state) {
    for (auto _ : state)
        MatScalarMult(state.range(0));
}
BENCHMARK(NM_MatScalarMult)->Range(8, 1000);

bool NumericMatrixSelfScalarMult(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    m1 *= m2;
    return m1.rows()==d;
}

static void NM_NumericMatrixSelfScalarMult(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixSelfScalarMult(state.range(0));
}
BENCHMARK(NM_NumericMatrixSelfScalarMult)->Range(8, 1000);

bool MatSelfScalarMult(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    m1 *= m2;
    return m1.rows==d;
}

static void NM_MatSelfScalarMult(benchmark::State& state) {
    for (auto _ : state)
        MatSelfScalarMult(state.range(0));
}
BENCHMARK(NM_MatSelfScalarMult)->Range(8, 1000);

//
// Div
//
bool NumericMatrixScalarDiv(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m3 = m1 / m2;
    return m3.rows()==d;
}

static void NM_NumericMatrixScalarDiv(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixScalarDiv(state.range(0));
}
BENCHMARK(NM_NumericMatrixScalarDiv)->Range(8, 1000);

bool MatScalarDiv(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m3 = m1 / m2;
    return m3.rows==d;
}

static void NM_MatScalarDiv(benchmark::State& state) {
    for (auto _ : state)
        MatScalarDiv(state.range(0));
}
BENCHMARK(NM_MatScalarDiv)->Range(8, 1000);

bool NumericMatrixSelfScalarDiv(int d) {
    ctk::NumericMatrix m1;
    m1.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.set(x,y, std::rand());
        }
    }
    ctk::NumericMatrix m2;
    m2.Create(d, d);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.set(x,y, std::rand());
        }
    }
    m1 /= m2;
    return m1.rows()==d;
}

static void NM_NumericMatrixSelfScalarDiv(benchmark::State& state) {
    for (auto _ : state)
        NumericMatrixSelfScalarDiv(state.range(0));
}
BENCHMARK(NM_NumericMatrixSelfScalarDiv)->Range(8, 1000);

bool MatSelfScalarDiv(int d) {
    cv::Mat m1(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m1.at<double>(y,x) = std::rand();
        }
    }
    cv::Mat m2(d, d, CV_64F);
    for (auto x=0; x<d; x++) {
        for (auto y=0; y<d; y++) {
            m2.at<double>(y,x) = std::rand();
        }
    }
    m1 /= m2;
    return m1.rows==d;
}

static void NM_MatSelfScalarDiv(benchmark::State& state) {
    for (auto _ : state)
        MatSelfScalarDiv(state.range(0));
}
BENCHMARK(NM_MatSelfScalarDiv)->Range(8, 1000);

#endif


BENCHMARK_MAIN();
