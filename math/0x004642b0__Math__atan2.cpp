// FUNC_NAME: Math::atan2
float Math::atan2(float y, float x) {
    return fpatan((float10)y, (float10)x); // fpatan likely computes atan2 with extended precision
}