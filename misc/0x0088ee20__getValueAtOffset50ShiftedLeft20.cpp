// FUNC_NAME: getValueAtOffset50ShiftedLeft20
// Function address: 0x0088ee20
// Very simple function: reads an int at offset 0x50 from this pointer,
// shifts left by 20 bits (multiply by 0x100000) and returns.
// Likely an accessor for a packed field or fixed-point scaling.

int __fastcall getValueAtOffset50ShiftedLeft20(int this)
{
    return *(int *)(this + 0x50) << 0x14;  // shift left 20 bits
}