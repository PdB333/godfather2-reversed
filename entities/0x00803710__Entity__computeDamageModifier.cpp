// FUNC_NAME: Entity::computeDamageModifier
int __thiscall Entity::computeDamageModifier(int this, int hitData)
{
    int healthComponentPtr;
    uint3 upperBytes;
    int stateComponentBase;
    uint hitFlags;
    undefined8 statusResult;

    hitFlags = *(uint *)(hitData + 0x14); // +0x14: damage type flags
    healthComponentPtr = *(int *)(this + 0xff0); // +0xff0: pointer to health component
    if (healthComponentPtr == 0) {
        stateComponentBase = 0;
    }
    else {
        stateComponentBase = healthComponentPtr + -0x48; // adjust to base of health component structure
    }

    // Check if entity is active and has valid state and health components
    if (((((*(char *)(this + 0x1028) != '\0') && // +0x1028: isActive flag
          (healthComponentPtr = *(int *)(this + 0xffc), healthComponentPtr != 0)) && // +0xffc: pointer to state component
         (healthComponentPtr = healthComponentPtr + -0x48, healthComponentPtr != 0)) &&
        ((stateComponentBase != 0 &&
         (healthComponentPtr = *(int *)(this + 0xff0), healthComponentPtr != 0)))) &&
       (healthComponentPtr = healthComponentPtr + -0x48, healthComponentPtr != 0)) {
        statusResult = FUN_007f7c00(); // likely isPlayerControlled() or isInCombat()
        healthComponentPtr = (int)statusResult;
        if (((char)statusResult != '\0') &&
           ((healthComponentPtr = 0x100,
            (*(uint *)((int)((ulonglong)statusResult >> 0x20) + 0x490) & 0x100) != 0 || // check flag 0x100 on some object
            ((*(uint *)(stateComponentBase + 0x490) & 0x100) != 0)))) { // check flag 0x100 on state component
            return 0x101; // special hit result (critical/unique)
        }
    }

    // Extract upper 3 bytes of healthComponentPtr (which is now base of health component)
    upperBytes = (uint3)((uint)healthComponentPtr >> 8);
    healthComponentPtr = CONCAT31(upperBytes, 1); // set low byte to 1 (default multiplier?)
    if (DAT_00d71c38 <= (float)(hitFlags & DAT_00e44680)) { // compare threshold with masked hit flags
        healthComponentPtr = (uint)upperBytes << 8; // clear low byte (no multiplier)
    }
    return healthComponentPtr;
}