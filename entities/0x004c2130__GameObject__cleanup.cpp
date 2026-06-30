// FUNC_NAME: GameObject::cleanup
void __thiscall GameObject::cleanup(void) {
    // +0x1c4: flags field (bitmask)
    if ((*(uint *)(this + 0x1c4) & 0x40) != 0) {
        // Clear bit 6 (0x40) and call some string-related function
        *(uint *)(this + 0x1c4) &= 0xffffffbf;
        FUN_004086d0(&g_debugString); // probably prints/logs something
    }

    int* pSubObject = *(int **)(this + 0x200); // +0x200: pointer to a sub-object
    if ((pSubObject != NULL) && (*(int *)(pSubObject + 8) != 0)) {
        FUN_009e7530(pSubObject); // release/delete the sub-object?
    }

    int* pOtherObject = *(int **)(this + 0x1c0); // +0x1c0: another sub-object pointer
    if (pOtherObject != NULL) {
        FUN_004c23f0(0); // first cleanup call on index 0
        FUN_004c23f0(0); // second cleanup call on index 0
    }
}