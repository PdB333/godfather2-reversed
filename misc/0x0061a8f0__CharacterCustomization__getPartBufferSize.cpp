// FUNC_NAME: CharacterCustomization::getPartBufferSize
// Maps a body part enum value (0x1e-0x23) to its vertex buffer size.
// Returns 4 for the specified part types, 1 for all others.
int __fastcall getPartBufferSize(int partIndex)
{
    // Part indices correspond to known body parts (e.g., head, torso, etc.)
    // The range 0x1e to 0x23 (30-35) requires a 4-byte buffer; others use 1 byte.
    if (partIndex >= 0x1e && partIndex <= 0x23)
        return 4;
    else
        return 1;
}