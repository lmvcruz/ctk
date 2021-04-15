#include <iostream>
#include <vector>

#include "ctk/image/rgb_image.h"
#include "ctk/misc/filesys.h"

void processImage(ctk::RgbImage& img, int w, int h) {
    int iw = img.GetWidth();
    int ih = img.GetHeight();
    double expRatio = static_cast<double>(w) / static_cast<double>(h);
    double diw = static_cast<double>(iw);
    double dih = static_cast<double>(ih);
    double curRatio = diw / dih;
    int ox = 0;
    int oy = 0;
    int niw = iw;
    int nih = ih;
    if (curRatio >= expRatio) {
        niw = static_cast<int>(diw * expRatio / curRatio );
        ox = (iw - niw) / 2;
    } else {
        nih = static_cast<int>(dih * curRatio / expRatio );
        oy = (ih - nih) / 2;
    }
    img.SelfCrop(ox, oy, niw, nih);
    img = img.resize(w, h);
}

void createRegularMosaic(std::vector<std::string>& imgDb) {
    ctk::RgbImage aux;
    ctk::RgbImage mosaic;
    int cw = 300;
    int ch = 200;
    int gw = 4;
    int gh = 3;
    int fs = 10;
    mosaic.Create(fs + gw * (cw + fs), fs + gh * (ch + fs));
    mosaic.Fill(255, 255, 255);
    for (int cx = 0; cx < gw; ++cx) {
        int ox = fs + cx * (cw + fs);
        for (int cy = 0; cy < gh; ++cy) {
            int oy = fs + cy * (ch + fs);
            aux.Open(imgDb[cx * gw + cy]);
            processImage(aux, cw, ch);
            mosaic.CopyFrom(aux, ox, oy, 0, 0, cw, ch);
        }
    }
    mosaic.Save("test.png");
}

int main(int argc, char *argv[]) {
    std::vector<std::string> filters = {"png", "PNG", "jpg", "jpeg", "JPEG", "JPG"};
    std::vector<std::string> imgDb = 
                            ctk::listFilesContainingAnyExpressions(
                                        "../../../../imgdb/dogs", filters);
    createRegularMosaic(imgDb);
    return 0;
}
