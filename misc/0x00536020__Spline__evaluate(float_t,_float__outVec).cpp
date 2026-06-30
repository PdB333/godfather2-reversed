// FUNC_NAME: Spline::evaluate(float t, float* outVec)
void __fastcall Spline::evaluate(float t, float* outVec) // param_1 unused (ecx)
{
    // Evaluate X component
    float* keysX = *(float**)(this + 0x18);
    if (*keysX <= t) {
        // t >= first key
        int countX = *(int*)(this + 0x10);
        if (t < keysX[countX - 1]) {
            // t is within range, search for segment
            int i = 0;
            float* pKey = keysX;
            while (i < countX) {
                if (t < pKey[1]) {
                    // found segment; compute local t
                    float localT = t - keysX[i];
                    float* coeffs = (float*)(*(int*)(this + 0x14) + i * 0x10); // 4 floats per segment
                    outVec[0] = ((coeffs[0] * localT + coeffs[1]) * localT + coeffs[2]) * localT + coeffs[3];
                    break;
                }
                i++;
                pKey++;
            }
            if (i >= countX) {
                outVec[0] = 0.0f;
            }
        } else {
            // t >= last key -> use last value
            float* vals = *(float**)(this + 0x1c);
            outVec[0] = vals[countX - 1];
        }
    } else {
        // t < first key -> use first value
        float* vals = *(float**)(this + 0x1c);
        outVec[0] = vals[0];
    }

    // Evaluate Y component
    float* keysY = *(float**)(this + 0x28);
    if (*keysY <= t) {
        int countY = *(int*)(this + 0x20);
        if (t < keysY[countY - 1]) {
            int i = 0;
            float* pKey = keysY;
            while (i < countY) {
                if (t < pKey[1]) {
                    float localT = t - keysY[i];
                    float* coeffs = (float*)(*(int*)(this + 0x24) + i * 0x10);
                    outVec[1] = ((coeffs[0] * localT + coeffs[1]) * localT + coeffs[2]) * localT + coeffs[3];
                    break;
                }
                i++;
                pKey++;
            }
            if (i >= countY) {
                outVec[1] = 0.0f;
            }
        } else {
            float* vals = *(float**)(this + 0x2c);
            outVec[1] = vals[countY - 1];
        }
    } else {
        float* vals = *(float**)(this + 0x2c);
        outVec[1] = vals[0];
    }

    // Evaluate Z component
    float* keysZ = *(float**)(this + 0x38);
    if (*keysZ <= t) {
        int countZ = *(int*)(this + 0x30);
        if (t < keysZ[countZ - 1]) {
            int i = 0;
            float* pKey = keysZ;
            while (i < countZ) {
                if (t < pKey[1]) {
                    float localT = t - keysZ[i];
                    float* coeffs = (float*)(*(int*)(this + 0x34) + i * 0x10);
                    outVec[2] = ((coeffs[0] * localT + coeffs[1]) * localT + coeffs[2]) * localT + coeffs[3];
                    break;
                }
                i++;
                pKey++;
            }
            if (i >= countZ) {
                outVec[2] = 0.0f;
            }
        } else {
            float* vals = *(float**)(this + 0x3c);
            outVec[2] = vals[countZ - 1];
        }
    } else {
        float* vals = *(float**)(this + 0x3c);
        outVec[2] = vals[0];
    }
}