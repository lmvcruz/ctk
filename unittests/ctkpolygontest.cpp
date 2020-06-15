#include "ctkpolygontest.h"

#include "ctktestsetup.h"


void CtkPolygonTest::SetUp()
{
  p1_v1.setX(0);p1_v1.setY(0);
  p1_v2.setX(1);p1_v2.setY(0);
  p1_v3.setX(0);p1_v3.setY(1);
  p1_v4.setX(1);p1_v4.setY(1);

  p1cv_v1.x=0;  p1cv_v1.x=0;
  p1cv_v2.x=1;  p1cv_v2.x=0;
  p1cv_v3.x=0;  p1cv_v3.x=1;
  p1cv_v4.x=1;  p1cv_v4.x=1;


  ctk::Polygon Poly1(p1);
  ctk::Polygon Poly1_cv(p1cv);

  p2_v1.setX(2);p2_v1.setY(2);
  p2_v2.setX(5);p2_v2.setY(2);
  p1_v3.setX(2);p2_v3.setY(5);
  p2_v4.setX(5);p2_v4.setY(5);

  p2cv_v1.x=2;  p2cv_v1.x=2;
  p2cv_v2.x=5;  p2cv_v2.x=2;
  p2cv_v3.x=2;  p2cv_v3.x=5;
  p2cv_v4.x=5;  p2cv_v4.x=5;

  ctk::Polygon Poly2(p2);
  ctk::Polygon Poly2_cv(p2cv);



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

TEST_F(CtkPolygonTest,Test_ConstructorCopy){
    ctk::Polygon pol(CtkPolygonTest::Poly1);
    std::vector<ctk::PointD> data=Poly1.get_data();

    std::cout<<"t "<<data.size()<<"\n";


   // EXPECT_EQ(data.size(),4);
    //EXPECT_EQ(pol.get_cvdata(),p1cv);


}

#endif

#endif // TEST_POLYGON

