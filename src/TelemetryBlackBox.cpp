#include "TelemetryBlackBox.h"

#include <cstdint>

void TelemetryBlackBox::onRocketStateChange(RocketState state) {
  currState = state;
}

void TelemetryBlackBox::onParachuteDeployed() { parachute = true; }

void TelemetryBlackBox::onBaroReading(bool error, uint16_t value) {
  baroError = error;
  altitude = value;
}

void TelemetryBlackBox::recordCurrentState() {}

uint32_t TelemetryBlackBox::getLastDataframe() {}
