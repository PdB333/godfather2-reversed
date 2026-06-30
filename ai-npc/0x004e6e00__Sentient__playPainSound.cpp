// FUNC_NAME: Sentient::playPainSound
void __thiscall Sentient::playPainSound(uint this, int sentientObj)
{
  // Check if the sentient has a pain sound flag set (bit 0 of byte at +0xB2)
  if ((*(byte *)(sentientObj + 0xb2) & 1) != 0) {
    // Call sound playback function with:
    // - sound handle at +0xA0
    // - sound parameters starting at +0x10
    // - unknown flags: 0, 0xffffffff, 6, 0
    // - this pointer as last parameter
    FUN_00433700(*(undefined4 *)(sentientObj + 0xa0), sentientObj + 0x10, 0, 0xffffffff, 6, 0, this);
  }
  return;
}