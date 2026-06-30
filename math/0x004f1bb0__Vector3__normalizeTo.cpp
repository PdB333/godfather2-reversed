// FUNC_NAME: Vector3::normalizeTo
void __fastcall Vector3::normalizeTo(Vector3* output)
{
    // input vector is 'this' (passed in ECX, referred by decompiler as in_EAX)
    float* input = reinterpret_cast<float*>(this);
    float x = input[0];
    float y = input[1];
    float z = input[2];

    // DAT_00e2cbe0 is likely a small squared epsilon (e.g., 1e-6)
    // DAT_00e2b1a4 is the target length factor (probably 1.0 for unit normalization)
    float lengthSq = x * x + y * y + z * z;
    if (lengthSq <= DAT_00e2cbe0) {
        output->x = 0.0f;
        output->y = 0.0f;
        output->z = 0.0f;
    } else {
        float scale = DAT_00e2b1a4 / sqrtf(lengthSq);
        output->x = x * scale;
        output->y = y * scale;
        output->z = z * scale;
    }
}