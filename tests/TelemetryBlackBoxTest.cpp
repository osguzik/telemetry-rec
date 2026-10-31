#include "TelemetryBlackBox.h"

#include <cstdint>

#include <gtest/gtest.h>

TEST(TelemetryBlackBoxTest, EmptyHistory) {
  TelemetryBlackBox recorder;
  EXPECT_EQ(recorder.getLastDataframe(), 0xFFFFFFFF);
}

TEST(TelemetryBlackBoxTest, DisarmZeroAltitude) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(DISARM);
  recorder.onBaroReading(false, 500);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0x00000000);
}

TEST(TelemetryBlackBoxTest, Arm) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(ARM);
  recorder.onBaroReading(false, 500);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0xF401F401);
}

TEST(TelemetryBlackBoxTest, Flight) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(FLIGHT);
  recorder.onBaroReading(false, 1000);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0xE903E802);
}

TEST(TelemetryBlackBoxTest, FlightAfterWrap) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(FLIGHT);
  for (uint16_t altitude = 1; altitude <= 20; altitude++) {
    recorder.onBaroReading(false, altitude);
    recorder.recordCurrentState();
  }
  EXPECT_EQ((recorder.getLastDataframe() >> 8) & 0xFFFF, 20);
}

TEST(TelemetryBlackBoxTest, BaroErrorMaxAltitude) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(FLIGHT);
  recorder.onBaroReading(true, 1000);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0x12FFFF12);
}

TEST(TelemetryBlackBoxTest, Parachute) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(PARACHUTE);
  recorder.onParachuteDeployed();
  recorder.onBaroReading(false, 7000);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0x481B580B);
}

TEST(TelemetryBlackBoxTest, LandedZeroAltitude) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(LANDED);
  recorder.onBaroReading(false, 500);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0x04000004);
}

TEST(TelemetryBlackBoxTest, BaroErrorOverridesLanded) {
  TelemetryBlackBox recorder;
  recorder.onRocketStateChange(LANDED);
  recorder.onBaroReading(true, 500);
  recorder.recordCurrentState();
  EXPECT_EQ(recorder.getLastDataframe(), 0x14FFFF14);
}
