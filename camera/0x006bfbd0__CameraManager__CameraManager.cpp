// FUNC_NAME: CameraManager::CameraManager
undefined4 * __thiscall CameraManager::CameraManager(undefined4 *this, undefined4 arg) {
    int *pCrewSlot;
    undefined4 uGlobalObject;
    int iGlobalData;
    float fVal1, fVal2, fVal3;
    // Base constructor call
    FUN_006d7020(arg);
    // Vtable setup
    *this = &PTR_FUN_00d5ee24;          // vtable pointer
    this[2] = &PTR_LAB_00d5ee1c;        // secondary vtable / base class subobject
    pCrewSlot = (int *)(this + 0x9c);   // +0x270: pointer to crew slot data?
    *pCrewSlot = 0;
    this[0x9d] = 0;                     // +0x274: integer field
    this[0x9e] = 0;                     // +0x278: integer field
    // Access a global pointer (e.g., game manager)
    iGlobalData = **(int **)(DAT_012233a0 + 4);
    // Check conditions (e.g., version flags, pointer validity)
    if (((iGlobalData != 0) && (iGlobalData != 0x1f30)) &&
        ((*(uint *)(iGlobalData + -0x1648) >> 0x1c & 1) != 0) &&
        (iGlobalData != -0x814)) {
        uGlobalObject = FUN_007e0d20();                // get some global object
        FUN_006bfa20(uGlobalObject);                   // init/register with that object
        if (*pCrewSlot != 0 && *pCrewSlot != 0x48) {  // check if slot is non-null and not invalid
            int iSlotData;
            if (*pCrewSlot == 0) {
                iSlotData = 0;
            } else {
                iSlotData = *pCrewSlot + -0x48;       // adjust offset
            }
            // Load two floats from a double (likely a Vector2 packed as double)
            fVal1 = (float)*(unsigned long long *)(iSlotData + 0x1a8);
            fVal2 = (float)((unsigned long long)*(unsigned long long *)(iSlotData + 0x1a8) >> 0x20);
            fVal3 = DAT_00e44564 - *(float *)(iSlotData + 0x1b0);
            // Reconstruct and call a math function
            // _local_c = CONCAT44(DAT_00e44564 - fVal2, DAT_00e44564 - fVal1);
            float localVals[2] = { DAT_00e44564 - fVal1, DAT_00e44564 - fVal2 };
            FUN_006d72a0(&localVals);  // e.g. vector subtraction or interpolation
        }
    }
    return this;
}