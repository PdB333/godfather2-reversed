// FUNC_NAME: Entity::checkDistanceCondition
uint __thiscall Entity::checkDistanceCondition(uint param_1, int target, bool checkInside, float radius) {
    byte bVar1;
    uint uVar2;
    int iVar3;
    int iVar4;
    float fVar6;
    float fVar7;
    float fVar8;

    // Get global game state flags (e.g., from GameManager)
    uVar2 = GetGlobalStateFlags();
    
    // Check a flag on the target at offset +0x78 (likely a bitfield)
    bVar1 = *(byte *)(target + 0x78) >> 2; // shift to get bit2's status in LSB
    // Combine global flags with this target flag byte
    uVar2 = (uVar2 & 0xFFFFFF00) | bVar1; // CONCAT31(uVar2>>8, bVar1) is equivalent
    
    // If target bit2 is set and additional condition (maybe line-of-sight) passes
    if (((bVar1 & 1) != 0) && (CheckCondition(param_1, target) != '\0')) {
        // Get two transform pointers (possibly this object and target)
        iVar3 = GetTransform();  // Could be this->getTransform()
        iVar4 = GetTransform();  // Could be target->getTransform()
        
        // Compute squared distance between positions (+0x30 = x, +0x34 = y, +0x38 = z)
        fVar6 = *(float *)(iVar3 + 0x30) - *(float *)(iVar4 + 0x30);
        fVar7 = *(float *)(iVar3 + 0x34) - *(float *)(iVar4 + 0x34);
        fVar8 = *(float *)(iVar3 + 0x38) - *(float *)(iVar4 + 0x38);
        fVar6 = fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6;  // squared distance
        
        // Save the upper 24 bits of current uVar2 (global state flags)
        uint upperBits = uVar2 & 0xFFFFFF00;
        
        if (checkInside == false) {
            // Check if distance is greater than radius (outside check)
            if (radius * radius < fVar6) {
                return upperBits | 1;  // Set LSB to 1 (success)
            }
        } else {
            // Check if distance is less than radius (inside check)
            if (fVar6 < radius * radius) {
                return upperBits | 1;
            }
        }
    }
    
    // Return global flags with LSB cleared (failure or not evaluated)
    return uVar2 & 0xFFFFFF00;
}