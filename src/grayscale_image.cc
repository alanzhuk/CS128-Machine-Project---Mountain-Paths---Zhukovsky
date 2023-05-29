#include "grayscale_image.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) : width_(dataset.Width()), height_(dataset.Height()){
    for (unsigned int i = 0; i < height_; i++) {
        std::vector<Color> hold;
        for (unsigned int w = 0; w < width_; w++) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                Color col(0,0,0);
                hold.push_back(col);
            } else {
                int grayscale = (int) std::round(static_cast<double>(dataset.DatumAt(i,w) - dataset.MinEle()) / static_cast<double>(dataset.MaxEle() - dataset.MinEle()) * static_cast<double>(kMaxColorValue));
                Color col(grayscale,grayscale,grayscale);
                hold.push_back(col);
            }
        }
        image_.push_back(hold);
    }
}
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) : width_(width), height_(height){
    ElevationDataset dataset(filename, width, height);
    for (unsigned int i = 0; i < height_; i++) {
        std::vector<Color> hold;
        for (unsigned int w = 0; w < width_; w++) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                Color col(0,0,0);
                hold.push_back(col);
            } else {
                double gray = dataset.DatumAt(i,w);
                int grayscale = (int) round(((gray - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle())) * kMaxColorValue);
                Color col(grayscale,grayscale,grayscale);
                hold.push_back(col);
            }
        }
        image_.push_back(hold);
    }
}
size_t GrayscaleImage::Width() const{
    return width_;
}
size_t GrayscaleImage::Height() const{
    return height_;
}
unsigned int GrayscaleImage::MaxColorValue() const{
    return kMaxColorValue;
}
const Color& GrayscaleImage::ColorAt(int row, int col) const{
    return image_[row][col];
}
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const{
    return image_;
}
void GrayscaleImage::ToPpm( const std::string& name ) const{
    std::ofstream ofs(name);
    if (!ofs.is_open()) {
        throw std::runtime_error("output file didn't open");
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
    for (unsigned int i = 0; i < height_; i++) {
        for (unsigned int w = 0; w < width_; w++) {
            Color hold = image_[i][w];
            ofs << hold.Red() << " " << hold.Green() << " " << hold.Blue() << " ";
        }
        ofs << std::endl;
    }
}