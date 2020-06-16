#include "ctkpolygontest.h"

#include "ctktestsetup.h"


void CtkPolygonTest::SetUp()
{
  p1_v1.setX(0);p1_v1.setY(0);
  p1_v2.setX(1);p1_v2.setY(0);
  p1_v3.setX(0);p1_v3.setY(1);
  p1_v4.setX(1);p1_v4.setY(1);

  p1cv_v1.x=0;  p1cv_v1.y=0;
  p1cv_v2.x=1;  p1cv_v2.y=0;
  p1cv_v3.x=0;  p1cv_v3.y=1;
  p1cv_v4.x=1;  p1cv_v4.y=1;


  p2_v1.setX(2);p2_v1.setY(2);
  p2_v2.setX(5);p2_v2.setY(2);
  p2_v3.setX(2);p2_v3.setY(5);
  p2_v4.setX(5);p2_v4.setY(5);

  p2cv_v1.x=2;  p2cv_v1.y=2;
  p2cv_v2.x=5;  p2cv_v2.y=2;
  p2cv_v3.x=2;  p2cv_v3.y=5;
  p2cv_v4.x=5;  p2cv_v4.y=5;


  p1 = {p1_v1, p1_v2, p1_v3, p1_v4} ;
  p1cv = {p1cv_v1, p1cv_v2, p1cv_v3, p1cv_v4 };
  p2 = {p2_v1, p2_v2, p2_v3, p2_v4 };
  p2cv = {p2cv_v1, p2cv_v2, p2cv_v3, p2cv_v4 };


 /* ctk::Polygon Poly1(p1);
  ctk::Polygon Poly2(p2);
  ctk::Polygon Poly2_cv(p2cv);*/



}

CtkPolygonTest::CtkPolygonTest()
{
}

#ifdef TEST_POLYGON

#if 1

TEST_F(CtkPolygonTest, Test_Setup) {

    EXPECT_EQ(CtkPolygonTest::p1.size(),4);
    EXPECT_EQ(CtkPolygonTest::p1cv.size(),4);

    EXPECT_EQ(CtkPolygonTest::p2.size(),4);
    EXPECT_EQ(CtkPolygonTest::p2cv.size(),4);

}


TEST_F(CtkPolygonTest,Test_GetData){
    ctk::Polygon Poly1(CtkPolygonTest::p1);

    std::vector<ctk::PointD> Data = Poly1.get_data();
    EXPECT_EQ(Data[0].getX(),0);
    EXPECT_EQ(Data[0].getY(),0);
    EXPECT_EQ(Data[1].getX(),1);
    EXPECT_EQ(Data[1].getY(),0);
    EXPECT_EQ(Data[2].getX(),0);
    EXPECT_EQ(Data[2].getY(),1);
    EXPECT_EQ(Data[3].getX(),1);
    EXPECT_EQ(Data[3].getY(),1);


}

TEST_F(CtkPolygonTest,Test_GetCVData){
    ctk::Polygon Poly1(CtkPolygonTest::p1);

    std::vector<cv::Point> cvData = Poly1.get_cvdata();
    EXPECT_EQ(cvData[0].x,0);
    EXPECT_EQ(cvData[0].y,0);
    EXPECT_EQ(cvData[1].x,1);
    EXPECT_EQ(cvData[1].y,0);
    EXPECT_EQ(cvData[2].x,0);
    EXPECT_EQ(cvData[2].y,1);
    EXPECT_EQ(cvData[3].x,1);
    EXPECT_EQ(cvData[3].y,1);


}


TEST_F(CtkPolygonTest,Test_ConstructorPointD){
     ctk::Polygon Poly1(CtkPolygonTest::p1);

    EXPECT_EQ(Poly1.get_data().size(),4);
    EXPECT_EQ(Poly1.get_cvdata().size(),4);


}

TEST_F(CtkPolygonTest,Test_ConstructorCopy){
    ctk::Polygon Poly1(CtkPolygonTest::p1);

    ctk::Polygon polC(Poly1);
    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();


    EXPECT_EQ(Data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_EQ(Data[0].getX(),0);
    EXPECT_EQ(Data[0].getY(),0);
    EXPECT_EQ(Data[1].getX(),1);
    EXPECT_EQ(Data[1].getY(),0);
    EXPECT_EQ(Data[2].getX(),0);
    EXPECT_EQ(Data[2].getY(),1);
    EXPECT_EQ(Data[3].getX(),1);
    EXPECT_EQ(Data[3].getY(),1);

    EXPECT_EQ(cvData[0].x,0);
    EXPECT_EQ(cvData[0].y,0);
    EXPECT_EQ(cvData[1].x,1);
    EXPECT_EQ(cvData[1].y,0);
    EXPECT_EQ(cvData[2].x,0);
    EXPECT_EQ(cvData[2].y,1);
    EXPECT_EQ(cvData[3].x,1);
    EXPECT_EQ(cvData[3].y,1);




}

TEST_F(CtkPolygonTest,Test_OperatorCopyPolygon){

    ctk::Polygon Poly1(CtkPolygonTest::p1);
    ctk::Polygon polC=Poly1;

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();


    EXPECT_EQ(Data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_EQ(Data[0].getX(),0);
    EXPECT_EQ(Data[0].getY(),0);
    EXPECT_EQ(Data[1].getX(),1);
    EXPECT_EQ(Data[1].getY(),0);
    EXPECT_EQ(Data[2].getX(),0);
    EXPECT_EQ(Data[2].getY(),1);
    EXPECT_EQ(Data[3].getX(),1);
    EXPECT_EQ(Data[3].getY(),1);

    EXPECT_EQ(cvData[0].x,0);
    EXPECT_EQ(cvData[0].y,0);
    EXPECT_EQ(cvData[1].x,1);
    EXPECT_EQ(cvData[1].y,0);
    EXPECT_EQ(cvData[2].x,0);
    EXPECT_EQ(cvData[2].y,1);
    EXPECT_EQ(cvData[3].x,1);
    EXPECT_EQ(cvData[3].y,1);




}

TEST_F(CtkPolygonTest,Test_OperatorCopyPointD){

    ctk::Polygon polC=CtkPolygonTest::p1;

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();


    EXPECT_EQ(Data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_EQ(Data[0].getX(),0);
    EXPECT_EQ(Data[0].getY(),0);
    EXPECT_EQ(Data[1].getX(),1);
    EXPECT_EQ(Data[1].getY(),0);
    EXPECT_EQ(Data[2].getX(),0);
    EXPECT_EQ(Data[2].getY(),1);
    EXPECT_EQ(Data[3].getX(),1);
    EXPECT_EQ(Data[3].getY(),1);

    EXPECT_EQ(cvData[0].x,0);
    EXPECT_EQ(cvData[0].y,0);
    EXPECT_EQ(cvData[1].x,1);
    EXPECT_EQ(cvData[1].y,0);
    EXPECT_EQ(cvData[2].x,0);
    EXPECT_EQ(cvData[2].y,1);
    EXPECT_EQ(cvData[3].x,1);
    EXPECT_EQ(cvData[3].y,1);

}

TEST_F(CtkPolygonTest,Test_OperatorCopyCVPoint){

    ctk::Polygon polC=CtkPolygonTest::p1cv;

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();


    EXPECT_EQ(Data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_EQ(Data[0].getX(),0);
    EXPECT_EQ(Data[0].getY(),0);
    EXPECT_EQ(Data[1].getX(),1);
    EXPECT_EQ(Data[1].getY(),0);
    EXPECT_EQ(Data[2].getX(),0);
    EXPECT_EQ(Data[2].getY(),1);
    EXPECT_EQ(Data[3].getX(),1);
    EXPECT_EQ(Data[3].getY(),1);

    EXPECT_EQ(cvData[0].x,0);
    EXPECT_EQ(cvData[0].y,0);
    EXPECT_EQ(cvData[1].x,1);
    EXPECT_EQ(cvData[1].y,0);
    EXPECT_EQ(cvData[2].x,0);
    EXPECT_EQ(cvData[2].y,1);
    EXPECT_EQ(cvData[3].x,1);
    EXPECT_EQ(cvData[3].y,1);


}

TEST_F(CtkPolygonTest,Test_AddPointPointD){
    ctk::Polygon polC=CtkPolygonTest::p1cv;
    ctk::PointD n_point(2,3);

    polC.add_point(n_point);

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();

    EXPECT_EQ(Data.size(),5);
    EXPECT_EQ(cvData.size(),5);

    EXPECT_EQ(Data[4].getX(),2);
    EXPECT_EQ(Data[4].getY(),3);
    EXPECT_EQ(cvData[4].x,2);
    EXPECT_EQ(cvData[4].y,3);


}

TEST_F(CtkPolygonTest,Test_AddPointPointxy){
    ctk::Polygon polC=CtkPolygonTest::p1cv;

    polC.add_point(2,3);

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();

    EXPECT_EQ(Data.size(),5);
    EXPECT_EQ(cvData.size(),5);

    EXPECT_EQ(Data[4].getX(),2);
    EXPECT_EQ(Data[4].getY(),3);
    EXPECT_EQ(cvData[4].x,2);
    EXPECT_EQ(cvData[4].y,3);


}

TEST_F(CtkPolygonTest,Test_SetPointPointD){
    ctk::Polygon polC=CtkPolygonTest::p1cv;
    ctk::PointD n_point(2,3);

    polC.set_point(0,n_point);

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();

    EXPECT_EQ(Data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_EQ(Data[0].getX(),2);
    EXPECT_EQ(Data[0].getY(),3);
    EXPECT_EQ(cvData[0].x,2);
    EXPECT_EQ(cvData[0].y,3);


}

TEST_F(CtkPolygonTest,Test_SetPointPointxy){
    ctk::Polygon polC=CtkPolygonTest::p1cv;

    polC.set_point(0,2,3);

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();

    EXPECT_EQ(Data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_EQ(Data[0].getX(),2);
    EXPECT_EQ(Data[0].getY(),3);
    EXPECT_EQ(cvData[0].x,2);
    EXPECT_EQ(cvData[0].y,3);


}

TEST_F(CtkPolygonTest,Test_GetPoint){
    ctk::Polygon polC=CtkPolygonTest::p1cv;

   ctk::PointD point=polC.point(0);

    EXPECT_EQ(point.getX(),0);
    EXPECT_EQ(point.getY(),0);
}

TEST_F(CtkPolygonTest,Test_Resize){
    ctk::Polygon polC=CtkPolygonTest::p1cv;

    polC.Resize(6);

    std::vector<ctk::PointD> Data = polC.get_data();
    std::vector<cv::Point> cvData = polC.get_cvdata();

    EXPECT_EQ(Data.size(),6);
    EXPECT_EQ(cvData.size(),6);

    polC.Resize(2);

    std::vector<ctk::PointD> Data_1 = polC.get_data();
    std::vector<cv::Point> cvData_1 = polC.get_cvdata();

    EXPECT_EQ(Data_1.size(),2);
    EXPECT_EQ(cvData_1.size(),2);
}

TEST_F(CtkPolygonTest,Test_Size){
    ctk::Polygon polC=CtkPolygonTest::p1cv;

    EXPECT_EQ(polC.size(),4);
}

TEST_F(CtkPolygonTest,Test_Area){
    ctk::Polygon polC=CtkPolygonTest::p1cv;

    EXPECT_EQ(polC.Perimeter(),1);
}











#endif

#endif // TEST_POLYGON

