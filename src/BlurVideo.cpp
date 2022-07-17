#include "BlurCamBack/BlurVideo.hpp"

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

  cv::Mat blurImg{inputImg.size(), inputImg.type()};
  cv::GaussianBlur(inputImg, blurImg, blurKernelSize, 0);

  for (const auto &rect : faces) {
    inputImg(rect).copyTo(blurImg(rect));
  }

  return blurImg;
}

}  // namespace blur_cam_back
