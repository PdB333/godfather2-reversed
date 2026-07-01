// FUNC_NAME: PlayerF2FSM::hideF2F
// Address: 0x00929ba0
// Role: Hides the F2F (Face-to-Face) camera/UI element, sets a flag at +0x50 to 0, and calls a script function.

void __fastcall PlayerF2FSM::hideF2F(PlayerF2FSM* this)
{
    // Stack local structure (possibly a Vector3 or similar)
    struct {
        float x; // offset -0xc
        float y; // offset -0x8
        uint8_t z; // offset -0x4 (1 byte, but likely part of a 4-byte field? decompiler shows undefined1)
    } localStruct; // total 12 bytes? Actually 4+4+1 = 9, but alignment may pad to 12.

    // Set flag at +0x50 to 0 (e.g., visibility flag)
    *(uint8_t*)((uintptr_t)this + 0x50) = 0;

    // Call script/function with string "HideF2F" and global data
    FUN_005a04a0("HideF2F", 0, &DAT_00d88584, 0);

    // Initialize local struct (likely zeroing)
    localStruct.x = DAT_01130358; // some global float
    localStruct.y = 0.0f;
    localStruct.z = 0;

    // Call another function with pointer to local struct and a zero
    FUN_00408a00(&localStruct, 0);
}