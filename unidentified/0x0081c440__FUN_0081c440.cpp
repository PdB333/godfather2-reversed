// FUNC_NAME: unknown::validateAndGetBuffer
// Address: 0x0081c440
// Validates a buffer descriptor and returns a pointer to the actual data.
// *param_1 points to a header structure (must be non-null).
// param_1[1] is compared with *( *param_1 + 0x18 ); if equal, assertion fails.
// On success, returns param_1[1] + 8 (skipping an 8‑byte header).

int __fastcall validateAndGetBuffer(int* bufferHeader)
{
    if (*bufferHeader == 0) {
        FUN_00b97aea();  // assert / abort
    }
    if (bufferHeader[1] == *(int*)(*bufferHeader + 0x18)) {
        FUN_00b97aea();  // assert / abort
    }
    return bufferHeader[1] + 8;
}