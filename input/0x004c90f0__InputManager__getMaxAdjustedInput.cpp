// FUNC_NAME: InputManager::getMaxAdjustedInput
float __thiscall InputManager::getMaxAdjustedInput(float inputValue)
{
    float fVar1;
    float fVar2;
    int currentTime = gCurrentTime; // 0x01205224
    float maxResult = 0.0f;
    float fVar7 = 0.0f;

    if ((this->active != 0) && (this->enabled != 0)) { // +0x00 active flag? Actually unaff_EDI[0] and unaff_EDI[0xa4] (offset 0x290)
        // Slot array starts at offset 0x10? PiVar5 points to this + 0x18 = third int of first slot.
        // As per analysis, slot struct: { int active; int type; int lastTime; int minWindow; int maxWindow; }
        // piVar5 points to slot.lastTime initially.
        InputSlot* piVar5 = reinterpret_cast<InputSlot*>(reinterpret_cast<char*>(this) + 0x18);
        for (int i = 0; i < 32; ++i, piVar5++) { // each step adds 0x14? Wait piVar5 increments by 5 ints = 20 bytes, but struct is 5 ints = 20 bytes, so piVar5++ works if sizeof(InputSlot)=20.
            // Correction: piVar5 = this+0x18, piVar5[-2] is slot.active, piVar5[-1] is slot.type, piVar5[0] is slot.lastTime, piVar5[1] is slot.minWindow, piVar5[2] is slot.maxWindow.
            // So we can dereference with negative offsets. But for clarity, let's cast to a struct pointer with base at piVar5[-2]. However, easier: treat slot as struct with fields, and piVar5 points to lastTime.
            if (piVar5[-2].active != 0) { // +0x10
                fVar1 = static_cast<float>(this->maxValue); // +0x2CC (0xb3*4)
                if (this->maxValue < 0) {
                    fVar1 += kFloatTwoPower32; // DAT_00e44578
                }
                float temp = fVar1; // fVar6
                if ((piVar5[-1].type == 1) && // +0x14
                    (static_cast<uint>(currentTime - piVar5[0].lastTime) >= static_cast<uint>(piVar5[1].minWindow)) && // +0x1C
                    (static_cast<uint>(currentTime - piVar5[0].lastTime) <= static_cast<uint>(piVar5[2].maxWindow))) { // +0x20
                    CallSomeHelper(); // FUN_005e6970
                    fVar2 = static_cast<float>(this->threshold); // +0x2D0 (0xb4*4)
                    if (this->threshold < 0) {
                        fVar2 += kFloatTwoPower32;
                    }
                    temp = fVar1; // still fVar1 unless condition inside
                    if (inputValue <= fVar2) {
                        float ratio = inputValue / fVar2;
                        temp = (gDeadzoneScale - ratio) * fVar1; // DAT_00e2b1a4
                    }
                }
                if (fVar7 < temp) {
                    fVar7 = temp;
                }
            }
            // piVar5 = piVar5 + 5? In disassembly, piVar5 += 5 ints (20 bytes). But if we use struct pointer, we need to advance by sizeof(InputSlot). Since struct is 5 ints, incrementing pointer by 1 should work.
            // But note: piVar5 initially points to slot.lastTime (offset 0 from start of slot struct? Actually piVar5 = this+0x18, which is offset 0x08 from slot struct start at this+0x10? Wait:
            // slot struct starts at this+0x10. piVar5 = this+0x18 = this+0x10 + 0x08 = &slot.lastTime. So piVar5 points to the third field. So to go to next slot, we need to advance by sizeof(Slot) = 20 bytes = 5 ints. That means we must add 5 to the pointer (int*). Since piVar5 is int*, piVar5 += 5 moves by 20 bytes.
            // So the loop should not use piVar5++ (which would add 4 bytes). We'll manually adjust.
            piVar5 = reinterpret_cast<InputSlot*>(reinterpret_cast<char*>(piVar5) + 20); // skip to next slot (piVar5's base at lastTime)
        }
    }
    return fVar7;
}