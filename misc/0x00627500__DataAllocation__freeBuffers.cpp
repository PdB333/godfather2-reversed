// FUNC_NAME: DataAllocation::freeBuffers
void __thiscall DataAllocation::freeBuffers(MemoryPool* pPool) {
    unsigned short count1 = *(unsigned short*)(this + 0x2c);
    if (*(int*)(this + 0x28) != 0) {
        g_pDeallocFunc(*(void**)(this + 0x28));
        if (pPool != 0) {
            int* pUsedSize = (int*)(*(int*)(pPool + 0x10) + 0x24);
            *pUsedSize += (int)count1 * -0x18;
        }
    }
    int count2 = *(int*)(this + 0x20);
    if (*(int*)(this + 0x1c) != 0) {
        g_pDeallocFunc(*(void**)(this + 0x1c));
        if (pPool != 0) {
            int* pUsedSize = (int*)(*(int*)(pPool + 0x10) + 0x24);
            *pUsedSize += count2 * -8;
        }
    }
}