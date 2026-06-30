// FUNC_NAME: vec3Add
void __fastcall vec3Add(float* out, const float* a, const float* b) {
    float ay = a[1];
    float az = a[2];
    float aw = a[3];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];
    float outW = out[3];

    out[0] = a[0] + b[0];
    out[1] = ay + by;
    out[2] = az + bz;
    out[3] = aw + bw; // Restore original w component

    out[3] = outW; // Actually preserve the original out w, not the sum of w's
}