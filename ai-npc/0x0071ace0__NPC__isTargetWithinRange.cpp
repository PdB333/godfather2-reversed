// FUNC_NAME: NPC::isTargetWithinRange
bool __thiscall NPC::isTargetWithinRange(NPC* this) {
    // +0x20: pointer to current target entity (NPC or Player)
    int* targetPtr = *(int**)((int)this + 0x20);
    if (targetPtr != nullptr) {
        // Global function returns pointer to player's transform structure
        // (offsets: +0x30 = x, +0x34 = y, +0x38 = z)
        int* playerTransform = (int*)FUN_00471610();
        
        float dx = *(float*)(targetPtr + 0x44) - *(float*)(playerTransform + 0x30);
        float dy = *(float*)(targetPtr + 0x48) - *(float*)(playerTransform + 0x34);
        float dz = *(float*)(targetPtr + 0x4c) - *(float*)(playerTransform + 0x38);
        
        // Squared distance check against global threshold (DAT_00d5f1a0)
        if (dx*dx + dy*dy + dz*dz < s_targetRangeThreshold) {
            return true;
        }
    }
    return false;
}