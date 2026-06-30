// FUNC_NAME: tlsStringConversionHelper
void __thiscall tlsStringConversionHelper(void* unusedThis, void* inputString) {
    // Temporary stack buffers for potential string conversions (384 and 396 bytes)
    char tempBuffer1[384]; // 0x180 bytes
    char tempBuffer2[396]; // 0x18C bytes

    // Structures used by the conversion function (pointer+size pairs)
    struct {
        void** bufPtr;  // +0x00: pointer to a buffer pointer
        int bufSize;    // +0x04: size or length field
    } convArgs1;

    // Initialize from global defaults
    convArgs1.bufPtr = (void**)0x00e397fc;    // PTR_LAB_00e397fc
    convArgs1.bufSize = *(int*)0x00e445dc;    // DAT_00e445dc

    // Second structure (initialized identically, likely for a second call)
    struct {
        void** bufPtr;
        int bufSize;
    } convArgs2;
    convArgs2.bufPtr = (void**)0x00e397fc;
    convArgs2.bufSize = *(int*)0x00e445dc;

    // Perform the actual conversion using the first structure
    FUN_00552930(inputString, &convArgs1); // FUN_00552930

    // After conversion, update the first structure's buffer pointer to another global
    convArgs1.bufPtr = (void**)0x00dc4710; // PTR_LAB_00dc4710
    // The second structure remains unchanged (pointing to original default)

    // Tagged flag for first temporary buffer (0x80000008 indicates stack buffer of 8 * 0x30 bytes?)
    uint flags1 = 0x80000008;
    if ((int)flags1 >= 0) { // only execute if high bit not set (negative)
        uint size1 = (flags1 & 0x3FFFFFFF) * 0x30; // size in bytes
        void* tlsData = TlsGetValue(*(DWORD*)0x01139810); // per-thread data
        // Perform some operation on the buffer (likely free or initialise)
        FUN_00aa26e0(tempBuffer1, size1, 0x17);
    }

    // Tagged flag for second temporary buffer
    uint flags2 = 0x80000008;
    if ((int)flags2 >= 0) {
        uint size2 = (flags2 & 0x3FFFFFFF) * 0x30;
        void* tlsData = TlsGetValue(*(DWORD*)0x01139810);
        FUN_00aa26e0(tempBuffer2, size2, 0x17);
    }
}