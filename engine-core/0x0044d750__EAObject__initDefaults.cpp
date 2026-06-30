// FUNC_NAME: EAObject::initDefaults
void __fastcall EAObject::initDefaults(unsigned int *thisObj)
{
  // Constants from global data (likely default settings)
  unsigned int defaultInt = DAT_00e2b1a4;
  unsigned int defaultInt2 = DAT_00e2b050;
  unsigned int defaultInt3 = DAT_00e447a4;
  unsigned int defaultInt4 = DAT_00e2fc48;
  unsigned int defaultInt5 = DAT_00e447a0;

  // Offset 0x00-0x0C: Magic signature (used for structure validation)
  thisObj[0] = 0xBADBADBA;          // +0x00: magic1
  thisObj[1] = 0xBEEFBEEF;          // +0x04: magic2
  thisObj[2] = 0xEAC15A55;          // +0x08: magic3
  thisObj[3] = 0x91100911;          // +0x0C: magic4

  // Offset 0x50 (0x14*4): Unknown field
  thisObj[0x14] = 0;                // +0x50: someFlag1 (int)

  // Offset 0x54-0x5B: Packed byte fields and short
  *(unsigned char *)((int)thisObj + 0x54) = 0;  // +0x54: byteA
  *(unsigned char *)((int)thisObj + 0x55) = 0;  // +0x55: byteB
  *(unsigned short *)((int)thisObj + 0x56) = 0x000B; // +0x56: wordC (default 11)

  // Offset 0x58 (0x16*4): Unknown field
  thisObj[0x16] = 0xFFFFFFFF;       // +0x58: allBitsSet (int)

  // Offset 0x5C-0x5F: Four consecutive bytes set to 0xFF
  *(unsigned char *)((int)thisObj + 0x5C) = 0xFF; // +0x5C: byteD
  *(unsigned char *)((int)thisObj + 0x5D) = 0xFF; // +0x5D: byteE
  *(unsigned char *)((int)thisObj + 0x5E) = 0xFF; // +0x5E: byteF
  *(unsigned char *)((int)thisObj + 0x5F) = 0xFF; // +0x5F: byteG

  // Offset 0x80-0x84: More byte fields
  *(unsigned char *)((int)thisObj + 0x80) = 0;    // +0x80: byteH
  *(unsigned char *)((int)thisObj + 0x81) = 0;    // +0x81: byteI
  *(unsigned char *)((int)thisObj + 0x82) = 0;    // +0x82: byteJ
  *(unsigned char *)((int)thisObj + 0x83) = 0xB2; // +0x83: byteK (default 178)
  *(unsigned char *)((int)thisObj + 0x84) = 0;    // +0x84: byteL

  // Offset 0x6C-0x7C: Global data assignments (likely default values for player stats)
  thisObj[0x1B] = defaultInt2;      // +0x6C: field1
  thisObj[0x1C] = defaultInt3;      // +0x70: field2
  thisObj[0x1D] = defaultInt4;      // +0x74: field3
  thisObj[0x1E] = defaultInt5;      // +0x78: field4
  thisObj[0x1F] = defaultInt;       // +0x7C: field5

  // Offset 0x60-0x68: Set to zero
  thisObj[0x18] = 0;                // +0x60: someArray[0] or field6
  thisObj[0x19] = defaultInt;       // +0x64: field7 (same as global)
  thisObj[0x1A] = defaultInt;       // +0x68: field8

  // Offset 0x10-0x4C: Array of fields with alternating defaults and zeros
  thisObj[4] = defaultInt;          // +0x10: member0
  thisObj[5] = 0;                   // +0x14: member1
  thisObj[6] = 0;                   // +0x18: member2
  thisObj[7] = 0;                   // +0x1C: member3
  thisObj[8] = 0;                   // +0x20: member4
  thisObj[9] = defaultInt;          // +0x24: member5
  thisObj[10] = 0;                  // +0x28: member6
  thisObj[0xB] = 0;                // +0x2C: member7
  thisObj[0xC] = 0;                // +0x30: member8
  thisObj[0xD] = 0;                // +0x34: member9
  thisObj[0xE] = defaultInt;       // +0x38: member10
  thisObj[0xF] = 0;                // +0x3C: member11
  thisObj[0x10] = 0;               // +0x40: member12
  thisObj[0x11] = 0;               // +0x44: member13
  thisObj[0x12] = 0;               // +0x48: member14
  thisObj[0x13] = defaultInt;      // +0x4C: member15

  return;
}