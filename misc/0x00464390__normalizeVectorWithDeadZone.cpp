// FUNC_NAME: normalizeVectorWithDeadZone

void __fastcall normalizeVectorWithDeadZone(float *out)
{
    float x = *in_EAX;
    float y = in_EAX[1];
    float lenSq = x * x + y * y;
    
    // Dead zone threshold (squared) - if magnitude is below this, output zero vector
    if (lenSq <= DAT_00e2cbe0) {
        lenSq = 0.0f;
    }
    else {
        // Scale factor to normalize to desired length (DAT_00e2b1a4)
        lenSq = DAT_00e2b1a4 / sqrtf(lenSq);
    }
    
    out[0] = lenSq * x;
    out[1] = lenSq * y;
}