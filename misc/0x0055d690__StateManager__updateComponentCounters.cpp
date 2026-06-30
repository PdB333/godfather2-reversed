// FUNC_NAME: StateManager::updateComponentCounters

void __thiscall StateManager::updateComponentCounters(void)
{
    short *psVar1;
    int iVar2;
    char cVar3;

    // Increment counters on component slots if their active flag is non-zero
    // Each component is pointed to from members at offsets 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x44, 0x9c, 0x3c
    // The component struct has:
    // +0x00: int (unknown)
    // +0x04: short activeFlag
    // +0x06: short counter (incremented)

    if (*(short *)(*(int *)(this + 0x1c) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x1c) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x20) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x20) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x24) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x24) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x28) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x28) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x2c) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x2c) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x30) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x30) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x34) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x34) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x38) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x38) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x44) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x44) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x9c) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x9c) + 6);
        *psVar1 = *psVar1 + 1;
    }
    if (*(short *)(*(int *)(this + 0x3c) + 4) != 0) {
        psVar1 = (short *)(*(int *)(this + 0x3c) + 6);
        *psVar1 = *psVar1 + 1;
    }

    // Global update call (likely engine tick)
    g_engineTickFunction();

    // Compute and store a delta (maybe elapsed time or progress)
    iVar2 = *(int *)(*(int *)(this + 0x34) + 8); // pointer from component at +0x34, offset +0x08
    *(float *)(this + 0x108) = *(float *)(iVar2 + 8) - *(float *)(iVar2 + 0x68); // store difference

    // Clear an array of 8-byte entries (likely per-layer or per-slot data)
    // Size is given by a byte from the first component (+0x1c) at its offset 0x20
    cVar3 = 0;
    if (0 < *(char *)(*(int *)(this + 0x1c) + 0x20)) {
        do {
            *(int *)(this + 0x150 + cVar3 * 8) = 0;
            *(int *)(this + 0x154 + cVar3 * 8) = 0;
            cVar3 = cVar3 + 1;
        } while (cVar3 < *(char *)(*(int *)(this + 0x1c) + 0x20));
    }
    return;
}