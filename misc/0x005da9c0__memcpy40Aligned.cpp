// FUNC_NAME: memcpy40Aligned
// Address: 0x005da9c0
// This function copies a block of memory in 40‑byte (5×8) chunks.
// The destination pointer is passed in EAX (not shown in the signature), 
// the source range is given by (srcEnd) as the exclusive end, and (srcStart) as the start.
// The loop advances both pointers by 40 bytes each iteration until srcStart == srcEnd.
// Remark: param_1 (ECX) is unused – the calling convention is non‑standard.

void __fastcall memcpy40Aligned(undefined4 param_1, undefined8 *srcEnd, undefined8 *srcStart)
{
    // in_EAX holds the destination pointer, set by the caller.
    // The copy is performed in 5‑qword (40‑byte) steps.
    if (srcStart != srcEnd) {
        do {
            *in_EAX = *srcStart;
            in_EAX[1] = srcStart[1];
            in_EAX[2] = srcStart[2];
            in_EAX[3] = srcStart[3];
            in_EAX[4] = srcStart[4];
            srcStart += 5;   // advance source by 5×8 = 40 bytes
            in_EAX   += 5;   // advance destination by 40 bytes
        } while (srcStart != srcEnd);
    }
    return;
}