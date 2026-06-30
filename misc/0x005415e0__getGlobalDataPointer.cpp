// FUNC_NAME: getGlobalDataPointer
// Address: 0x005415e0
// Returns a pointer to a global data structure at 0x01139820.
// This is likely a singleton or global manager instance.
undefined4* getGlobalDataPointer() {
    return &DAT_01139820;
}