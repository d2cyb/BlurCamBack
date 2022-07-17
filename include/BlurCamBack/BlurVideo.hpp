#ifndef BLUR_CAM_BACK_BLUR_VIDEO
#define BLUR_CAM_BACK_BLUR_VIDEO

#include <spdlog/spdlog.h>

#include <filesystem>
#include <memory>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <stdexcept>
#include <vector>

namespace blur_cam_back {

class BlurVideo {
 private:
  static const int frameSeconds{33};
  const std::string _windowName;
  const std::filesystem::path _classifierFilePath;
  const cv::Size blurKernelSize{101, 101};

 public:
  explicit BlurVideo(std::string&& windowName = "BlurVideo",
                     std::filesystem::path&& classifierFilePath =
                         "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")
      : _windowName(windowName), _classifierFilePath(classifierFilePath) {
  }

  auto blurBackground(int videoDeviceDescriptor = 0) -> void;

 private:
  auto blurFrameBackground(cv::CascadeClassifier& cascade, cv::Mat&& inputImg) -> cv::Mat;
};

}  // namespace blur_cam_back

#endif  // BLUR_CAM_BACK_BLUR_VIDEO
