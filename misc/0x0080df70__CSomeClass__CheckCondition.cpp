// FUNC_NAME: CSomeClass::CheckCondition
int __fastcall CSomeClass::CheckCondition(int thisPtr) {
    float vPos[3];
    // This call might initialize some state or profiling data
    SomeInitializationFunction();

    // Get position from sub-object at +0x50 via vtable offset 0x4c
    // The sub-object is likely a TransformComponent or similar
    (*(void (__thiscall **)(float*))(**(int**)(thisPtr + 0x50) + 0x4c))(vPos);

    bool bXThreshold = vPos[0] < g_fThresholdX; // Global threshold at 0x00d64cc0

    int someObj = GetSomeObjectPointer(); // e.g., Player or Sim from FUN_00471610

    // The pointer at +0x58 points to a sub-object embedded inside a parent struct at offset -0x48
    int parent1 = (*(int*)(thisPtr + 0x58) != 0) ? *(int*)(thisPtr + 0x58) - 0x48 : 0;
    int parent2 = (*(int*)(thisPtr + 0x58) != 0) ? *(int*)(thisPtr + 0x58) - 0x48 : 0; // same as parent1

    // High 24 bits of parent pointer (used as an identifier)
    unsigned int packedID = (unsigned int)(parent2 >> 8);

    // Condition: someObj->field_0x34 <= parent1->field_0x1a0 + parent2->field_0x1c0
    if (*(float*)(someObj + 0x34) <= *(float*)(parent1 + 0x1a0) + *(float*)(parent2 + 0x1c0) &&
        // The OR condition uses the high byte of EBX (passed from caller)
        (bXThreshold || ((char)(register_EBX >> 24) != (char)bXThreshold))) { // simplified to bXThreshold || (register_EBX & 0xFF000000)
        // Return packed value: high 24 bits from parent pointer, LSB set to 1
        return (packedID << 8) | 1;  // CONCAT31(packedID, 1)
    } else {
        // Return packed value: high 24 bits from parent pointer, LSB set to 0
        return (packedID << 8);      // (uint)packedID << 8
    }
}