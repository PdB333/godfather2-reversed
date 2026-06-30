// FUNC_NAME: normalizeVectorToFixedMagnitude
// Function at 0x004bd430: Scales a 4-component float vector such that the magnitude of the first three components becomes DAT_00e2b1a4 (a global constant). The fourth component is scaled proportionally.
void normalizeVectorToFixedMagnitude(float* vec) {
    float scale = DAT_00e2b1a4 / sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    vec[0] *= scale;
    vec[1] *= scale;
    vec[2] *= scale;
    vec[3] *= scale;
}