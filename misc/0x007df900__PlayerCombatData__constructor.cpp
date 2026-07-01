// FUNC_NAME: PlayerCombatData::constructor
uint* __thiscall PlayerCombatData::constructor(uint* thisPtr, uint param_2, uint param_3) {
    char isFlagSet;
    int deltaValue;
    uint minValue;

    // Call base Object/Entity constructor
    Object::constructor(param_2, param_3);
    *thisPtr = &PTR_LAB_00d6f87c; // vtable for PlayerCombatData
    *(thisPtr + 0x1f) = 0;        // +0x7c: some char flag, reset
    *(thisPtr + 0x7d) = 0;        // +0x1f4: some char flag, reset (cast to byte pointer)
    setFlag(1);                    // set a global/game flag to 1
    clearFlag(0);                  // clear a global/game flag to 0
    int* someComponent = thisPtr[0x16]; // +0x58: pointer to component/state struct
    thisPtr[0x1e] = 0;            // +0x78: some counter, reset
    thisPtr[0x1d] = DAT_01205224; // +0x74: default combat timer value

    // Bit checks on flags at offsets 0x8e0 and 0x8e8 of the component
    if ((*(uint*)(someComponent + 0x8e0) >> 1 & 1) == 0) { // bit 1 of flags0x8e0
        // Second block
        if ((*(uint*)(someComponent + 0x8e0) >> 0x19 & 1) == 0) goto LAB_007df9f3; // bit 25 not set -> skip
        deltaValue = isCombatEnabled(); // FUN_007ab1e0()
        if (deltaValue == 0) goto LAB_007df9f3;
        if ((*(uint*)(thisPtr[0x16] + 0x8e0) >> 0x1b & 1) == 0) { // bit 27 not set
            isFlagSet = isPlayerControlled(); // FUN_008a4380()
            if ((isFlagSet != 0) || (deltaValue = 1, (*(uint*)(thisPtr[0x16] + 0x249f) & 1) == 0)) {
                deltaValue = 400; // large delta
            }
        }
        else {
            deltaValue = 1; // minimal delta
        }
    }
    else { // bit 1 set
        if ((*(uint*)(someComponent + 0x8e0) >> 9 & 1) == 0) { // bit 9 not set
            // simple case
            someComponent = thisPtr[0x16];
            if ((*(uint*)(someComponent + 0x8e8) >> 2 & 1) == 0) goto LAB_007df9a0; // bit 2 of 0x8e8 not set -> jump
            // else fall through to increase
        }
        else { // bit 9 set
            isFlagSet = checkPlatform(3); // FUN_007ab500(3)
            if (isFlagSet == 0) goto simpleCase;
            int vehicleType = getVehicleType(); // FUN_007ab160()
            if ((*(byte*)(vehicleType + 4) & 0x80) == 0) goto simpleCase; // bit 7 of some offset
        }
        deltaValue = isCombatEnabled(); // FUN_007ab1e0()
        if (deltaValue == 0) goto LAB_007df9f3;
        deltaValue = computeCombatTimerIncrease(); // FUN_007df8c0()
    }
    thisPtr[0x1d] = thisPtr[0x1d] + deltaValue; // increase timer

LAB_007df9f3:
    minValue = getMinCombatTimer(); // FUN_007ab270()
    if ((uint)thisPtr[0x1d] < minValue) {
        thisPtr[0x1d] = minValue; // clamp to minimum
    }
    clearFlag(0); // FUN_007ab260(0) - clear flag again
    setGameplayEvent(0x28); // FUN_007f63e0(0x28) - e.g., threat/alert event
    setGameplayEvent(0x4c); // FUN_007f6420(0x4c) - e.g., combat start event
    setGameplayEvent(0x4d); // FUN_007f63e0(0x4d) - e.g., combat end event
    return thisPtr;
}