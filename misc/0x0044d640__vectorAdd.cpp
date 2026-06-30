// FUNC_NAME: vectorAdd
void vectorAdd(const float* a, const float* b, float* result) {
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];
    result[0] = a[0] + b[0];
    result[1] = a1 + b1;
    result[2] = a2 + b2;
    result[3] = a3 + b3;
}