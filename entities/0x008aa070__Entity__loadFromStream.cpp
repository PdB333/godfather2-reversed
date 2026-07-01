// FUNC_NAME: Entity::loadFromStream
void __thiscall Entity::loadFromStream(int this, int streamHandle)
{
  char isEnd;
  int opcode;
  int* pInt;
  int intValue;
  char* strValue;
  int roundedFloat;

  openStream(streamHandle);
  registerHash(streamHandle, 0xb390b11a);
  pushContext(1);
  registerHash(streamHandle, 0xfc175d4a);
  isEnd = isEndOfStream();
  while (isEnd == '\0') {
    advanceStream();
    opcode = readOpcode();
    switch(opcode) {
    case 0: // Quaternion / 4 floats at +0x134
      advanceStream();
      pInt = (int*)read4Floats();
      *(int*)(this + 0x134) = *pInt;          // +0x134 quatX
      *(int*)(this + 0x138) = pInt[1];        // +0x138 quatY
      *(int*)(this + 0x13c) = pInt[2];        // +0x13c quatZ
      *(int*)(this + 0x140) = pInt[3];        // +0x140 quatW
      break;
    case 1: // Flag bit 2 at +0x7c
      intValue = advanceStream();
      if (*(int*)(intValue + 8) == 0) {
        *(unsigned int*)(this + 0x7c) &= 0xfffffffb; // clear bit 2
      } else {
        *(unsigned int*)(this + 0x7c) |= 4;          // set bit 2
      }
      break;
    case 2: // Some integer at +0x130
      intValue = advanceStream();
      *(int*)(this + 0x130) = *(int*)(intValue + 8);
      break;
    case 3: // Integer at +0x12c (300)
      intValue = advanceStream();
      *(int*)(this + 0x12c) = *(int*)(intValue + 8);
      break;
    case 4: // Integer at +0x144
      intValue = advanceStream();
      *(int*)(this + 0x144) = *(int*)(intValue + 8);
      break;
    case 5: // String resolved to ID at +0x108
      advanceStream();
      strValue = readString();
      strValue = (char*)resolveStringToId((int)strValue);
      *(int*)(this + 0x108) = (int)strValue;
      break;
    case 6: // Integer at +0x17c
      intValue = advanceStream();
      *(int*)(this + 0x17c) = *(int*)(intValue + 8);
      break;
    case 7: // Integer at +0x180
      intValue = advanceStream();
      *(int*)(this + 0x180) = *(int*)(intValue + 8);
      break;
    case 8: // String -> load resource
      advanceStream();
      strValue = readString();
      loadResource(strValue);
      break;
    case 9: // Integer * 1000 at +0x98
      intValue = advanceStream();
      *(int*)(this + 0x98) = *(int*)(intValue + 8) * 1000;
      break;
    case 10: // Integer * 1000 at +0x9c
      intValue = advanceStream();
      *(int*)(this + 0x9c) = *(int*)(intValue + 8) * 1000;
      break;
    case 0xb: // Float rounded to int at +0x90
      intValue = advanceStream();
      roundedFloat = (int)(*(float*)(intValue + 8) * (float)0x00d73d00); // Some global constant
      *(int*)(this + 0x90) = roundedFloat;
      break;
    case 0xc: // Integer at +0x94
      intValue = advanceStream();
      *(int*)(this + 0x94) = *(int*)(intValue + 8);
      break;
    case 0xd: // Integer at +0x118
      intValue = advanceStream();
      *(int*)(this + 0x118) = *(int*)(intValue + 8);
      break;
    case 0xe: // Integer at +0x120
      intValue = advanceStream();
      *(int*)(this + 0x120) = *(int*)(intValue + 8);
      break;
    case 0xf: // Integer at +0x128
      intValue = advanceStream();
      *(int*)(this + 0x128) = *(int*)(intValue + 8);
      break;
    case 0x10: // String at +0xa0
      advanceStream();
      strValue = readString();
      copyString(this + 0xa0, strValue);
      break;
    case 0x11: // String at +0xa8
      advanceStream();
      strValue = readString();
      copyString(this + 0xa8, strValue);
      break;
    case 0x12: // String at +0xb0
      advanceStream();
      strValue = readString();
      copyString(this + 0xb0, strValue);
      break;
    case 0x13: // String at +0xb8
      advanceStream();
      strValue = readString();
      copyString(this + 0xb8, strValue);
      break;
    case 0x14: // Transform at +0x14c
      intValue = this + 0x14c;
      advanceStream(intValue);   // Actually advanceStream is called with intValue? But original code: FUN_0043b210(iVar4) then FUN_0043ad10(iVar4)
      readTransform(intValue);
      break;
    case 0x15: // Integer at +0x184
      intValue = advanceStream();
      *(int*)(this + 0x184) = *(int*)(intValue + 8);
      break;
    }
    advanceStream();
    isEnd = isEndOfStream();
  }
  finalizeInit(this);
  return;
}