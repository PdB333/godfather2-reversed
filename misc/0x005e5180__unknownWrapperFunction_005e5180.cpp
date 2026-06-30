// FUNC_NAME: unknownWrapperFunction_005e5180
// Function address: 0x005e5180
// Role: Simple wrapper that forwards param_2 and two local buffers to sub_005f0560.
// The first parameter (ECX) is not used; this suggests a static or global function.
// The two locals (one byte, one 4‑byte array) are output parameters whose contents are ignored after the call.
void __fastcall unknownWrapperFunction(int unusedParam, int param2)
{
    char byteOutput;                     // +0x00 (local)
    char bufferOutput[4];                // +0x04 (local)
    sub_005f0560(param2, &byteOutput, bufferOutput);
    // sub_005f0560 (0x005f0560) likely performs some initialization or query using param2,
    // writing results into byteOutput and bufferOutput. The caller does not use these values.
    return;
}