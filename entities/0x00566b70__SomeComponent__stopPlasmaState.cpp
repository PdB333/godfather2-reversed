// FUNC_NAME: SomeComponent::stopPlasmaState
undefined4 __fastcall SomeComponent::stopPlasmaState(SomeComponent* this)
{
    uint uVar1;
    int iVar2;

    // Notify global manager (e.g., DebugManager) if present
    if (gDebugManager != (int *)0x0) {
        (**(code **)(*gDebugManager + 0xc))();
    }

    // If we have a sub-object (e.g., DebugLogger) and current state is 2, log stop request
    if ((*(int **)(this + 0xc) != (int *)0x0) && (*(char *)(this + 0x14) == '\x02')) {
        (**(code **)(**(int **)(this + 0xc) + 0x60))(5, "We Want To Stop Plasma");
    }

    // Extract and transform state bits from flags
    uVar1 = *(uint *)(this + 0x2c) >> 6 & 0xffffff01;
    // Signed byte extension: if uVar1 != 0, use (uVar1 >> 8) - 1; else use (uVar1 >> 8)
    iVar2 = CONCAT31((int3)(uVar1 >> 8), -((char)uVar1 != '\0')) + 4;
    // Store new state
    *(char *)(this + 0x14) = (char)iVar2;
    // Clear flags bits 5 and 6
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) & 0xffffff9f;
    // Reset sub-state if not 9
    if (*(int *)(this + 0x10) != 9) {
        *(undefined4 *)(this + 0x10) = 0;
    }
    // Return success indicator (always 1 in this branch)
    return CONCAT31((int3)((uint)iVar2 >> 8), 1);
}