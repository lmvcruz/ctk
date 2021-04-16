#include "ctk/image/rgb_image.h"

#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types_c.h>

#include "ctk/image/binary_image.h"
#include "ctk/image/gray_image.h"

namespace ctk {

/**
 * @brief RgbImage::RgbImage
 */
RgbImage::RgbImage() : ColorImage() {
    invert_channels = true;
}

/**
 * @brief RgbImage::RgbImage - Copy Construtor
 * @param that reference to an existing RgbImage
 */
RgbImage::RgbImage(const RgbImage &that) {
    if (that.data.type()!=CV_8UC3 || that.data.channels()!=3) throw  incompatible_parameters();
    type = that.type;
    ch_size = that.ch_size;
    invert_channels = true;
    data = that.data.clone();
}

/**
 * @brief RgbImage::RgbImage - Copy Construtor
 * @param that  reference to an existing AbstractImage
 */
RgbImage::RgbImage(const AbstractImage<cv::Vec3b> &that) {
    if (that.GetData().type() != CV_8UC3 || that.GetData().channels() != 3) {
        throw  incompatible_parameters();
    }
    type = CV_8UC3;
    ch_size = 3;
    invert_channels = true;
    data = that.GetData().clone();
}

/**
 * @brief RgbImage::RgbImage
 * @param d
 */
RgbImage::RgbImage(cv::Mat &d) : ColorImage(d) {
    if (d.type() != CV_8UC3 || d.channels() != 3) {
        throw  incompatible_parameters();
    }
}

/**
 * @brief RgbImage::Create - Create RgbImage
 * @param w  int representing the image width (number of columns)
 * @param h  int representing the image hight (number of rows)
 */
void RgbImage::Create(int w, int h) {
    // TODO evaluate if this method is really necessary (why does not inherit it)
    ColorImage::Create(w, h);
}

/**
 * @brief RgbImage::Fill  Fill all pixels in image with the passed rgb values
 * @param r int representing the red value
 * @param g int representing the green value
 * @param b int representing the blue value
 */
void RgbImage::Fill(int r, int g, int b) {
    //TODO: TEST
    if (r < 0 || r > 255) throw incompatible_parameters();
    if (g < 0 || g > 255) throw incompatible_parameters();
    if (b < 0 || b > 255) throw incompatible_parameters();
    data = cv::Scalar(r, g, b);
}

/**
 * @brief RgbImage::CreateAndFill Create RgbImage and fills all pixels
 * @param w  int representing the image width (number of columns)
 * @param h  int representing the image hight (number of rows)
 * @param r int representing the red value
 * @param g int representing the green value
 * @param b int representing the blue value
 */
void RgbImage::CreateAndFill(int w, int h, int r, int g, int b) {
    //TODO: TEST
    Create(w, h);
    Fill(r, g, b);
}

/**
 * @brief RgbImage::Set - Set value of image pixel
 * @param x int representing the column index
 * @param y int representing the row index
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::Set(int x, int y, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractMatrix<cv::Vec3b>::Set(x, y, cv::Vec3b(ucr, ucg, ucb));
}

/**
 * @brief RgbImage::SafeSet - Set value of image pixel
 * @param x int representing the column index
 * @param y int representing the row index
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::SafeSet(int x, int y, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractMatrix<cv::Vec3b>::SafeSet(x, y, cv::Vec3b(ucr, ucg, ucb));
}

/**
 * @brief RgbImage::SafeISet
 * @param i int representing the desired index in vector indices
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::SafeISet(int i, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractImage<cv::Vec3b>::SafeISet(i, cv::Vec3b(ucr, ucg, ucb));
}

/**
 * @brief RgbImage::Set
 * @param i int representing the desired index in vector indices
 * @param r int representing the desired red value
 * @param g int representing the desired green value
 * @param b int representing the desired blue value
 */
void RgbImage::Set(int i, int r, int g, int b) {
    unsigned char ucr = static_cast<unsigned char>(r);
    unsigned char ucg = static_cast<unsigned char>(g);
    unsigned char ucb = static_cast<unsigned char>(b);
    AbstractImage<cv::Vec3b>::ISet(i, cv::Vec3b(ucr, ucg, ucb));
}

/**
 * @brief RgbImage::Red Get red value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the red value of the pixel at (x,y)
 */
int RgbImage::Red(int x, int y) {
    return AbstractMatrix<cv::Vec3b>::Get(x, y)[0];
}

/**
 * @brief RgbImage::Green Get green value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the green value of the pixel at (x,y)
 */
int RgbImage::Green(int x, int y) {
    return AbstractMatrix<cv::Vec3b>::Get(x, y)[1];
}


/**
 * @brief RgbImage::Blue Get blue value of a pixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return int representing the blue value of the pixel at (x,y)
 */
int RgbImage::Blue(int x, int y) {
    return AbstractMatrix<cv::Vec3b>::Get(x, y)[2];
}

/**
 * @brief RgbImage::GetPixel
 * @param x int representing the row index
 * @param y int representing the column index
 * @return Point representing the pixel at (x,y)
 */
PointI RgbImage::GetPixel(int x, int y) {
    return PointI(Red(x, y), Green(x, y), Blue(x, y));
}

/**
 * @brief RgbImage::Quantize
 * @param q int representing the number of clusters for the kmeans algorithm
 * @param iter int representing the maximum number of iterations for the termination criteria in the kmeans algorithm
 * @param eps float representing the desired accuracy for the termination criteria in the kmeans algorithm
 * @param attempts int representing the number of times the kmeans algorithm is executed using different initial labellings
 * @param qtype int specifying the method of selecting the first centers
 * @return RgbImage obtained after kmeans clustering of original image
 */
RgbImage RgbImage::Quantize(int q, int iter, float eps, int attempts, int qtype) {
    RgbImage cluster(data);
    cv::Mat vals;
    cluster.data.convertTo(vals, CV_32F);
    vals = vals.reshape(1, vals.total());

    cv::Mat labels, centers;
    cv::TermCriteria crit(CV_TERMCRIT_ITER, iter, eps);
    kmeans(vals, q, labels, crit, attempts, qtype, centers);
    // reshape both to a single row of Vec3f pixels:
    centers = centers.reshape(3, centers.rows);
    vals = vals.reshape(3, vals.rows);
    // replace pixel values with their center value:
    cv::Vec3f *p = vals.ptr<cv::Vec3f>();
    for (size_t i = 0; i < vals.rows; ++i) {
       int center_id = labels.at<int>(i);
       p[i] = centers.at<cv::Vec3f>(center_id);
    }
    // back to 2d, and uchar:
    cluster.data = vals.reshape(3, cluster.data.rows);
    cluster.data.convertTo(cluster.data, CV_8U);
    cv::cvtColor(cluster.data, cluster.data, cv::COLOR_BGR2RGB);
    return cluster;
}

/**
 * @brief RgbImage::PickColor  Get binary mask for specified color
 * @param r int representing the red value
 * @param g int representing the green value
 * @param b int representing the blue value
 * @return BinaryImage consisting of a mask of the original image which is 1 for the passed color and 0 otherwise
 */
BinaryImage RgbImage::PickColor(int r, int g, int b) {
    BinaryImage mask;
    mask.Create(GetWidth(), GetHeight());
    for (auto x = 0; x < data.rows; ++x) {
        for (auto y = 0; y < data.cols; ++y) {
            if ((Red(x, y) == r) && (Green(x, y) == g) && (Blue(x, y) == b)) {
                mask.Set(x, y, true);
            } else {
                mask.Set(x, y, false);
            }
        }
    }
    return mask;
}

/**
 * @brief RgbImage::Project
 * @param colors vector of PointI where each element represents a color
 * @return GrayImage for each pixel in the original image assigns the index of the most similar color in the passed vector
 */
GrayImage RgbImage::Project(std::vector<PointI> &colors) {
    if (colors.size() > 256) throw incompatible_parameters();
    GrayImage mask;
    mask.Create(GetWidth(), GetHeight());
    for (auto x = 0; x < data.rows; ++x) {
        for (auto y = 0; y < data.cols; ++y) {
            int idx = -1;
            float dist = FLT_MAX;
            for (auto i = 0; i < colors.size(); ++i) {
                float d = colors[i].Distance(GetPixel(x, y));
                if (d < dist) {
                    dist = d;
                    idx = i;
                }
            }
            mask.Set(x, y, idx);
        }
    }
    return mask;
}

/**
 * @brief RgbImage::Contours Get image contours
 * @return vector of Polygons with the image contours
 */
std::vector<Polygon> RgbImage::Contours() {
    BinaryImage bin = ToGrayImage().ApplyOtsuThreshold();

    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.GetData(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);

    std::vector<Polygon> ctk_contours;
    ctk_contours.resize(cv_contours.size());
    for (auto i=0; i<cv_contours.size(); ++i) {
        ctk_contours[i] = cv_contours[i];
    }
    return ctk_contours;
}

/**
 * @brief RgbImage::ApproximateContours  Get approximate image contours
 * @param eps int specifying the approximation accuracy. The maximum distance between the original polygon and its approximation.
 * @return vector of Polygons with the approximate image contours
 */
std::vector<Polygon> RgbImage::ApproximateContours(int eps) {
    BinaryImage bin = ToGrayImage().ApplyOtsuThreshold();

    std::vector<std::vector<cv::Point> > cv_contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin.GetData(), cv_contours, hierarchy,
                     cv::RETR_TREE, cv::CHAIN_APPROX_TC89_KCOS);

    std::vector<Polygon> ctk_contours;
    ctk_contours.resize(cv_contours.size());
    for (auto i = 0; i < cv_contours.size(); ++i) {
        std::vector<cv::Point> approx;
        approxPolyDP(cv::Mat(cv_contours[i]), approx, eps, true);
        ctk_contours[i] = approx;
    }
    return ctk_contours;
}

//TODO: write tests and benchmark
/**
 * @brief RgbImage::Warp  Applies a perspective transformation to the image
 * @param pts  vector of PointD representing the coordinates of the points in the original plane
 * @param refs  vector of PointD representing the coordinates of the points in the target plane
 * @param w  int representing the width of the output image
 * @param h  int representing the hight of the output image
 * @return RgbImage resulting of the transformation
 */
RgbImage RgbImage::Warp(std::vector<PointD> &pts, std::vector<PointD> &refs, int w, int h) {
    if (pts.size() != refs.size()) throw  incompatible_parameters();
    if (pts.size() < 4) throw  incompatible_parameters();
    std::vector<cv::Point2f> cv_pts;
    cv_pts.resize(pts.size());
    std::vector<cv::Point2f> cv_refs;
    cv_refs.resize(refs.size());
    for (auto i = 0; i < pts.size(); ++i) {
        cv_pts[i].x = pts[i].GetX();
        cv_pts[i].y = pts[i].GetY();
        cv_refs[i].x = refs[i].GetX();
        cv_refs[i].y = refs[i].GetY();
    }
    cv::Mat homo_mat;
    // We assume that size>=4 (verified in the begining of the method)
    if (pts.size() > 4) {
        homo_mat = cv::findHomography(cv_pts, cv_refs,cv::RANSAC);
    } else {
        homo_mat = cv::findHomography(cv_pts, cv_refs);
    }
    //
    RgbImage rect;
    cv::warpPerspective(data, rect.GetData(), homo_mat, cv::Size(w,h));
    return rect;
}

/**
 * @brief RgbImage::ToGrayImage  convert to gray image
 * @return GrayImage
 */
GrayImage RgbImage::ToGrayImage() {
    GrayImage newImage;
    cv::cvtColor(data, newImage.GetData(), cv::COLOR_RGB2GRAY);
    return newImage;
}

/**
 * @brief RgbImage::DrawPolygon
 * @param pol  Polygon respresenting the contour to draw
 * @return RgbImage image with drawn contour
 */
RgbImage RgbImage::DrawPolygon(Polygon &pol) {
    std::vector<std::vector<cv::Point>> cv_conts;
    cv_conts.resize(1);
    cv_conts[0] = pol.GetCvData();
    std::cout << cv_conts[0].size() << " " << contourArea(cv_conts[0]) << std::endl;

    RgbImage new_img(data);
    cv::Mat &new_mat = new_img.GetData();
    const int kThickness = 2;
    const int kLineType = 8;
    cv::Scalar color = cv::Scalar(rand()%255, rand()%255, rand()%255);
    cv::drawContours(new_mat,cv_conts, 0, color, kThickness, kLineType);
    return new_img;
}

} // namespace ctk 
