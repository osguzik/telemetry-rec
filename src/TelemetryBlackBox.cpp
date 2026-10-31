#include "TelemetryBlackBox.h"

#include <cstdint>
#include <iostream>

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

  history.put(frame);
}

uint32_t TelemetryBlackBox::getLastDataframe() {
  // empty history is treated the same as an invalid checksum
  if (history.empty()) {
    return 0xFFFFFFFF;
  }

  uint32_t frame = history.last();

  uint8_t frameChecksum = frame >> 24;
  uint8_t expectedChecksum = checksum(frame);
  if (frameChecksum != expectedChecksum) {
    return 0xFFFFFFFF;
  }

  uint32_t frameState = frame & 0x7;
  uint32_t frameParachute = (frame >> 3) & 1;
  uint32_t frameBaroError = (frame >> 4) & 1;
  uint32_t frameAltitude = (frame >> 8) & 0xFFFF;

  std::cout << "state=" << frameState << " parachute=" << frameParachute
            << " baro_error=" << frameBaroError << " altitude=" << frameAltitude
            << "\n";

  return frame;
}
