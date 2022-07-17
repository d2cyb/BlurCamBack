#include "BlurCamBack/BlurVideo.hpp"

#include <catch2/catch.hpp>
#include <stdexcept>

namespace bcb = blur_cam_back;
TEST_CASE("throw error on undefined video device descriptor", "[BlurVideo]") {
  bcb::BlurVideo bv{};

  SECTION("initialized") {
    REQUIRE(typeid(bv) == typeid(bcb::BlurVideo));
  }

  SECTION("blurBackground") {
    REQUIRE_THROWS_WITH(
      bv.blurBackground(INT_MAX),
      "Couldn't open video capture"
    );
  }
}
