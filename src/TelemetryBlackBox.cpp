#include "TelemetryBlackBox.h"

#include <cstdint>

void TelemetryBlackBox::onRocketStateChange(RocketState state) {}

void TelemetryBlackBox::onParachuteDeployed() {}

void TelemetryBlackBox::onBaroReading(bool error, uint16_t value) {}

void TelemetryBlackBox::recordCurrentState() {}

uint32_t TelemetryBlackBox::getLastDataframe() {}
