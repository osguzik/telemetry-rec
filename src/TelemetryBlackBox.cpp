#include "TelemetryBlackBox.h"

#include <cstdint>

namespace {

uint8_t checksum(uint32_t frame) {
  uint8_t byte0 = frame & 0xFF;
  uint8_t byte1 = (frame >> 8) & 0xFF;
  uint8_t byte2 = (frame >> 16) & 0xFF;
  return byte0 ^ byte1 ^ byte2;
}

} // namespace

void TelemetryBlackBox::onRocketStateChange(RocketState state) {
  currState = state;
}

void TelemetryBlackBox::onParachuteDeployed() { parachute = true; }

void TelemetryBlackBox::onBaroReading(bool error, uint16_t value) {
  baroError = error;
  altitude = value;
}

void TelemetryBlackBox::recordCurrentState() {
  uint16_t frameAltitude = altitude;
  if (currState == DISARM || currState == LANDED) {
    frameAltitude = 0;
  }
  if (baroError) {
    frameAltitude = 0xFFFF;
  }

  uint32_t frame = currState | (parachute << 3) | (baroError << 4) |
                   (uint32_t(frameAltitude) << 8);
  frame |= uint32_t(checksum(frame)) << 24;
}

uint32_t TelemetryBlackBox::getLastDataframe() {}
