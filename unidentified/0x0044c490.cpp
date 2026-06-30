// FUNC_ADDRESS: 0x0044c490 - Vector math: out = a + scale * b (4-component)
void vec4AddScaled(const float* a, const float* b, float scale, float* out) {
    out[0] = a[0] + scale * b[0];
    out[1] = a[1] + scale * b[1];
    out[2] = a[2] + scale * b[2];
    out[3] = a[3] + scale * b[3];
}