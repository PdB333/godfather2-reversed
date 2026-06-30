// FUNC_NAME: maskToIndex
// Input: mask (single-bit mask in bits 1-27), outIndex (pointer to store bit position).
// Returns 1 if a single set bit was found (position 1-27), else 0.
// Note: bit 0 (mask == 1) is not handled.
int __fastcall maskToIndex(int mask, int* outIndex)
{
  int bitPos;

  // Search for bit positions 1 through 27
  for (bitPos = 1; bitPos < 0x1c; bitPos++)
  {
    if (mask == (1 << bitPos))
    {
      *outIndex = bitPos;
      return 1;
    }
  }

  return 0;
}