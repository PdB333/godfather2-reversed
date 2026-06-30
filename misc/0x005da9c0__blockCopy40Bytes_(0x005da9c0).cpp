// FUNC_NAME: blockCopy40Bytes (0x005da9c0)
// Copies 40-byte blocks from source to destination until src pointer reaches srcEnd.
// Fastcall: dest in ECX, srcEnd in EDX, src on stack.
void __fastcall blockCopy40Bytes(void* dest, void* srcEnd, const void* src)
{
    // Use uint64* for efficient 8-byte copies (5*8 = 40 bytes per iteration)
    uint64* dstPtr = (uint64*)dest;
    const uint64* srcPtr = (const uint64*)src;
    const uint64* endPtr = (const uint64*)srcEnd;

    if (srcPtr != endPtr)
    {
        do
        {
            // Copy 5 qwords (40 bytes) per iteration
            dstPtr[0] = srcPtr[0];
            dstPtr[1] = srcPtr[1];
            dstPtr[2] = srcPtr[2];
            dstPtr[3] = srcPtr[3];
            dstPtr[4] = srcPtr[4];
            srcPtr += 5;
            dstPtr += 5;
        } while (srcPtr != endPtr);
    }
}