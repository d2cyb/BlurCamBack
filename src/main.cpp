#include <spdlog/spdlog.h>

#include <span>

#include "BlurCamBack/BlurVideo.hpp"

using std::runtime_error;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  spdlog::set_level(spdlog::level::debug);

  try {
    auto args = std::span(argv, static_cast<size_t>(argc));

    spdlog::debug("Camera with blur background");
    blur_cam_back::BlurVideo bv{};
    bv.blurBackground();

  } catch (const runtime_error &err) {
    spdlog::error("Undefined type error {}", err.what());
  } catch (const std::exception &error) {
    spdlog::error("Exercises error {}", error.what());
  } catch (...) {
    spdlog::error("Undefined type error");
  }

  return 0;
}
