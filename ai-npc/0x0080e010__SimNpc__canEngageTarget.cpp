// FUNC_NAME: SimNpc::canEngageTarget
int __fastcall SimNpc::canEngageTarget(SimNpc* this, float threshold) {
    int stateFlag; // result of FUN_0080d3f0
    int physicsBase; // derived from m_pPhysicsComponent
    uint adjustedAddrLow; // low byte of physicsBase address shifted
    float position[3]; // output of getPosition call

    stateFlag = FUN_0080d3f0(); // e.g., IsInCombatMode()
    FUN_00471610(); // e.g., GameTime::Update()
    // Call virtual getPosition on the position component at +0x50
    (*(void (__thiscall**)(float*))(*(int*)(this + 0x50) + 0x4c))(position);

    // Obtain physics component base: if m_pPhysicsComponent (+0x58) is null, physicsBase = 0;
    // otherwise, subtract 0x48 to get to the containing object (e.g., HavokVehicle)
    if (*(int*)(this + 0x58) == 0) {
        physicsBase = 0;
    } else {
        physicsBase = *(int*)(this + 0x58) - 0x48;
    }

    // Extract lower byte of physicsBase for return packing
    adjustedAddrLow = (uint)((uint)physicsBase >> 8) & 0xFF; // assuming uint3 cast means low byte

    // Check condition: health (at +0x194) <= threshold AND (global distance threshold < position.x OR stateFlag == 1)
    if ((*(float*)(physicsBase + 0x194) <= threshold) &&
        (DAT_00d58cbc < position[0] || stateFlag == 1)) {
        return (int)((adjustedAddrLow << 8) | 1); // Pack result: low byte of base addr + success flag
    }
    return (int)(adjustedAddrLow << 8); // Pack result: low byte only, failure
}