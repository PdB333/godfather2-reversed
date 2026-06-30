// FUNC_NAME: copyToTLSBuffer
void __thiscall copyToTLSBuffer(void* thisPointer, uint32_t* sourceData)
{
    // Get the thread-local storage base pointer (FS:0x2c is the TLS index slot)
    int* tlsBase = *(int**)(__readfsdword(0x2c));
    // Fetch the per-module TLS base (first pointer in the TLS array) + 8
    int* moduleTlsBase = *(int**)(*(int*)tlsBase + 8);
    // Compute destination buffer address: module TLS base + offset from thisPointer+0x18
    uint32_t* destBuffer = (uint32_t*)((int)moduleTlsBase + *(int*)((char*)thisPointer + 0x18));

    // Copy 64 bytes (16 dwords) from sourceData to destBuffer
    uint32_t v0, v1, v2, v3;
    v0 = sourceData[0]; v1 = sourceData[1]; v2 = sourceData[2]; v3 = sourceData[3];
    destBuffer[0] = v0; destBuffer[1] = v1; destBuffer[2] = v2; destBuffer[3] = v3;

    v0 = sourceData[4]; v1 = sourceData[5]; v2 = sourceData[6]; v3 = sourceData[7];
    destBuffer[4] = v0; destBuffer[5] = v1; destBuffer[6] = v2; destBuffer[7] = v3;

    v0 = sourceData[8]; v1 = sourceData[9]; v2 = sourceData[10]; v3 = sourceData[11];
    destBuffer[8] = v0; destBuffer[9] = v1; destBuffer[10] = v2; destBuffer[11] = v3;

    v0 = sourceData[12]; v1 = sourceData[13]; v2 = sourceData[14]; v3 = sourceData[15];
    destBuffer[12] = v0; destBuffer[13] = v1; destBuffer[14] = v2; destBuffer[15] = v3;
}