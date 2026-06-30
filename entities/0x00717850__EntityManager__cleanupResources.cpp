// FUNC_NAME: EntityManager::cleanupResources
void __thiscall EntityManager::cleanupResources(void)
{
    void *pBuffer1;
    void *pBuffer2;
    void *pParentManager;
    void *pListHead;

    // Free first buffer (offset +0x330)
    if (*(int *)(this + 0x330) != 0) {
        Memory::deallocate(*(int **)(this + 0x330));
        *(int *)(this + 0x330) = 0;
    }

    // Free second buffer (offset +0x338)
    if (*(int *)(this + 0x338) != 0) {
        Memory::deallocate((unsigned int *)(this + 0x338));
        *(int *)(this + 0x338) = 0;
    }

    // Get parent manager pointer (offset +0x18)
    pParentManager = *(void **)(this + 0x18);
    pListHead = (int *)((char *)pParentManager + 0x1c78);

    // If the manager's list head is non-null, free it and clear
    if (*(int *)pListHead != 0) {
        Memory::deallocate(pListHead);
        *(int *)pListHead = 0;
    }

    // Clear flags at offset +0x308 (bits 2 and 4)
    *(unsigned int *)(this + 0x308) &= 0xffffffeb;

    return;
}