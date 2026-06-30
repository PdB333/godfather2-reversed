// FUNC_NAME: copyFortyByteBlockArray
// Address: 0x005dab00
// This utility function copies an array of 40-byte blocks (5×8-byte fields) from a source range to a destination.
// Parameters: ECX = unused, EDX = srcStart (inclusive), stack = srcEnd (exclusive), EAX = dest (may be null for skip).
// The loop advances by one block per iteration (40 bytes).
void __fastcall copyFortyByteBlockArray(int /*unused*/, FortyByteBlock* srcStart, FortyByteBlock* srcEnd)
{
    FortyByteBlock* dest; // passed via EAX register, assumed to be set before call

    while (srcStart != srcEnd)
    {
        if (dest != nullptr)
        {
            // Copy the 5 eight-byte fields of the 40-byte struct
            *dest = *srcStart; // struct assignment copies all fields
        }
        // Advance both pointers by one 40-byte block
        srcStart = (FortyByteBlock*)((uint8_t*)srcStart + 40);
        dest = (FortyByteBlock*)((uint8_t*)dest + 40);
    }
}