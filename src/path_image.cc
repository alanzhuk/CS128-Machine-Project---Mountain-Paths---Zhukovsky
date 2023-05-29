#include "path_image.hpp"
#include <fstream>
/*std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;*/
int Abs (int input) {
    if (input < 0) {
        return input * -1;
    }
    return input;
}
void PathImage::GreenPaint(unsigned int index) {
    for(unsigned int i = 0; i < paths_[index].Length(); i++) {
        path_image_[paths_[index].GetPath()[i]][i] = Color(kGreenOne,kGreenTwo, kGreenThree);
    }
}
PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) : width_(image.Width()), height_(image.Height()){
    path_image_ = image.GetImage();
    unsigned int index = 0;
    unsigned int min = kLarge;
    for (unsigned int i = 0; i < height_; i++) {
        Path hold(width_, i); int last = dataset.DatumAt(i,0); path_image_[i][0] = Color(kRedOne,kRedTwo,kRedThree); unsigned int row = i;
        for (unsigned int w = 1; w < width_; w++) {
            int plus = kLarge;
            int minus = kLarge;
            int straight = Abs(last - dataset.DatumAt(row,w));
            if (row != 0) {
                minus = Abs(last - dataset.DatumAt(row - 1,w));
            }
            if (row != height_ - 1) {
                plus = Abs(last - dataset.DatumAt(row + 1,w));
            }
            if (straight <= plus && straight <= minus) {
                hold.IncEleChange(straight);
                hold.SetLoc(w, row);
                path_image_[row][w] = Color(kRedOne,kRedTwo,kRedThree);
            } else if (plus <= minus) {
                hold.IncEleChange(plus);
                hold.SetLoc(w, row + 1);
                path_image_[row + 1][w] = Color(kRedOne,kRedTwo,kRedThree);
                row++;
            } else {
                hold.IncEleChange(minus);
                hold.SetLoc(w, row - 1);
                path_image_[row - 1][w] = Color(kRedOne,kRedTwo,kRedThree);
                row--;
            }
            last = dataset.DatumAt(row, w);
        }
        if (hold.EleChange() < min) {
            min = hold.EleChange();
            index = i;
        }
        paths_.push_back(hold);
    }
    GreenPaint(index);
}
size_t PathImage::Width() const{
    return width_;
}
size_t PathImage::Height() const{ 
    return height_;
}
unsigned int PathImage::MaxColorValue() const{
    return kMaxColorValue;
}
const std::vector<Path>& PathImage::Paths() const{
    return paths_;
}
const std::vector<std::vector<Color> >&  PathImage::GetPathImage() const{
    return path_image_;
}
void PathImage::ToPpm(const std::string& name) const{
    std::ofstream ofs(name);
    if (!ofs.is_open()) {
        throw std::runtime_error("output file didn't open");
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
    for (unsigned int i = 0; i < height_; i++) {
        for (unsigned int w = 0; w < width_; w++) {
            Color hold = path_image_.at(i).at(w);
            ofs << hold.Red() << " " << hold.Green() << " " << hold.Blue() << " ";
        }
        ofs << std::endl;
    }
}