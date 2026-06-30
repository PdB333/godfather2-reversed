// FUNC_NAME: applyExponentialSmoothing
// Address: 0x005cda10
// One-pole low-pass filter applied to a byte stream with configurable strides and coefficient.
// Coefficient is a 15-bit fractional value (0-32767) controlling smoothing amount.
void __fastcall applyExponentialSmoothing(
    int sampleCount,
    int inputStride,
    uint8_t *output,
    const uint8_t *input,
    int outputStride,
    int coefficient
)
{
    // Initialize state with first input sample scaled to 16-bit fixed point
    int state = (uint)*input << 8;

    if (sampleCount != 0) {
        do {
            // Output current state's high byte
            *output = (uint8_t)((uint)state >> 8);

            // Read next input sample (at current input + inputStride)
            uint8_t nextSample = input[inputStride];
            input += inputStride;
            output += outputStride;

            // Update state: state += (nextSample*256 - state) * coefficient / 32768
            state = state + ((int)((uint)nextSample * 0x100 - state) * coefficient >> 0xf);

            --sampleCount;
        } while (sampleCount != 0);
    }
}