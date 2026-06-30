// FUNC_NAME: Utility::clampValueWithObject
float clampValueWithObject(int param1, int param2, int param3)
{
    float result;
    void** vtablePtr;          // +0xD0
    float local_cc;            // +0xCC
    float maxValue;            // +0xB0 (copied from global)
    int local_ac;              // +0xAC
    int local_a0;              // +0xA0
    int local_80;              // +0x80
    int isActive;              // +0x70
    char objectBuffer[92];     // +0x60 (size 0x5C)

    // Initialize internal state with the three parameters
    FUN_00542650(param1, param2, param3, 0x1000000, 0, 0);

    local_ac = -1;
    local_a0 = -1;
    vtablePtr = (void**)&PTR_FUN_00e32a8c; // vtable for temporary object
    isActive = 0;
    maxValue = _DAT_00d5780c;             // global maximum value
    local_80 = 0;
    local_cc = _DAT_00d5780c;
    FUN_009e5ed0(objectBuffer, &vtablePtr); // construct object in stack buffer
    result = _DAT_00d5780c;

    if (isActive != 0) {
        if (maxValue <= 0.0f) {
            return 0.0f;
        }
        if (_DAT_00d5780c <= maxValue) {
            return _DAT_00d5780c;
        }
        result = maxValue;
    }
    return result;
}