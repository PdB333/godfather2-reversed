// FUNC_NAME: isTimeWithinThreshold
bool __cdecl isTimeWithinThreshold(float currentTime, float previousTime) {
    float diff = currentTime - previousTime;
    uint maskedDiff = (uint)diff & timeMask; // 0x00e44680 - mask for time truncation
    float floatMasked = (float)maskedDiff;
    return floatMasked <= timeThreshold; // 0x00e2e210 - threshold for time difference
}