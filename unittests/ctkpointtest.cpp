#include "ctkpointtest.h"
#include "ctktestsetup.h"

void CtkPointTest::SetUp(){

    Pi.set(1,2,3);
    Pi_1.set(2,2);
    Pi_2.set(4,5,3);
    Pui.set(1,2,3);
    Pl.set(1,2,3);
    Pul.set(1,2,3);
    Pll.set(1,2,3);
    Pull.set(1,2,3);
    Pd.set(1.1,2.1,3.1);
    Pd_1.set(1,1,1);
    Pd_2.set(1.1,5.5,6.6);

}

#ifdef TEST_POINT
TEST_F(CtkPointTest, Test_Setup){

}

TEST_F(CtkPointTest, Test_Get){

 EXPECT_EQ(CtkPointTest::Pi.getX(),1);
 EXPECT_EQ(CtkPointTest::Pi.getY(),2);
 EXPECT_EQ(CtkPointTest::Pi.getZ(),3);

 EXPECT_EQ(CtkPointTest::Pi_1.getX(),2);
 EXPECT_EQ(CtkPointTest::Pi_1.getY(),2);
 EXPECT_EQ(CtkPointTest::Pi_1.getZ(),0);

 EXPECT_EQ(CtkPointTest::Pui.getX(),1);
 EXPECT_EQ(CtkPointTest::Pui.getY(),2);
 EXPECT_EQ(CtkPointTest::Pui.getZ(),3);

 EXPECT_EQ(CtkPointTest::Pl.getX(),1);
 EXPECT_EQ(CtkPointTest::Pl.getY(),2);
 EXPECT_EQ(CtkPointTest::Pl.getZ(),3);

 EXPECT_EQ(CtkPointTest::Pul.getX(),1);
 EXPECT_EQ(CtkPointTest::Pul.getY(),2);
 EXPECT_EQ(CtkPointTest::Pul.getZ(),3);

 EXPECT_EQ(CtkPointTest::Pll.getX(),1);
 EXPECT_EQ(CtkPointTest::Pll.getY(),2);
 EXPECT_EQ(CtkPointTest::Pll.getZ(),3);

 EXPECT_EQ(CtkPointTest::Pull.getX(),1);
 EXPECT_EQ(CtkPointTest::Pull.getY(),2);
 EXPECT_EQ(CtkPointTest::Pull.getZ(),3);

 EXPECT_EQ(CtkPointTest::Pd.getX(),1.1);
 EXPECT_EQ(CtkPointTest::Pd.getY(),2.1);
 //EXPECT_EQ(CtkPointTest::Pd.getZ(),3.1);
}

TEST_F(CtkPointTest, Test_DefaultConstructor){
 ctk::Point<int> P1;
 EXPECT_EQ(P1.getX(),0);
 EXPECT_EQ(P1.getY(),0);
 EXPECT_EQ(P1.getZ(),0);

 ctk::Point<unsigned int> P2;
 EXPECT_EQ(P2.getX(),0);
 EXPECT_EQ(P2.getY(),0);
 EXPECT_EQ(P2.getZ(),0);

 ctk::Point<long> P3;
 EXPECT_EQ(P3.getX(),0);
 EXPECT_EQ(P3.getY(),0);
 EXPECT_EQ(P3.getZ(),0);

 ctk::Point<unsigned long> P4;
 EXPECT_EQ(P4.getX(),0);
 EXPECT_EQ(P4.getY(),0);
 EXPECT_EQ(P4.getZ(),0);

 ctk::Point<long long> P5;
 EXPECT_EQ(P5.getX(),0);
 EXPECT_EQ(P5.getY(),0);
 EXPECT_EQ(P5.getZ(),0);

 ctk::Point<unsigned long long> P6;
 EXPECT_EQ(P6.getX(),0);
 EXPECT_EQ(P6.getY(),0);
 EXPECT_EQ(P6.getZ(),0);

 ctk::Point<double> P7;
 EXPECT_EQ(P7.getX(),0);
 EXPECT_EQ(P7.getY(),0);
 EXPECT_EQ(P7.getZ(),0);
}

TEST_F(CtkPointTest, Test_CopyConstructor){
 ctk::Point<int> Pic(CtkPointTest::Pi);
 EXPECT_EQ(Pic.getX(),1);
 EXPECT_EQ(Pic.getY(),2);
 EXPECT_EQ(Pic.getZ(),3);

 ctk::Point<unsigned int> Puic(CtkPointTest::Pui);
 EXPECT_EQ(Puic.getX(),1);
 EXPECT_EQ(Puic.getY(),2);
 EXPECT_EQ(Puic.getZ(),3);

 ctk::Point<long> Plc(CtkPointTest::Pl);
 EXPECT_EQ(Plc.getX(),1);
 EXPECT_EQ(Plc.getY(),2);
 EXPECT_EQ(Plc.getZ(),3);

 ctk::Point<unsigned long> Pulc(CtkPointTest::Pul);
 EXPECT_EQ(Pulc.getX(),1);
 EXPECT_EQ(Pulc.getY(),2);
 EXPECT_EQ(Pulc.getZ(),3);

 ctk::Point<long long> Pllc(CtkPointTest::Pll);
 EXPECT_EQ(Pllc.getX(),1);
 EXPECT_EQ(Pllc.getY(),2);
 EXPECT_EQ(Pllc.getZ(),3);

 ctk::Point<unsigned long long> Pullc(CtkPointTest::Pull);
 EXPECT_EQ(Pullc.getX(),1);
 EXPECT_EQ(Pullc.getY(),2);
 EXPECT_EQ(Pullc.getZ(),3);

 ctk::Point<double> Pdc(CtkPointTest::Pd);
 EXPECT_EQ(Pdc.getX(),1.1);
 EXPECT_EQ(Pdc.getY(),2.1);
 //EXPECT_EQ(Pdc.getZ(),3.1);
}

TEST_F(CtkPointTest, Test_OperatorCopy){
    ctk::Point<int> Pic = CtkPointTest::Pi;
    EXPECT_EQ(Pic.getX(),1);
    EXPECT_EQ(Pic.getY(),2);
    EXPECT_EQ(Pic.getZ(),3);

    ctk::Point<unsigned int> Puic = CtkPointTest::Pui;
    EXPECT_EQ(Puic.getX(),1);
    EXPECT_EQ(Puic.getY(),2);
    EXPECT_EQ(Puic.getZ(),3);

    ctk::Point<long> Plc = CtkPointTest::Pl;
    EXPECT_EQ(Plc.getX(),1);
    EXPECT_EQ(Plc.getY(),2);
    EXPECT_EQ(Plc.getZ(),3);

    ctk::Point<unsigned long> Pulc = CtkPointTest::Pul;
    EXPECT_EQ(Pulc.getX(),1);
    EXPECT_EQ(Pulc.getY(),2);
    EXPECT_EQ(Pulc.getZ(),3);

    ctk::Point<long long> Pllc = CtkPointTest::Pll;
    EXPECT_EQ(Pllc.getX(),1);
    EXPECT_EQ(Pllc.getY(),2);
    EXPECT_EQ(Pllc.getZ(),3);

    ctk::Point<unsigned long long> Pullc = CtkPointTest::Pull;
    EXPECT_EQ(Pullc.getX(),1);
    EXPECT_EQ(Pullc.getY(),2);
    EXPECT_EQ(Pullc.getZ(),3);

    ctk::Point<double> Pdc = CtkPointTest::Pd;
    EXPECT_EQ(Pdc.getX(),1.1);
    EXPECT_EQ(Pdc.getY(),2.1);
    //EXPECT_EQ(Pdc.getZ(),3.1);

}

/*TEST_F(CtkPointTest, Test_OperatorEqual){
    ctk::PointI Pic = CtkPointTest::Pi;
    EXPECT_EQ(CtkPointTest::Pi==CtkPointTest::Pi_2,false);
    EXPECT_EQ(CtkPointTest::Pi==Pic,true);

    ctk::PointD Pdc = CtkPointTest::Pd;
    EXPECT_EQ(CtkPointTest::Pd==CtkPointTest::Pd_2,false);
    EXPECT_EQ(CtkPointTest::Pd==Pdc,true);

}*/

TEST_F(CtkPointTest, Test_OperatorSum){
    ctk::PointI Pis = CtkPointTest::Pi + CtkPointTest::Pi_2;
    EXPECT_EQ(Pis.getX(),5);
    EXPECT_EQ(Pis.getY(),7);
    EXPECT_EQ(Pis.getZ(),6);

    ctk::PointD Pds = CtkPointTest::Pd + CtkPointTest::Pd_2;
    EXPECT_EQ(Pds.getX(),2.2);
    EXPECT_EQ(Pds.getY(),7.6);
    //EXPECT_EQ(Pds.getZ(),9.7);
}

TEST_F(CtkPointTest, Test_AdditionAssignement){
    ctk::PointI Pis(1,1,1);
    Pis+= CtkPointTest::Pi;
    EXPECT_EQ(Pis.getX(),2);
    EXPECT_EQ(Pis.getY(),3);
    EXPECT_EQ(Pis.getZ(),4);

    ctk::PointD Pds(2.1,1.2,3.3);
    Pds+= CtkPointTest::Pd;
    EXPECT_EQ(Pds.getX(),3.2);
    EXPECT_EQ(Pds.getY(),3.3);
    //EXPECT_EQ(Pds.getZ(),6.4);


}

TEST_F(CtkPointTest, Test_OperatorSubtraction){
    ctk::PointI Pis = CtkPointTest::Pi_2 - CtkPointTest::Pi;
    EXPECT_EQ(Pis.getX(),3);
    EXPECT_EQ(Pis.getY(),3);
    EXPECT_EQ(Pis.getZ(),0);

    ctk::PointD Pds = CtkPointTest::Pd_2 - CtkPointTest::Pd;
    EXPECT_EQ(Pds.getX(),0);
    EXPECT_EQ(Pds.getY(),3.4);
    //EXPECT_EQ(Pds.getZ(),3.5);
}

TEST_F(CtkPointTest, Test_SubtractionAssignement){
    ctk::PointI Pis(10,10,10);
    Pis -= CtkPointTest::Pi;
    EXPECT_EQ(Pis.getX(),9);
    EXPECT_EQ(Pis.getY(),8);
    EXPECT_EQ(Pis.getZ(),7);

    ctk::PointD Pds(10,10,10);
    Pds -= CtkPointTest::Pd;
    EXPECT_EQ(Pds.getX(),8.9);
    EXPECT_EQ(Pds.getY(),7.9);
    //EXPECT_EQ(Pds.getZ(),6.9);


}

TEST_F(CtkPointTest, Test_OperatorMultiplication){
    ctk::PointI Pim = CtkPointTest::Pi_2 * CtkPointTest::Pi;
    EXPECT_EQ(Pim.getX(),4);
    EXPECT_EQ(Pim.getY(),10);
    EXPECT_EQ(Pim.getZ(),9);

    ctk::PointD Pdm = CtkPointTest::Pd_2 * CtkPointTest::Pd;
   // EXPECT_EQ(Pdm.getX(),1.21);
    EXPECT_EQ(Pdm.getY(),11.55);
  //  EXPECT_EQ(Pdm.getZ(),20.46);
}

TEST_F(CtkPointTest, Test_MultiplicationAssignement){
    ctk::PointI Pim(2,2,2);
    Pim *= CtkPointTest::Pi;
    EXPECT_EQ(Pim.getX(),2);
    EXPECT_EQ(Pim.getY(),4);
    EXPECT_EQ(Pim.getZ(),6);

    ctk::PointD Pdm(2,2,2);
    Pdm *= CtkPointTest::Pd;
    EXPECT_EQ(Pdm.getX(),2.2);
    EXPECT_EQ(Pdm.getY(),4.2);
   // EXPECT_EQ(Pdm.getZ(),6.2);


}

TEST_F(CtkPointTest, Test_OperatorDivision){
    ctk::PointI Pix(2,4,6);
    ctk::PointI Pid = Pix /CtkPointTest::Pi ;
    EXPECT_EQ(Pid.getX(),2);
    EXPECT_EQ(Pid.getY(),2);
    EXPECT_EQ(Pid.getZ(),2);

    ctk::PointD Pdx(2,2,2);
    ctk::PointD Pdm = CtkPointTest::Pd / Pdx;
    EXPECT_EQ(Pdm.getX(),0.55);
    EXPECT_EQ(Pdm.getY(),1.05);
    //EXPECT_EQ(Pdm.getZ(),1.55);
}

TEST_F(CtkPointTest, Test_DivisionAssignement){
    ctk::PointI Pix(2,4,6);
    Pix /= CtkPointTest::Pi ;
    EXPECT_EQ(Pix.getX(),2);
    EXPECT_EQ(Pix.getY(),2);
    EXPECT_EQ(Pix.getZ(),2);

    ctk::PointD Pdx(2.2,4.2,6.2);
    Pdx /= CtkPointTest::Pd ;
    EXPECT_EQ(Pdx.getX(),2);
    EXPECT_EQ(Pdx.getY(),2);
    EXPECT_EQ(Pdx.getZ(),2);

}

TEST_F(CtkPointTest, Test_ManhattanLength){

    EXPECT_EQ( CtkPointTest::Pi.ManhattanLength(),3);
    EXPECT_EQ( CtkPointTest::Pd.ManhattanLength(),3);
}

TEST_F(CtkPointTest, Test_Norm){

    EXPECT_EQ(CtkPointTest::Pi.Norm(),std::sqrt(14));
    EXPECT_EQ(CtkPointTest::Pd.Norm(),std::sqrt(15.23));

}

TEST_F(CtkPointTest, Test_Inner){

    EXPECT_EQ(CtkPointTest::Pi.inner(CtkPointTest::Pi_2),23);
    EXPECT_EQ(CtkPointTest::Pd.inner(CtkPointTest::Pd_2),33.22);

}

TEST_F(CtkPointTest, Test_Outter){

    ctk::PointI outI = CtkPointTest::Pi.outter(CtkPointTest::Pi_2);
    EXPECT_EQ(outI.getX(),-9);
    EXPECT_EQ(outI.getY(),9);
    EXPECT_EQ(outI.getZ(),-3);

    /*ctk::PointD ouD = CtkPointTest::Pd.outter(CtkPointTest::Pd_2);
    EXPECT_EQ(ouD.getX(),-3.19);
    EXPECT_EQ(ouD.getY(),-3.85);
    EXPECT_EQ(ouD.getZ(),3.74);*/


}

TEST_F(CtkPointTest, Test_Distance){

   EXPECT_EQ(CtkPointTest::Pi.Distance(CtkPointTest::Pi_2),std::sqrt(18));
   //EXPECT_EQ(CtkPointTest::Pd.Distance(CtkPointTest::Pd_2),std::sqrt(23.81));

}

/**TEST_F(CtkPointTest, Test_Angle){


   EXPECT_EQ(CtkPointTest::Pi.Angle(CtkPointTest::Pi_1,CtkPointTest::Pi_2),std::acos(18));
   EXPECT_EQ(CtkPointTest::Pd.Angle(CtkPointTest::Pd_1,CtkPointTest::Pd_2),std::sqrt(23.81));

}*/

/*TEST_F(CtkPointTest, Test_Normalize){

   ctk::PointI norm = CtkPointTest::Pi_1.normalize();
   EXPECT_EQ(norm.getX(),1);
   EXPECT_EQ(norm.getY(),1);
   EXPECT_EQ(norm.getZ(),0);



}*/


#endif
