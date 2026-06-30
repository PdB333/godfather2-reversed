// FUNC_NAME: copy8ByteArrayToGlobalBuffer
void __fastcall copy8ByteArrayToGlobalBuffer(undefined4 param_1, int sourceBuffer)
{
    uint elementCount = unaff_ESI; // Input register ESI holds the number of 8-byte elements to copy
    uint idx = 0;
    
    if (elementCount != 0) {
        do {
            // Global array of 8-byte structures at DAT_01223354
            undefined4 *destEntry = (undefined4 *)(DAT_01223354 + idx * 8);
            
            if (destEntry != (undefined4 *)0x0) {
                // Copy 8 bytes (two 32-bit values) from source to destination
                *destEntry = *(undefined4 *)(sourceBuffer + idx * 8);
                destEntry[1] = *(undefined4 *)(sourceBuffer + (idx * 8) + 4);
            }
            
            idx++;
        } while (idx < elementCount);
    }
    
    return;
}