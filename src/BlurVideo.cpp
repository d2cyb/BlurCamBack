#include "BlurCamBack/BlurVideo.hpp"

#include <stdexcept>

namespace blur_cam_back {

auto BlurVideo::blurBackground(int videoDeviceDescriptor) -> void {
  auto cascade = cv::CascadeClassifier(_classifierFilePath.string());
  cv::VideoCapture cap;

  cap.open(videoDeviceDescriptor);

  if (!cap.isOpened()) {
    std::string errorOpenVideoCapture{"Couldn't open video capture"};
    throw std::runtime_error(errorOpenVideoCapture);
  }

  cv::Mat frame;
  cv::Mat frameBlur;
  for (;;) {
    cap >> frame;
    if (frame.empty()) {
      break;
    }

    frameBlur = blurFrameBackground(cascade, std::move(frame));

    cv::imshow(_windowName, frameBlur);

    if (cv::waitKey(BlurVideo::frameSeconds) >= 0) {
      break;
    }
  }
}

auto BlurVideo::blurFrameBackground(cv::CascadeClassifier &cascade, cv::Mat &&inputImg) -> cv::Mat {
  std::vector<cv::Rect> faces{};
  cascade.detectMultiScale(inputImg, faces);
  cv::Size windowSize{101, 101};

  cv::Mat blur{inputImg.size(), inputImg.type()};
  cv::Mat roiColor;
  for (const auto &rect : faces) {
    cv::Rect roiRect = cv::Rect(rect.y, rect.y, rect.width, rect.height);
    cv::GaussianBlur(inputImg(roiRect), inputImg(roiRect), windowSize, 0);
  }

  return inputImg;
}

}  // namespace blur_cam_back
