// FUNC_NAME: atanWrapper
long double atanWrapper(float x) {
    // Computes atan(x) via atan2(x, 1)
    return atan2l((long double)x, 1.0L);
}