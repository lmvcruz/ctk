#include <iostream>
#include <vector>

#include "ctk/image/rgb_image.h"
#include "ctk/misc/filesys.h"

void copyImage(ctk::RgbImage& mosaic, ctk::RgbImage& that, 
               int ox, int oy, int w, int h) 
{
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            mosaic.set(ox + x, oy + y, that.get(x, y));
        }
    }
} 

void createMosaic() {
    std::vector<std::string> filters = {"png", "PNG", "jpg", "jpeg", "JPEG", "JPG"};
    std::vector<std::string> files = ctk::listFilesContainingAnyExpressions(
                                            "../../../../imgdb/dogs",
                                            filters);
    //
    ctk::RgbImage mosaic;
    int cs = 300;
    int gs = 3;
    int fs = 3;
    std::cout << fs + gs * (cs + fs) << " " << fs + gs * (cs + fs) << std::endl;
    mosaic.Create(fs + gs * (cs + fs), fs + gs * (cs + fs));
    mosaic.Fill(255, 255, 255);
    for (int cx = 0; cx < gs; ++cx) {
        for (int cy = 0; cy < gs; ++cy) {
            int ox = fs + cx * cs;
            int oy = fs + cy * cs;
            ctk::RgbImage that;
            std::cout << files[cx * gs + cy] << std::endl;
            that.Open(files[cx * gs + cy]);
            that = that.resize(cs, cs);
            copyImage(mosaic, that, ox, oy, cs, cs);
        }
    }
    mosaic.Save("test.png");
}

int main(int argc, char *argv[]) {
    createMosaic();
    return 0;
}
