// FUNC_NAME: AnimationBlendController::updateBlendFactor
void AnimationBlendController::updateBlendFactor(float param) {
    // +0x0c: flags (uint32) - bit 0x10000 indicates "disabled" or "locked"
    if ((this->flags & 0x10000) != 0) {
        return;
    }

    float currentBlend = this->blendValue;  // +0x90
    // Global hysteresis thresholds
    // DAT_00e4483c = maybe blendSpeedFactor, DAT_00e2b334 = blendDeadZone
    float lowerBound = currentBlend - currentBlend * DAT_00e2b334;
    float upperBound = currentBlend * DAT_00e4483c;

    if ((param < lowerBound) || (param > upperBound)) {
        // Need to update state for each slot in the blend set
        short numSlots = this->numSlots;  // +0x80 (short)
        int slotIndex = 0;
        // Each slot has a 20-byte (5 uint32) flag/state block beginning at +0xf0
        uint32_t* slotFlags = reinterpret_cast<uint32_t*>(this + 0xf0);
        // Each slot also references an external object array at +0x10
        ExternalObject* objArray = this->objectArray;  // +0x10

        for (int i = 0; i < numSlots; i++) {
            int objIndex = i * 0x24; // Each external object size is 0x24 bytes
            ExternalObject* obj = &objArray[i]; // But using index in bytes?

            if (slotFlags[1] != 0) { // slotFlags[1] is a "active" flag?
                // Compare param with the object's min and max blend range
                float minBlend = *(float*)(obj + 0x48 + objIndex); // Wait, objIndex already offsets? Actually obj is already pointer, so obj + 0x48 + slotIndex*0x24? The code uses iVar7 (which is i*0x24) to index into iVar4. iVar4 is from *(int *)(iVar6+0x10). So iVar4 is base of an array of structures of size 0x24. Then they access *(float *)(iVar4 + 0x48 + iVar7) and *(float *)(iVar4 + 0x50 + iVar7). So these are per-slot min and max blend values.
                float objMin = obj->blendMin; // +0x48 + i*0x24
                float objMax = obj->blendMax; // +0x50 + i*0x24

                if ((param < objMin) || (param > objMax && param != objMax)) {
                    // Outside range - enable or set flags
                    if ((slotFlags[0] & 4) == 0 && ((obj->flags2 & 0x1000000) == 0)) {
                        // Transition to "active" state
                        slotFlags[0] |= 0x74000000;
                        callSomeSoundOrEvent(); // FUN_005343f0
                        slotFlags[1] = 0;
                    } else {
                        slotFlags[0] |= 0x200000;
                    }
                } else {
                    // Within range - clear the 0x200000 flag
                    slotFlags[0] &= ~0x200000;
                }
            }

            slotFlags += 5; // Next slot flags block (5 uint32s)
            // slotIndex increases by 0x24 for the object array offset
            // but note: objIndex is not used directly in pointer arithmetic after first access?
            // Actually the code uses iVar7 incremented by 0x24, but obj pointer is recalculated each iteration from base + offset? The decompiled code shows iVar4 is fixed (from iVar6+0x10), and iVar7 is offset. So likely obj = base + iVar7. So we need to treat objArray as a byte offset.
        }

        // Update current blend value
        this->blendValue = param; // +0x90
    }

    // Always update lastSeenParam?
    this->lastParam = param; // +0x8c
}