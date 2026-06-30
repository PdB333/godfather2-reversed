// FUNC_NAME: TLSMemoryPool::releasePooledMemory

void TLSMemoryPool::releasePooledMemory(void)
{
    int count;
    void* tlsHandle;

    // Release first pool: pointer at +0x5c, count at +0x64 (100)
    count = *(int *)(this + 100); // +0x64
    if (count >= 0) {
        tlsHandle = TlsGetValue(gTlsIndex); // DAT_01139810
        FUN_00aa26e0(*(void **)(this + 0x5c), count * 4, 0x17); // release with debug fill 0x17
    }

    // Release second pool: pointer at +0x50, count at +0x58 (88)
    count = *(int *)(this + 0x58); // +0x58
    if (count >= 0) {
        tlsHandle = TlsGetValue(gTlsIndex);
        FUN_00aa26e0(*(void **)(this + 0x50), count * 4, 0x17);
    }

    // Release third pool: pointer at +0x44, count at +0x4c (76)
    count = *(int *)(this + 0x4c); // +0x4c
    if (count >= 0) {
        tlsHandle = TlsGetValue(gTlsIndex);
        FUN_00aa26e0(*(void **)(this + 0x44), count * 4, 0x17);
    }

    // Final cleanup for the TLS pool
    FUN_009fd9b0();
}