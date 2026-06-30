// FUNC_NAME: ComputeClampedFloatFromGlobal
float __cdecl ComputeClampedFloatFromGlobal(uint param_1, uint param_2, uint param_3)
{
    // Local variables
    float result;               // local_d4
    void** vtablePtr;           // local_d0, points to some global function table
    float local_cc;             // unused? initialized but not used
    float clampValue;           // local_b0, initial clamp threshold
    uint local_ac;              // set to 0xFFFFFFFF, not used
    uint local_a0;              // set to 0xFFFFFFFF, not used
    uint local_80;              // set to 0, not used
    int conditionFlag;          // local_70, initially 0
    char buffer[92];            // local_60, work buffer

    // Call some global initialization function (e.g., fetch game state)
    FUN_00542650(param_1, param_2, param_3, 0x1000000, 0, 0);

    local_ac = 0xFFFFFFFF;
    local_a0 = 0xFFFFFFFF;
    vtablePtr = &PTR_FUN_00e32a8c;   // pointer to a vtable or function table
    conditionFlag = 0;                // reset condition
    clampValue = _DAT_00d5780c;       // global float (e.g., max clamp)
    local_80 = 0;
    local_cc = _DAT_00d5780c;         // also global

    // Call a function that may modify vtablePtr or buffer
    FUN_009e5ed0(buffer, &vtablePtr);

    result = _DAT_00d5780c;           // default result is global value

    // If conditionFlag was set (e.g., by FUN_009e5ed0 via pointer manipulation),
    // clamp the result between 0 and clampValue
    if (conditionFlag != 0)
    {
        if (clampValue <= 0.0f)
        {
            return 0.0f;
        }
        if (_DAT_00d5780c <= clampValue)
        {
            return _DAT_00d5780c;
        }
        result = clampValue;
    }

    return result;
}