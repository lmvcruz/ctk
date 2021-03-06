#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "ctk/matrix/numeric_matrix.h"

const int LARGE_RANGE_MIN = 8;
const int LARGE_RANGE_MAX = 8<<2;

const double NUMERIC_SCALAR = 1000.0;

//
// Auxiliar Functions
//

void CreateNumericMatrix(ctk::NumericMatrix &m, int w, int h)
{
    m.Create(w, h);
    for (auto x=0; x<w; x++) {
        for (auto y=0; y<h; y++) {
            m.Set(x,y, std::rand()%10);
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

#if 1
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


#if 1
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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

#if 1
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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


#if 1
//
// Arithmetic operations: by Scalar and returning result
//
static void NM_SumScalar(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1 + NUMERIC_SCALAR;
    }
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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
    state.SetComplexityN(m1.GetSize());
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


#if 1
//
// Linear Algebra
//
static void NM_Determinant(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1.Determinant();
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(NM_Determinant)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatDeterminant(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        cv::determinant(m1);
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatDeterminant)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_Invert(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1.Invert();
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(NM_Invert)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatInvert(benchmark::State& state) {
    cv::Mat m1;
    do {
        CreateNumericMat(m1, state.range(0), state.range(0));
    } while( std::fabs(cv::determinant(m1)<=FLT_EPSILON) );
    //
    for (auto _ : state) {
        cv::Mat m2 = m1.inv();
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatInvert)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_SelfInvert(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    do {
        CreateNumericMatrix(m1, state.range(0), state.range(0));
    } while( std::fabs(m1.Determinant())<=FLT_EPSILON );
    //
    for (auto _ : state) {
        m2 = m1;
        m2.SelfInvert();
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(NM_SelfInvert)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfInvert(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 = m1.inv();
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfInvert)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);
#endif


#if 1
static void NM_Transpose(benchmark::State& state) {
    ctk::NumericMatrix m1;
    CreateNumericMatrix(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        ctk::NumericMatrix m2 = m1.Transpose();
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(NM_Transpose)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatTranspose(benchmark::State& state) {
    cv::Mat m1;
    do {
        CreateNumericMat(m1, state.range(0), state.range(0));
    } while( std::fabs(cv::determinant(m1)<=FLT_EPSILON) );
    //
    for (auto _ : state) {
        cv::Mat m2 = m1.t();
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatTranspose)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);

static void NM_SelfTranspose(benchmark::State& state) {
    ctk::NumericMatrix m1, m2;
    do {
        CreateNumericMatrix(m1, state.range(0), state.range(0));
    } while( std::fabs(m1.Determinant())<=FLT_EPSILON );
    //
    for (auto _ : state) {
        m2 = m1;
        m2.SelfTranspose();
    }
    state.SetComplexityN(m1.GetSize());
}
BENCHMARK(NM_SelfTranspose)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);


static void NM_MatSelfTranspose(benchmark::State& state) {
    cv::Mat m1;
    CreateNumericMat(m1, state.range(0), state.range(0));
    for (auto _ : state) {
        m1 = m1.t();
    }
    state.SetComplexityN(m1.rows*m1.cols);
}
BENCHMARK(NM_MatSelfTranspose)
            ->Range(LARGE_RANGE_MIN, LARGE_RANGE_MAX)
            ->Complexity(benchmark::oN);
#endif

BENCHMARK_MAIN();
