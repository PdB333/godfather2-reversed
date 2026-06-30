// FUNC_NAME: resetTwoInts
// Function address: 0x004abf00
// Role: Initializes a pair of 32-bit integer fields to zero. Used by multiple constructors/initializers,
//       likely for a small struct or class with two consecutive int members (e.g., a 2D int vector or range).
void __fastcall resetTwoInts(int* pair)
{
    pair[0] = 0;  // Offset +0x00
    pair[1] = 0;  // Offset +0x04
}