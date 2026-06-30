// FUNC_NAME: mapKeyToValue
unsigned int __fastcall mapKeyToValue(unsigned int key)
{
  int index;
  
  index = 0;
  key = key & 0xFFFF;
  do {
    // Check four separate key tables (each 16-bit entries) at current index
    if (g_keyTable1[index * 2] == key) break;                    // +0x00 (base: 0x00e2e3dc)
    if (g_keyTable2[index * 2] == key) {                         // +0x00 (base: 0x00e2e3e4)
      return g_valueTable2[index * 2];                           // +0x00 (base: 0x00e2e3e0)
    }
    if (g_keyTable3[index * 2] == key) {                         // +0x00 (base: 0x00e2e3ec)
      return g_valueTable3[index * 2];                           // +0x00 (base: 0x00e2e3e8)
    }
    if (g_keyTable4[index * 2] == key) {                         // +0x00 (base: 0x00e2e3f4)
      return g_valueTable4[index * 2];                           // +0x00 (base: 0x00e2e3f0)
    }
    index += 4;
  } while (index < 16);
  // Default: return value from table0 (no match)
  return g_valueTable0[index * 2];                               // +0x00 (base: 0x00e2e3d8)
}