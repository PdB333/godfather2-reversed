// FUNC_NAME: Animated::update
void __fastcall Animated::update(int thisPtr)
{
  // Set flag bit 1 at +0x84 (e.g., "dirty" or "needs update")
  *(unsigned short *)(thisPtr + 0x84) |= 2;

  // Check if animation data exists (+0xd8) and flag bit 0 is set (+0x84 bit 0)
  if (*(int *)(thisPtr + 0xd8) != 0 && (*(unsigned char *)(thisPtr + 0x84) & 1) != 0) {
    // Scale stored float (+0xac) by two constants (likely time deltas or multipliers)
    float scaledValue = *(float *)(thisPtr + 0xac) * DAT_00d5eee4;
    *(float *)(thisPtr + 0xb0) = *(float *)(thisPtr + 0xac) * DAT_00e445ac;
    *(float *)(thisPtr + 0xb4) = scaledValue;
  }
}