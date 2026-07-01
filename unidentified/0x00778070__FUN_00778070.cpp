// FUNC_NAME: SomeClass::updateSomething

void __thiscall FUN_00778070(int thisPtr, int someParam)
{
    int *piVar1;
    int iVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    float10 fVar6;
    float10 fVar7;
    undefined4 uVar8;
    undefined4 uVar9;

    piVar1 = *(int **)(thisPtr + 0x5c); // +0x5c: pointer to some internal data (maybe a manager object)
    iVar4 = FUN_00800a90(); // Get some object/manager instance
    if (iVar4 != 0) {
        FUN_00776570(iVar4); // Perform some operation on that object
        fVar3 = (float)someParam;
        if (someParam < 0) {
            fVar3 = fVar3 + 1.0f; // Adjust negative values (DAT_00e44578 likely 1.0f)
        }
        *(float *)(thisPtr + 0x98) = fVar3 * 0.001f; // +0x98: store scaled parameter, DAT_00d5efb8 likely 0.001
        iVar5 = _rand();
        iVar2 = *(int *)(iVar4 + 0x328); // +0x328: some value from the object
        fVar6 = (float10)FUN_00701020(); // Get some random/float value
        fVar7 = (float10)iVar2;
        if (iVar2 < 0) {
            fVar7 = fVar7 + 1.0f; // Adjust negative (DAT_00e44578 likely 1.0f)
        }
        *(float *)(thisPtr + 0x94) = // +0x94: compute and store combined value (maybe steering/target)
            (float)((float10)iVar5 * 0.01f * 0.003f + fVar7 * fVar6 + // DAT_00e44590=0.01, _DAT_00d6819c=0.003
                  (float10)*(float *)(thisPtr + 0x98));
        piVar1[0x7d6] = piVar1[0x7d6] | 0x400000; // Set flag bit 22
        (**(code **)(*piVar1 + 0x264))(); // Call vtable method at +0x264 (likely update/finalize)
        piVar1[0x7d6] = piVar1[0x7d6] & 0xffbfffff; // Clear flag bit 22
        if (*(char *)(iVar4 + 0x1aa) == '\x01') { // +0x1aa: some state flag
            uVar8 = 2;
        }
        else {
            uVar8 = 3;
        }
        FUN_00777200(uVar8); // Set state/behavior (2 or 3)
        if ((*(uint *)(thisPtr + 0xac) >> 10 & 1) != 0) { // +0xac: check flag bit 10
            uVar9 = 0;
            uVar8 = FUN_006fbc40(0,0); // Get some value/object
            FUN_007f96a0(0,5,uVar8,uVar9); // Play sound/effect (presumably with sound id 5)
            FUN_006fbc70(); // Cleanup after previous call
        }
    }
    return;
}