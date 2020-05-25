#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iomanip>

#include <QCoreApplication>
#include <QProcess>
#include <QDir>

#include "ctkimage.h"
#include "videogenerator.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "Oi" << std::endl;
    ctk::RgbImage img;
    img.Open("../../ctk/data/general/rgb_img.jpg");
    std::cout << img.rows() << std::endl;
    ctk::RgbImage frame;
    for (int i=0; i<100; i++) {
        std::ostringstream out;
        out << std::setw(3) << std::setfill('0') << i;
        std::string filename = "out/" + out.str() + ".png";
        std::cout << filename << std::endl;
        //
        int opt = std::rand() % 7;
        switch (opt) {
        case 0: {
            frame = img.FlipHorizontally();
            break;
        }
        case 1: {
            frame = img.FlipVertically();
            break;
        }
        case 2: {
            frame = img.FlipBoth();
            break;
        }
        case 3: {
            frame = img.Rotate90();
            break;
        }
        case 4: {
            frame = img.Rotate180();
            break;
        }
        case 5: {
            frame = img.Rotate270();
            break;
        }
        case 6: {
            frame = img;
            break;
        }
        default: {
            frame = img;
        }
        }
        frame = frame.resize(640, 480);
        frame.Save(filename);
    }
    //
    VideoGenerator video;
    video.run();
    video.showReport();
    return 0;
}
