#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <string>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
private:
  void GreenPaint(unsigned int index);
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  static const int kLarge = 2147483647;
  static const int kRedOne = 252;
  static const int kRedTwo = 25;
  static const int kRedThree = 63;
  static const int kGreenOne = 31;
  static const int kGreenTwo = 253;
  static const int kGreenThree = 13;
};

#endif