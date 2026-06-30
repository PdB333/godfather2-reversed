// FUNC_NAME: copy5EntryBlocks
// Function at 0x005dab00: Copies 40-byte blocks (5 × 8 bytes) from source to destination until source reaches end pointer.
// Uses __fastcall: ECX (param_1) is unused, EDX (param_2) is end pointer, stack (param_3) is source.
// Destination is passed in EAX (in_EAX). If EAX is null, skip copy but still advance.
void __fastcall copy5EntryBlocks(undefined4 unused, undefined8* endPtr, undefined8* src)
{
    undefined8* dst;

    // dst is the value of EAX at entry (not a formal parameter)
    // In this decompilation, it's captured as 'in_EAX'.
    dst = (undefined8*)__read_reg(EAX); // pseudo: get EAX register value

    if (src != endPtr) {
        do {
            if (dst != (undefined8*)0x0) {
                // Copy 5 consecutive 8-byte values (40 bytes total)
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                dst[4] = src[4];
            }
            // Advance both pointers by 5 entries (40 bytes)
            src += 5;
            dst += 5;
        } while (src != endPtr);
    }
    return;
}