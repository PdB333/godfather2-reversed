// FUNC_NAME: UnknownStruct::copyFrom
// Function at 0x0055f7d0: Copies a fixed-size structure (0x80 bytes) member by member.
// Offsets: +0x00: 2-byte flags, +0x04: 4-byte integer, +0x10..+0x7C: array of 27 DWORDs (108 bytes).
// This appears to be a copy assignment for a common data block (possibly a transform or state structure).

struct UnknownStruct {
    short flags;          // +0x00: two bytes (likely flags or type)
    // padding at +0x02..+0x03? Not copied.
    int someInt;          // +0x04: integer field
    // +0x08..+0x0F: uncopied gap (padding or separate members)
    int data[27];         // +0x10: 27 DWORDs (108 bytes) – likely matrix or array data
    // Total size = 2 + 2(pad) + 4 + 8(pad) + 108 = 0x80 bytes
};

void __thiscall UnknownStruct::copyFrom(UnknownStruct* this, const UnknownStruct* other) {
    // Copy two-byte field at offset 0
    *(short*)this = *(short*)other;

    // Copy integer at offset 4
    *(int*)((char*)this + 4) = *(int*)((char*)other + 4);

    // Copy block at offset 0x10 to 0x7C (27 DWORDs)
    for (int i = 0; i < 27; i++) {
        *(int*)((char*)this + 0x10 + i * 4) = *(int*)((char*)other + 0x10 + i * 4);
    }
    // Note: Original code copies each field individually; loop is for clarity.
    // The 2-byte copy could also be a short, but the decompiler shows two byte assigns.
}