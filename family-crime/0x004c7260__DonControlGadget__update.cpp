//FUNC_NAME: DonControlGadget::update
void __thiscall DonControlGadget::update(uint this) {
    int iVar1;
    int iVar2;
    int iVar3;
    int *piVar4;
    float lowPartB0;
    float highPartB0;
    float highPartC0;
    float lowPartC8;
    float highPartC8;

    iVar2 = this;
    // Split double at +0xB0 into two floats (low and high parts)
    lowPartB0 = (float)*(undefined8 *)(this + 0xB0);
    highPartB0 = (float)((ulonglong)*(undefined8 *)(this + 0xB0) >> 0x20);
    // Condition: check various floating-point fields and state
    if (((((0.0 <= *(float *)(this + 0xAC) * lowPartB0) ||
          (highPartC0 = (float)((ulonglong)*(undefined8 *)(this + 0xC0) >> 0x20), highPartC0 != 0.0)) ||
         (lowPartC8 = (float)*(undefined8 *)(this + 200), lowPartC8 != 0.0)) ||
        (highPartC8 = (float)((ulonglong)*(undefined8 *)(this + 200) >> 0x20), highPartC8 != 0.0)) &&
       ((0.0 <= highPartB0 && (2 < *(uint *)(this + 4))))) {
        // Begin drawing or update sequence
        FUN_004c5da0();
        iVar3 = 0;
        piVar4 = (int *)(this + 0xA0);
        this = 0;
        if (*piVar4 != 0) {
            do {
                // Get pointer to element in array at +0xA4, stride 0x1C
                iVar1 = *(int *)(*(int *)(iVar2 + 0xA4) + 4 + iVar3);
                piVar4 = (int *)(*(int *)(iVar2 + 0xA4) + iVar3);
                // Check conditions on the element's target object
                if (((*(char *)(iVar1 + 4) == '\x01') && (*(char *)(iVar1 + 6) != '\0')) &&
                   (((*(byte *)(iVar1 + 8) & 0x10) == 0 &&
                    (((*(byte *)(*piVar4 + 0xB2) & 1) != 0 && (*(int *)(iVar2 + 8) == *(int *)(iVar2 + 4))))))) {
                    // Set texture/material from this+0x94
                    FUN_00613b40(*(undefined4 *)(iVar2 + 0x94));
                    // Continue drawing
                    FUN_004c5d70();
                    // Draw first sprite (index 0) using computed texture ID from iVar1
                    FUN_0060c8d0(0,
                                 *(undefined4 *)(iVar1 + 100 + (uint)*(byte *)(*(int *)(iVar1 + 0x50) + 0x2D) * 4),
                                 *(undefined1 *)(iVar1 + 0x26),
                                 0, 0, 0, 1);
                    // Draw second sprite (index 1) using texture from element array (offset based on flag)
                    FUN_0060c8d0(1,
                                 piVar4[(*(uint *)(iVar2 + 8) & 1) + 5],
                                 0xC,
                                 0, 0, 0, 1);
                    // Draw text or rectangle with parameters from iVar1
                    FUN_0060cb70(*(undefined2 *)(iVar1 + 0x3C),
                                 *(undefined4 *)(iVar1 + 0x60),
                                 *(undefined4 *)(iVar1 + 0x34),
                                 *(undefined4 *)(iVar1 + 0x30),
                                 *(undefined2 *)(iVar1 + 0x40),
                                 *(undefined2 *)(iVar1 + 0x42));
                }
                this = this + 1;
                iVar3 = iVar3 + 0x1C;
            } while (this < *(uint *)(iVar2 + 0xA0));
        }
        // Update global state flags
        if (DAT_011da800 != 1) {
            (**(code **)(*DAT_01205750 + 0x198))(DAT_01205750, 1, 1);
            DAT_011da800 = 1;
        }
        if (DAT_011da804 != 0) {
            (**(code **)(*DAT_01205750 + 400))(DAT_01205750, 1, 0, 0, 0);
            DAT_011da804 = 0;
        }
    }
    return;
}