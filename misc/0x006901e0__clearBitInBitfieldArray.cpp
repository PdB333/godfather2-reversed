// FUNC_NAME: clearBitInBitfieldArray
// Function address: 0x006901e0
// Role: Clears a specific bit in a bitfield array stored at offset 0x249c from the object.
// The bitfield is an array of uint32_t words, indexed by bitIndex >> 5.
void __thiscall clearBitInBitfieldArray(uint bitIndex)
{
    // Calculate pointer to the word containing the bit
    uint* bitfieldWord = reinterpret_cast<uint*>(
        reinterpret_cast<uintptr_t>(this) + 0x249c + (bitIndex >> 5) * 4
    );
    // Clear the bit using a mask
    *bitfieldWord &= ~(1 << (bitIndex & 0x1f));
}