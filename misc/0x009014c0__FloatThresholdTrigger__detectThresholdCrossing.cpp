// FUNC_NAME: FloatThresholdTrigger::detectThresholdCrossing

void __thiscall FloatThresholdTrigger::detectThresholdCrossing(float oldValue, float newValue)
{
    float fVar1;
    uint uVar2;
    bool bVar3;
    bool bVar4;
    int iVar5;
    float10 fVar6;
    undefined1 auStack_c[4];
    int aiStack_8[2];

    if (((*(int*)(this + 0x38) != 0) && (*(int*)(this + 0x38) != 0x48)) &&
        (*(int*)(this + 0x40) != 0)) {
        // Get current time from time source (vtable+0x2c)
        fVar6 = (float10)(**(code**)(**(int**)(this + 0x40) + 0x2c))();
        uVar2 = *(uint*)(this + 0x24);            // flags (bit0: less, bit1: equal, bit2: greater)
        fVar1 = (float)(fVar6 * (float10)*(float*)(this + 0x20)); // threshold = time * factor

        // Check if old value satisfies threshold condition
        if (((((uVar2 & 1) != 0) && (oldValue < fVar1)) ||
             (((uVar2 & 2) != 0 && (oldValue == fVar1)))) ||
            (((uVar2 & 4) != 0 && (fVar1 < oldValue)))) {
            bVar3 = true;
        } else {
            bVar3 = false;
        }

        // Check if new value satisfies threshold condition
        if (((((uVar2 & 1) != 0) && (newValue < fVar1)) ||
             (((uVar2 & 2) != 0 && (newValue == fVar1)))) ||
            (((uVar2 & 4) != 0 && (fVar1 < newValue)))) {
            bVar4 = true;
        } else {
            bVar4 = false;
        }

        // If crossing INTO the threshold region (old outside, new inside)
        if ((!bVar3) && (bVar4)) {
            // Convert offset to event ID: targetId - 0x48 (or 0 if null)
            if (*(int*)(this + 0x38) == 0) {
                iVar5 = 0;
            } else {
                iVar5 = *(int*)(this + 0x38) + -0x48;
            }
            fireEventById(iVar5);
            executeAction(this + 0x18, auStack_c, 0);
            if (aiStack_8[0] != 0) {
                releaseObject(aiStack_8);
            }
        }
    }
    return;
}