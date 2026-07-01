// FUNC_NAME: DebugSentinel::init
void __fastcall DebugSentinel::init(uint32_t* thisPtr)
{
    // Zero out first three fields (likely vtable pointer and two other members)
    thisPtr[0] = 0;          // +0x00: vtable pointer (null)
    thisPtr[2] = 0;          // +0x08: some field
    thisPtr[3] = 0;          // +0x0C: some field

    // Set debug sentinel values to mark uninitialized/invalid memory
    thisPtr[5] = 0xBADBADBA; // +0x14: sentinel 1
    thisPtr[6] = 0xBEEFBEEF; // +0x18: sentinel 2
    thisPtr[7] = 0xEAC15A55; // +0x1C: sentinel 3
    thisPtr[8] = 0x91100911; // +0x20: sentinel 4
}