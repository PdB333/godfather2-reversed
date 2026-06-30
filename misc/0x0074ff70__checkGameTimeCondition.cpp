// FUNC_NAME: checkGameTimeCondition

extern void* __fastcall getGlobalTimeStruct();       // FUN_00471610 - likely returns pointer to a time manager singleton
extern float __fastcall computeTimeDelta(void* param1, void* param2, void* param3, float* param4); // FUN_004a0b00 - computes a float time delta or condition

extern float g_timeDeltaOffset;     // DAT_00d648f8 - some offset/constant used in time calculation
extern float g_timeThreshold;       // DAT_00d64924 - threshold compared against computed result

bool __fastcall checkGameTimeCondition(void* thisPtr)
{
    // Dereference two-level pointer: this+0x110 -> +0x24cc
    void* subObj = *(void**)((uint8_t*)thisPtr + 0x110);   // some sub-object or manager
    int state = *(int*)((uint8_t*)subObj + 0x24cc);         // state or ID at offset 0x24cc

    // Only proceed if state is not 0 and not 0x48 (likely special flags)
    if (state == 0 || state == 0x48)
        return false;

    // Get first time structure
    void* t1 = getGlobalTimeStruct();
    uint32_t time1_low = *(uint32_t*)((uint8_t*)t1 + 0x30); // low 32 bits of a 64-bit value at +0x30

    // Get second time structure
    void* t2 = getGlobalTimeStruct();
    uint32_t time2_low = *(uint32_t*)((uint8_t*)t2 + 0x30); // low 32 bits of a 64-bit value at +0x30

    // Get third time structure (used for additional parameter)
    void* t3 = getGlobalTimeStruct();

    // Compute a float result from the times and global offset
    float result = computeTimeDelta(&time2_low, (uint8_t*)t3 + 0x20, &time1_low, &g_timeDeltaOffset);

    // If result >= threshold, condition is met
    if (g_timeThreshold <= result)
        return true;

    return false;
}