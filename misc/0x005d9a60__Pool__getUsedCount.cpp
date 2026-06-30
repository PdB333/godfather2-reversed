// FUNC_NAME: Pool::getUsedCount
int __fastcall Pool::getUsedCount(int this) {
    int startPtr = *(int *)(this + 8);
    if (startPtr == 0) {
        return 0;
    }
    int currentPtr = *(int *)(this + 0xc);
    // Element stride is 0x28 (40 bytes), compute number of elements allocated
    return (currentPtr - startPtr) / 0x28;
}