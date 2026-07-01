// FUNC_NAME: SomeClass::updateSmoothedDistance  

void __thiscall SomeClass::updateSmoothedDistance(int thisPtr, float inputParam, float *outSquared, float *outOffset)  
{  
    float fVar1;  
    float fVar2;  
    float a;          // local_c  
    float b;          // local_8  
    byte scratch[4];  // local_4 – unused buffer  

    // Call a helper that computes some intermediate values and places them in a and b.  
    // The helper also returns a float (in fVar1).  
    fVar1 = (float)FUN_0083d270(scratch, &b, &inputParam, &a, inputParam, 0);  

    // Compute squared difference between a member variable (offset 0x6c) and the helper result.  
    fVar2 = *(float *)(thisPtr + 0x6c) - fVar1;  
    fVar2 = fVar2 * fVar2;  

    // Assign squared result, clamped to a minimum value (a).  
    *outSquared = fVar2;  
    if (fVar2 < a) {  
        *outSquared = a;  
    }  

    // Output offset = b + global constant (likely a tuning value).  
    *outOffset = b + _DAT_00d743fc;  

    return;  
}