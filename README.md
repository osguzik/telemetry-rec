# telemetry-rec

Telemetry recorder (black box). Packs state into 32-bit frames and stores the last 16 frames in a ring buffer.

## Build and run

```
cmake -S . -B build
cmake --build build
```

Run tests with CTest: `cd build && ctest`

Or run the test binary directly: `./build/tests`

## Structure

- `include/TelemetryBlackBox.h` - provided recorder API
- `include/RingBuffer.h` - ring buffer for frame history
- `src/TelemetryBlackBox.cpp` - frame encoding, checksum, and decoding
- `tests/` - GTest tests for both the recorder and the ring buffer

## Notes
- `getLastDataframe()` returns `0xFFFFFFFF` (just like an invalid checksum) if no frame was stored yet
- A barometer error in DISARM/LANDED state sets altitude to `0xFFFF` instead of zeroing it

## References
- [Creating a Circular Buffer in C and C++](https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/)
- [Quickstart: Building with CMake](https://google.github.io/googletest/quickstart-cmake.html) (GoogleTest)
