// FUNC_NAME: interpolateVectorWithConditionalSpeed
void __cdecl interpolateVectorWithConditionalSpeed(float* out, float* current, float* target, int* object)  
{  
    float speed = _DAT_00d6fa94; // normal interpolation speed (from dataset)  
    int someState = FUN_00800b10(); // likely checks if game is paused or in transition  

    // Condition A: if game state is active and bit 10 (0x400) set at offset 0x8e0 of object  
    // Condition B: if offset 0x30c0 is non-zero and not equal to 0x48  
    if ((someState != 0 && ((*(uint*)(object + 0x8e0) >> 0xa & 1) != 0)) ||  
        (*(int*)(object + 0x30c0) != 0 && *(int*)(object + 0x30c0) != 0x48))  
    {  
        speed = DAT_00d6fa90; // faster interpolation speed  
    }  

    // Linear interpolation: out = target * speed + current  
    out[0] = target[0] * speed + current[0];  
    out[1] = target[1] * speed + current[1];  
    out[2] = target[2] * speed + current[2];  
}