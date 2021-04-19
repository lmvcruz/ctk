#include "point_test.h"

#include "test_setup.h"

#ifdef TEST_POINT
TEST_F(CtkPointTest, Test_Get) {
    EXPECT_EQ(CtkPointTest::Pi.GetX(), 1);
    EXPECT_EQ(CtkPointTest::Pi.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pi.GetZ(), 3);

    EXPECT_EQ(CtkPointTest::Pi_1.GetX(), 2);
    EXPECT_EQ(CtkPointTest::Pi_1.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pi_1.GetZ(), 0);

    EXPECT_EQ(CtkPointTest::Pui.GetX(), 1);
    EXPECT_EQ(CtkPointTest::Pui.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pui.GetZ(), 3);

    EXPECT_EQ(CtkPointTest::Pl.GetX(), 1);
    EXPECT_EQ(CtkPointTest::Pl.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pl.GetZ(), 3);

    EXPECT_EQ(CtkPointTest::Pul.GetX(), 1);
    EXPECT_EQ(CtkPointTest::Pul.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pul.GetZ(), 3);

    EXPECT_EQ(CtkPointTest::Pll.GetX(), 1);
    EXPECT_EQ(CtkPointTest::Pll.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pll.GetZ(), 3);

    EXPECT_EQ(CtkPointTest::Pull.GetX(), 1);
    EXPECT_EQ(CtkPointTest::Pull.GetY(), 2);
    EXPECT_EQ(CtkPointTest::Pull.GetZ(), 3);

    EXPECT_DOUBLE_EQ(CtkPointTest::Pd.GetX(), 1.1);
    EXPECT_DOUBLE_EQ(CtkPointTest::Pd.GetY(), 2.1);
    EXPECT_DOUBLE_EQ(CtkPointTest::Pd.GetZ(), 3.1);
}

TEST_F(CtkPointTest, Test_DefaultConstructor) {
    ctk::Point<int> P1;
    EXPECT_EQ(P1.GetX(), 0);
    EXPECT_EQ(P1.GetY(), 0);
    EXPECT_EQ(P1.GetZ(), 0);

    ctk::Point<unsigned int> P2;
    EXPECT_EQ(P2.GetX(), 0);
    EXPECT_EQ(P2.GetY(), 0);
    EXPECT_EQ(P2.GetZ(), 0);

    ctk::Point<long> P3;
    EXPECT_EQ(P3.GetX(), 0);
    EXPECT_EQ(P3.GetY(), 0);
    EXPECT_EQ(P3.GetZ(), 0);

    ctk::Point<unsigned long> P4;
    EXPECT_EQ(P4.GetX(), 0);
    EXPECT_EQ(P4.GetY(), 0);
    EXPECT_EQ(P4.GetZ(), 0);

    ctk::Point<long long> P5;
    EXPECT_EQ(P5.GetX(), 0);
    EXPECT_EQ(P5.GetY(), 0);
    EXPECT_EQ(P5.GetZ(), 0);

    ctk::Point<unsigned long long> P6;
    EXPECT_EQ(P6.GetX(), 0);
    EXPECT_EQ(P6.GetY(), 0);
    EXPECT_EQ(P6.GetZ(), 0);

    ctk::Point<double> P7;
    EXPECT_DOUBLE_EQ(P7.GetX(), 0);
    EXPECT_DOUBLE_EQ(P7.GetY(), 0);
    EXPECT_DOUBLE_EQ(P7.GetZ(), 0);
}

TEST_F(CtkPointTest, Test_CopyConstructor) {
    ctk::Point<int> Pic(CtkPointTest::Pi);
    EXPECT_EQ(Pic.GetX(), 1);
    EXPECT_EQ(Pic.GetY(), 2);
    EXPECT_EQ(Pic.GetZ(), 3);

    ctk::Point<unsigned int> Puic(CtkPointTest::Pui);
    EXPECT_EQ(Puic.GetX(), 1);
    EXPECT_EQ(Puic.GetY(), 2);
    EXPECT_EQ(Puic.GetZ(), 3);

    ctk::Point<long> Plc(CtkPointTest::Pl);
    EXPECT_EQ(Plc.GetX(), 1);
    EXPECT_EQ(Plc.GetY(), 2);
    EXPECT_EQ(Plc.GetZ(), 3);

    ctk::Point<unsigned long> Pulc(CtkPointTest::Pul);
    EXPECT_EQ(Pulc.GetX(), 1);
    EXPECT_EQ(Pulc.GetY(), 2);
    EXPECT_EQ(Pulc.GetZ(), 3);

    ctk::Point<long long> Pllc(CtkPointTest::Pll);
    EXPECT_EQ(Pllc.GetX(), 1);
    EXPECT_EQ(Pllc.GetY(), 2);
    EXPECT_EQ(Pllc.GetZ(), 3);

    ctk::Point<unsigned long long> Pullc(CtkPointTest::Pull);
    EXPECT_EQ(Pullc.GetX(), 1);
    EXPECT_EQ(Pullc.GetY(), 2);
    EXPECT_EQ(Pullc.GetZ(), 3);

    ctk::Point<double> Pdc(CtkPointTest::Pd);
    EXPECT_DOUBLE_EQ(Pdc.GetX(), 1.1);
    EXPECT_DOUBLE_EQ(Pdc.GetY(), 2.1);
    EXPECT_DOUBLE_EQ(Pdc.GetZ(), 3.1);
}

TEST_F(CtkPointTest, Test_OperatorCopy) {
    ctk::Point<int> Pic = CtkPointTest::Pi;
    EXPECT_EQ(Pic.GetX(), 1);
    EXPECT_EQ(Pic.GetY(), 2);
    EXPECT_EQ(Pic.GetZ(), 3);

    ctk::Point<unsigned int> Puic = CtkPointTest::Pui;
    EXPECT_EQ(Puic.GetX(), 1);
    EXPECT_EQ(Puic.GetY(), 2);
    EXPECT_EQ(Puic.GetZ(), 3);

    ctk::Point<long> Plc = CtkPointTest::Pl;
    EXPECT_EQ(Plc.GetX(), 1);
    EXPECT_EQ(Plc.GetY(), 2);
    EXPECT_EQ(Plc.GetZ(), 3);

    ctk::Point<unsigned long> Pulc = CtkPointTest::Pul;
    EXPECT_EQ(Pulc.GetX(), 1);
    EXPECT_EQ(Pulc.GetY(), 2);
    EXPECT_EQ(Pulc.GetZ(), 3);

    ctk::Point<long long> Pllc = CtkPointTest::Pll;
    EXPECT_EQ(Pllc.GetX(), 1);
    EXPECT_EQ(Pllc.GetY(), 2);
    EXPECT_EQ(Pllc.GetZ(), 3);

    ctk::Point<unsigned long long> Pullc = CtkPointTest::Pull;
    EXPECT_EQ(Pullc.GetX(), 1);
    EXPECT_EQ(Pullc.GetY(), 2);
    EXPECT_EQ(Pullc.GetZ(), 3);

    ctk::Point<double> Pdc = CtkPointTest::Pd;
    EXPECT_DOUBLE_EQ(Pdc.GetX(), 1.1);
    EXPECT_DOUBLE_EQ(Pdc.GetY(), 2.1);
    EXPECT_DOUBLE_EQ(Pdc.GetZ(), 3.1);
}

TEST_F(CtkPointTest, Test_OperatorEqual) {
    ctk::PointI Pic = CtkPointTest::Pi;
    EXPECT_FALSE(CtkPointTest::Pi == CtkPointTest::Pi_2);
    EXPECT_TRUE(CtkPointTest::Pi == Pic);

    EXPECT_TRUE(CtkPointTest::Pi != CtkPointTest::Pi_2);
    EXPECT_FALSE(CtkPointTest::Pi != Pic);

    ctk::PointD Pdc = CtkPointTest::Pd;
    EXPECT_FALSE(CtkPointTest::Pd == CtkPointTest::Pd_2);
    EXPECT_TRUE(CtkPointTest::Pd == Pdc);

    EXPECT_TRUE(CtkPointTest::Pd != CtkPointTest::Pd_2);
    EXPECT_FALSE(CtkPointTest::Pd != Pdc);
}

TEST_F(CtkPointTest, Test_OperatorSum) {
    ctk::PointI Pis = CtkPointTest::Pi + CtkPointTest::Pi_2;
    EXPECT_EQ(Pis.GetX(), 5);
    EXPECT_EQ(Pis.GetY(), 7);
    EXPECT_EQ(Pis.GetZ(), 6);

    ctk::PointD Pds = CtkPointTest::Pd + CtkPointTest::Pd_2;
    EXPECT_DOUBLE_EQ(Pds.GetX(), 2.2);
    EXPECT_DOUBLE_EQ(Pds.GetY(), 7.6);
    EXPECT_DOUBLE_EQ(Pds.GetZ(), 9.7);
}

TEST_F(CtkPointTest, Test_AdditionAssignement) {
    ctk::PointI Pis(1, 1, 1);
    Pis += CtkPointTest::Pi;
    EXPECT_EQ(Pis.GetX(), 2);
    EXPECT_EQ(Pis.GetY(), 3);
    EXPECT_EQ(Pis.GetZ(), 4);

    ctk::PointD Pds(2.1, 1.2, 3.3);
    Pds += CtkPointTest::Pd;
    EXPECT_DOUBLE_EQ(Pds.GetX(), 3.2);
    EXPECT_DOUBLE_EQ(Pds.GetY(), 3.3);
    EXPECT_DOUBLE_EQ(Pds.GetZ(), 6.4);
}

TEST_F(CtkPointTest, Test_OperatorSubtraction) {
    ctk::PointI Pis = CtkPointTest::Pi_2 - CtkPointTest::Pi;
    EXPECT_EQ(Pis.GetX(), 3);
    EXPECT_EQ(Pis.GetY(), 3);
    EXPECT_EQ(Pis.GetZ(), 0);

    ctk::PointD Pds = CtkPointTest::Pd_2 - CtkPointTest::Pd;
    EXPECT_DOUBLE_EQ(Pds.GetX(), 0);
    EXPECT_DOUBLE_EQ(Pds.GetY(), 3.4);
    EXPECT_DOUBLE_EQ(Pds.GetZ(), 3.5);
}

TEST_F(CtkPointTest, Test_SubtractionAssignement) {
    ctk::PointI Pis(10, 10, 10);
    Pis -= CtkPointTest::Pi;
    EXPECT_EQ(Pis.GetX(), 9);
    EXPECT_EQ(Pis.GetY(), 8);
    EXPECT_EQ(Pis.GetZ(), 7);

    ctk::PointD Pds(10, 10, 10);
    Pds -= CtkPointTest::Pd;
    EXPECT_DOUBLE_EQ(Pds.GetX(), 8.9);
    EXPECT_DOUBLE_EQ(Pds.GetY(), 7.9);
    EXPECT_DOUBLE_EQ(Pds.GetZ(), 6.9);
}

TEST_F(CtkPointTest, Test_OperatorMultiplication) {
    ctk::PointI Pim = CtkPointTest::Pi_2 * CtkPointTest::Pi;
    EXPECT_EQ(Pim.GetX(), 4);
    EXPECT_EQ(Pim.GetY(), 10);
    EXPECT_EQ(Pim.GetZ(), 9);

    ctk::PointD Pdm = CtkPointTest::Pd_2 * CtkPointTest::Pd;
    EXPECT_DOUBLE_EQ(Pdm.GetX(), 1.21);
    EXPECT_DOUBLE_EQ(Pdm.GetY(), 11.55);
    EXPECT_DOUBLE_EQ(Pdm.GetZ(), 20.46);
}

TEST_F(CtkPointTest, Test_MultiplicationAssignement) {
    ctk::PointI Pim(2, 2, 2);
    Pim *= CtkPointTest::Pi;
    EXPECT_EQ(Pim.GetX(), 2);
    EXPECT_EQ(Pim.GetY(), 4);
    EXPECT_EQ(Pim.GetZ(), 6);

    ctk::PointD Pdm(2, 2, 2);
    Pdm *= CtkPointTest::Pd;
    EXPECT_DOUBLE_EQ(Pdm.GetX(), 2.2);
    EXPECT_DOUBLE_EQ(Pdm.GetY(), 4.2);
    EXPECT_DOUBLE_EQ(Pdm.GetZ(), 6.2);
}

TEST_F(CtkPointTest, Test_OperatorDivision) {
    ctk::PointI Pix(2, 4, 6);
    ctk::PointI Pid = Pix / CtkPointTest::Pi ;
    EXPECT_EQ(Pid.GetX(), 2);
    EXPECT_EQ(Pid.GetY(), 2);
    EXPECT_EQ(Pid.GetZ(), 2);

    ctk::PointD Pdx(2, 2, 2);
    ctk::PointD Pdm = CtkPointTest::Pd / Pdx;
    EXPECT_DOUBLE_EQ(Pdm.GetX(), 0.55);
    EXPECT_DOUBLE_EQ(Pdm.GetY(), 1.05);
    EXPECT_DOUBLE_EQ(Pdm.GetZ(), 1.55);
}

TEST_F(CtkPointTest, Test_DivisionAssignement) {
    // Also testing initialize list constructor
    ctk::PointI Pix = {2, 4, 6};
    Pix /= CtkPointTest::Pi ;
    EXPECT_EQ(Pix.GetX(), 2);
    EXPECT_EQ(Pix.GetY(), 2);
    EXPECT_EQ(Pix.GetZ(), 2);

    ctk::PointD Pdx = {2.2, 4.2, 6.2};
    Pdx /= CtkPointTest::Pd ;
    EXPECT_DOUBLE_EQ(Pdx.GetX(), 2);
    EXPECT_DOUBLE_EQ(Pdx.GetY(), 2);
    EXPECT_DOUBLE_EQ(Pdx.GetZ(), 2);
}

TEST_F(CtkPointTest, Test_ManhattanLength) {
    EXPECT_EQ(CtkPointTest::Pi.ManhattanLength(), 6);
    EXPECT_EQ(CtkPointTest::Pd.ManhattanLength(), 6);
}

TEST_F(CtkPointTest, Test_Norm) {
    EXPECT_DOUBLE_EQ(CtkPointTest::Pi.Norm(), std::sqrt(14));
    EXPECT_DOUBLE_EQ(CtkPointTest::Pd.Norm(), std::sqrt(15.23));
}

TEST_F(CtkPointTest, Test_Inner) {
    EXPECT_DOUBLE_EQ(CtkPointTest::Pi.Inner(CtkPointTest::Pi_2), 23);
    EXPECT_DOUBLE_EQ(CtkPointTest::Pd.Inner(CtkPointTest::Pd_2), 33.22);
}

TEST_F(CtkPointTest, Test_Outter) {
    ctk::PointI outI = CtkPointTest::Pi.Outter(CtkPointTest::Pi_2);
    EXPECT_EQ(outI.GetX(), -9);
    EXPECT_EQ(outI.GetY(), 9);
    EXPECT_EQ(outI.GetZ(), -3);

    ctk::PointD ouD = CtkPointTest::Pd.Outter(CtkPointTest::Pd_2);
    EXPECT_DOUBLE_EQ(ouD.GetX(), -3.19);
    EXPECT_DOUBLE_EQ(ouD.GetY(), -3.85);
    EXPECT_DOUBLE_EQ(ouD.GetZ(), +3.74);
}

TEST_F(CtkPointTest, Test_Distance) {
    EXPECT_DOUBLE_EQ(CtkPointTest::Pi.Distance(CtkPointTest::Pi_2),
                     std::sqrt(18));
    EXPECT_DOUBLE_EQ(CtkPointTest::Pd.Distance(CtkPointTest::Pd_2),
                     std::sqrt(23.81));
}

TEST_F(CtkPointTest, Test_Angle) {
    ctk::PointD p(0, 0);
    ctk::PointD p1(0, 1);
    ctk::PointD p2(1, 0);
    EXPECT_DOUBLE_EQ(p.Angle(p1,p2), std::acos(0.0));
}

TEST_F(CtkPointTest, Test_Normalize) {
    ctk::PointI norm = CtkPointTest::Pi_1.Normalize();
    EXPECT_EQ(norm.GetX(), 1);
    EXPECT_EQ(norm.GetY(), 1);
    EXPECT_EQ(norm.GetZ(), 0);
}

TEST_F(CtkPointTest, Test_SelfNormalize) {
    ctk::PointI norm(CtkPointTest::Pi_1);
    norm.SelfNormalize();
    EXPECT_EQ(norm.GetX(), 1);
    EXPECT_EQ(norm.GetY(), 1);
    EXPECT_EQ(norm.GetZ(), 0);
}
#endif
