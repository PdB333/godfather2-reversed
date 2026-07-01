// FUNC_NAME: AICarBehavior::computeArrivalTime
float __fastcall AICarBehavior::computeArrivalTime(int thisPtr)
{
    // +0xc88 bit 11 (0x800) flag check, e.g. "isDriving" or "hasPath"
    if (!(*(uint *)(thisPtr + 0xc88) & 0x800) || !(*(int *)(DAT_0112af68 + 0x174))) {
        return s_fDefaultArrivalTime;  // DAT_00d756ec
    }

    float currentTime = getTimeSeconds();  // FUN_008fa190
    void* pVehicle = getPlayerVehicle();   // FUN_008f82b0

    float result;
    if (pVehicle == nullptr) {
        pVehicle = getAlternateVehicle();  // FUN_008f82d0
        result = s_fDefaultArrivalTime;    // DAT_00d756ec
    } else {
        float vehicleSpeed = (**(float (__thiscall **)(void*))(*(int*)pVehicle + 0x1b0))(pVehicle);  // vtable+0x1b0, getSpeed()
        float arrivalEstimate = vehicleSpeed + s_fSpeedOffset;  // DAT_00d75860
        result = currentTime;  // initial assignment
        if (arrivalEstimate <= currentTime) {
            // goto LAB_00860f03: result = arrivalEstimate (already)
        }
        result = arrivalEstimate;
    }

    if (pVehicle != nullptr) {
        int* pObjA = getEntityByIndex();  // FUN_00471610
        int* pObjB = getEntityByIndex();  // FUN_00471610
        int* pObjC = getEntityByIndex();  // FUN_00471610

        // Dot product: (pObjA forward) · (pObjB.position - pObjC.position)
        // Offsets: pObjA +0x20 = forward.x, +0x24 = forward.y, +0x28 = forward.z
        //            pObjB +0x30 = position.x, etc.
        float dot = (*(float*)(pObjA + 0x24) * (*(float*)(pObjB + 0x34) - *(float*)(pObjC + 0x34)) +
                     *(float*)(pObjA + 0x20) * (*(float*)(pObjB + 0x30) - *(float*)(pObjC + 0x30)) +
                     *(float*)(pObjA + 0x28) * (*(float*)(pObjB + 0x38) - *(float*)(pObjC + 0x38)));

        if (s_fDotThresholdGlobal < dot) {  // DAT_00d577a0
            result = s_fArrivalTimeOverride;  // DAT_00d7585c
        }
    }

    return result;
}