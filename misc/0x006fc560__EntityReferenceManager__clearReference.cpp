// FUNC_NAME: EntityReferenceManager::clearReference
// Address: 0x006fc560
// This function clears two reference slots if they point to the given entity.
void __thiscall EntityReferenceManager::clearReference(int thisPtr, int entityPtr)
{
    // +0x184: pointer to some entity (likely a target or reference)
    // +0x180: associated data (could be type or ID)
    if (*(int *)(thisPtr + 0x184) == entityPtr) {
        *(int *)(thisPtr + 0x184) = 0;
        *(int *)(thisPtr + 0x180) = 0;
    }

    // +0x1bc: another entity reference slot
    // +0x1b8: associated data for that slot
    if (*(int *)(thisPtr + 0x1bc) == entityPtr) {
        *(int *)(thisPtr + 0x1bc) = 0;
        *(int *)(thisPtr + 0x1b8) = 0;
    }
}