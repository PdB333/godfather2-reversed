// FUNC_NAME: SomeStructure::constructor_zeroInit
void __fastcall SomeStructure::constructor_zeroInit(undefined4 *thisStruct)
{
  // This initializes the struct to zero. Offsets are relative to thisStruct.
  thisStruct[0] = 0;   // +0x00
  thisStruct[1] = 0;   // +0x04
  thisStruct[2] = 0;   // +0x08
  thisStruct[3] = 0;   // +0x0C
  thisStruct[0xc] = 0; // +0x30
  thisStruct[0xd] = 0; // +0x34
  thisStruct[0xe] = 0; // +0x38
  thisStruct[0xf] = 0; // +0x3C
  thisStruct[4] = 0;   // +0x10
  thisStruct[5] = 0;   // +0x14
  thisStruct[6] = 0;   // +0x18
  thisStruct[7] = 0;   // +0x1C
  thisStruct[0x10] = 0; // +0x40
  thisStruct[0x11] = 0; // +0x44
  thisStruct[0x12] = 0; // +0x48
  thisStruct[0x13] = 0; // +0x4C
  thisStruct[8] = 0;   // +0x20
  thisStruct[9] = 0;   // +0x24
  thisStruct[10] = 0;  // +0x28
  thisStruct[0xb] = 0; // +0x2C
  thisStruct[0x14] = 0; // +0x50
  thisStruct[0x15] = 0; // +0x54
  thisStruct[0x16] = 0; // +0x58
  thisStruct[0x17] = 0; // +0x5C
  thisStruct[0x18] = 0; // +0x60
  thisStruct[0x19] = 0; // +0x64
  thisStruct[0x1a] = 0; // +0x68
  thisStruct[0x1b] = 0; // +0x6C
  return;
}