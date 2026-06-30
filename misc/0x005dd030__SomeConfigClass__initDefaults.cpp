// FUNC_NAME: SomeConfigClass::initDefaults
void SomeConfigClass::initDefaults(void)
{
  // This function initializes default values for a configuration structure.
  // The structure appears to be 0x68 bytes (0x1A * 4) and contains flags, constants,
  // and possibly debug settings.

  // Constants loaded from global data at addresses 0x00e2b1a4 and 0x00e2b118.
  // Likely some system-level default values.
  uint32_t dword_e2b1a4 = DAT_00e2b1a4;
  uint32_t dword_e2b118 = DAT_00e2b118;

  // +0x44: Set some timer or threshold to 96000 (ms? frames?)
  in_EAX[0x11] = 96000;  // +0x44
  // +0x4C: Another value set to 96000
  in_EAX[0x13] = 96000;  // +0x4C

  // +0x00: First field initialized with the global value
  *in_EAX = dword_e2b1a4;  // +0x00
  // +0x04: Second field same value
  in_EAX[1] = dword_e2b1a4;  // +0x04
  // +0x28: Another field same value
  in_EAX[10] = dword_e2b1a4; // +0x28
  // +0x2C: Another field same value
  in_EAX[0xb] = dword_e2b1a4; // +0x2C

  // Byte at +0x21 and +0x22 set to 0 (probably boolean flags)
  *(uint8_t*)((int)in_EAX + 0x21) = 0;  // +0x21
  *(uint8_t*)((int)in_EAX + 0x22) = 0;  // +0x22

  // Zeroing out several int fields
  in_EAX[2] = 0;   // +0x08
  in_EAX[9] = 0;   // +0x24
  in_EAX[0xc] = 0; // +0x30
  in_EAX[0xd] = 0; // +0x34
  in_EAX[0x12] = 0; // +0x48
  *(uint8_t*)((int)in_EAX + 0x23) = 0; // +0x23

  // Set a flag to 1 at +0x0C
  in_EAX[3] = 1;   // +0x0C

  // Magic constants (likely debug markers or sentinel values)
  in_EAX[4] = 0xbadbadba;  // +0x10 - BadBad
  in_EAX[5] = 0xbeefbeef;  // +0x14 - BeefBeef
  in_EAX[6] = 0xeac15a55;  // +0x18 - EAC IS A 55? (EARS internal ID?)
  in_EAX[7] = 0x91100911;  // +0x1C - Police? (9-1-1)

  // +0x38: Set from the other global value
  in_EAX[0xe] = dword_e2b118; // +0x38
  // +0x3C: Set from first global value again
  in_EAX[0xf] = dword_e2b1a4; // +0x3C

  // +0x50 to +0x64: Zero out remaining fields (six ints)
  in_EAX[0x14] = 0; // +0x50
  in_EAX[0x15] = 0; // +0x54
  in_EAX[0x16] = 0; // +0x58
  in_EAX[0x17] = 0; // +0x5C
  in_EAX[0x18] = 0; // +0x60
  in_EAX[0x19] = 0; // +0x64
}