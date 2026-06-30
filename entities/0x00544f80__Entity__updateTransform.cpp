// FUNC_NAME: Entity::updateTransform
void __thiscall Entity::updateTransform(int *this, uint param2, uint param3) {
    float fVar1;
    char cVar2;
    int iVar3;
    int *piVar4;
    int *piVar5;
    undefined1 auStack_90[16];
    undefined1 auStack_80[48];
    int local_50[12];
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;

    // First call: likely some pre-update utility (e.g., frame delta or input)
    FUN_0046fbc0(param2, param3);

    // Read position components (X, Y, Z) from this +0x134, +0x138, +0x13c
    fVar1 = (float)this[0x4d]; // +0x134 (X)
    // Copy 16 integers (64 bytes) from this+0x34 into local array -> transformation matrix
    piVar4 = this + 0x34; // offset 0xD0 (matrix)
    piVar5 = local_50;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar5 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar5 = piVar5 + 1;
    }

    // Zero out some local variables (likely used for bounds check)
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;

    // Position wrap check: compare wrapped distance against a maximum threshold
    if (((DAT_00e44598 < (float)((uint)(fVar1 - DAT_00e2b1a4) & DAT_00e44680)) ||
        (DAT_00e44598 < (float)((uint)((float)this[0x4e] - DAT_00e2b1a4) & DAT_00e44680))) ||
        (DAT_00e44598 < (float)((uint)((float)this[0x4f] - DAT_00e2b1a4) & DAT_00e44680))) {
        // If any component exceeds the max allowed distance after wrapping, adjust matrix
        FUN_0043a2a0(local_50, local_50);
    }

    iVar3 = this[0xba]; // offset 0x2E8 (some flag or pointer)
    cVar2 = (**(code **)(*this + 0x19c))(); // vtable method at index 103 (0x19c/4)
    if (cVar2 == '\0') {
        if (iVar3 != 0) {
            // If method returns false and flag is set, perform update sequence
            FUN_004b59d0(local_50, auStack_80);
            FUN_00aa3930(auStack_80);
            FUN_009f4c70(auStack_90);
        }
    } else {
        // If method returns true, trigger state change
        FUN_0055db80();
    }

    // Call another vtable method at offset 600 (index 150) – often post-update or render
    (**(code **)(*this + 600))();
    return;
}