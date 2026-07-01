// FUNC_NAME: CSomeManager::lazyInitialize
void __thiscall CSomeManager::lazyInitialize(void)
{
    // Guard: only initialize once (offset +0x80 is an initialized flag)
    if (*(char *)(this + 0x80) == '\0') {
        // Copy 0x8000 bytes from global static data (DAT_0112f9d0) into internal buffer at +0x4c
        if (DAT_0112f9d0 != 0) {
            FUN_00408900(this + 0x4c, &DAT_0112f9d0, 0x8000);  // memcpy-like helper
        }
        // Mark as initialized
        *(char *)(this + 0x80) = 1;
    }
}