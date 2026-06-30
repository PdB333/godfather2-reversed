// FUNC_NAME: fsin_wrapper
// Function at 0x0064b6c0: Wrapper around fsin for extended precision float conversion.
// Takes a float argument and returns the sine using x87 fsin instruction, returning an 80-bit extended precision value.

float fsin_wrapper(float angle) {
    // The original uses unkbyte10 (80-bit extended float) internally.
    // The fsin instruction typically operates on x87 FPU stack with extended precision.
    long double result = fsin((long double)angle); // assuming fsin takes and returns long double
    return (float)result; // truncate back to float for compatibility
}