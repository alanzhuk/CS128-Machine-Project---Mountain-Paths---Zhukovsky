#include "elevation_dataset.hpp"
#include <fstream>

ElevationDataset::ElevationDataset(const std::string& input, size_t width, size_t height) : width_(width), height_(height) {
    std::ifstream ifs(input);
    int max = 0;
    int min = kLarge;
    if (!ifs.is_open()) {
      throw std::runtime_error("");
    }
    for(unsigned int i = 0; i < height; i++) {
        std::vector<int> hold;
        for (unsigned int w = 0; w < width; w++) {
            hold.push_back(0);
        }
        data_.push_back(hold);
    }
    for(unsigned int i = 0; i < height_; i++) {
        for(unsigned int w = 0; w < width_; w++) {
            int read = 0;
            ifs >> read;
            if (ifs.fail()) {
                throw std::runtime_error("too little data in file or format read error");
            } 
            data_.at(i).at(w) = read;
            if (read > max) {
                max = read;
            }
            if (read < min) {
                min = read;
            }
        }
    }
    min_ele_ = min;
    max_ele_ = max;
    int i = 0;
    ifs >> i;
    if (ifs.good() || data_.size() != height_ || data_.at(0).size() != width_) {
        throw std::runtime_error("too much data");
    }
} 
size_t ElevationDataset::Width() const {
    return width_;
}
size_t ElevationDataset::Height() const {
    return height_;
}
int ElevationDataset::MaxEle() const{
    return max_ele_;
}
int ElevationDataset::MinEle() const {
    return min_ele_;
}
int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_[row][col];
}
const std::vector<std::vector<int> >& ElevationDataset::GetData() const {
    return data_;
}