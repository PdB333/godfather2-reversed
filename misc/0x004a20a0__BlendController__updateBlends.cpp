// FUNC_NAME: BlendController::updateBlends

void BlendController::updateBlends(uint unknown1, int unknown2, float blendValue, uint unknown4)
{
    // Reentrancy guard at +0x1C0
    this->busyFlag = true;

    // unaff_EDI - external manager pointer (e.g., from EDI register)
    // Possibly a globally accessible manager object
    if (g_manager) {
        // Call helper function (likely resets or prepares something)
        FUN_004a1fc0();

        // Slot structure at +0x88: array of 12 entries (size 0xC each)
        // Each entry: [void* object, float currentVal, float previousVal]
        // Current index at +0x118
        int currentIdx = this->activeSlotIndex;
        void* slotObj = this->slotArray[currentIdx].objectPtr;

        if (slotObj) {
            // Call virtual function on the object's vtable (offset 0)
            // Calling convention: __thiscall with 'this' in ECX, arg = 1
            (*(void (__thiscall**)(void*, int))(*((int**)slotObj)))(slotObj, 1);

            // Clear the object pointer for this slot
            this->slotArray[currentIdx].objectPtr = nullptr;
        }

        // Clear the blend target at +0x8C (offset 4 of slot array entry)
        float* entryBase = &this->slotArray[currentIdx].currentVal; // +0x8C for idx=0
        *entryBase = 0.0f; // Actually set to 0 via later code? Wait, the original sets *(this+0x8c + idx*0xc) = uVar3 (the result of virtual call).
        // Correction: The original code: *(undefined4 *)(in_EAX + 0x8c + *(int *)(in_EAX + 0x118) * 0xc) = 0;
        // So it sets the float at offset 4 of the entry to 0 (the currentVal). Then later it sets the object pointer from the virtual call result.
        // Then it calls a virtual function on that new object with param1 and param4.
        this->slotArray[currentIdx].currentVal = 0.0f;

        // Get new object via virtual call on manager (vtable offset 0x20)
        void* newObj = (*(void* (__thiscall**)(void*))(*((int**)g_manager) + 0x20 / 4))(g_manager);
        this->slotArray[currentIdx].objectPtr = newObj;

        if (newObj) {
            // Call virtual function at vtable offset 4 on the new object (with two args)
            (*(void (__thiscall**)(void*, uint, uint))(*((int**)newObj) + 4 / 4))(newObj, unknown1, unknown4);
        }
    }

    // Global blend delta (DAT_00e2b1a4)
    float blendDelta = g_blendDelta;

    // Iterate over all 12 slots
    for (uint i = 0; i < 12; i++) {
        float* slotCurr = &this->slotArray[i].currentVal; // offset +0x8C + i*0xC
        float* slotPrev = &this->slotArray[i].previousVal; // offset +0x90? Actually slotPrev = slotCurr + 1

        if (i == this->activeSlotIndex) {
            // Active slot: blendDelta becomes the new target value
            slotPrev[0] = blendDelta - slotCurr[0]; // store difference

            if (blendValue == 0.0f) {
                slotCurr[0] = blendDelta;
            }
        } else {
            // Inactive slots: reset current to 0 if blendValue is 0
            if (blendValue == 0.0f) {
                slotCurr[0] = 0.0f;
            }
            slotPrev[0] = slotCurr[0]; // copy current to previous
        }
    }

    // Clear variables at the end
    this->someCount1 = 0;   // +0x11C
    this->someCount2 = 0;   // +0x120
    this->storedBlendValue = blendValue; // +0x124
    this->someId = unknown1; // +0x128

    this->busyFlag = false;
}