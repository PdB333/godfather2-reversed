// FUNC_NAME: UIWidget::initFromDefinition
undefined4 * __thiscall UIWidget::initFromDefinition(undefined4 *thisObj, int definition, undefined4 someParam)
{
  uint hash;
  int copyVal;
  undefined4 *entryPtr;
  bool hasScale9;
  char charValue;
  undefined4 result;
  uint index;
  int *propEntry;

  // Call base class constructor or some initialization
  FUN_004a7560(definition, someParam);

  // Global data reference
  result = DAT_0110ac04;

  // Set vtable
  *thisObj = &PTR_FUN_00e2f720;

  // Initialize fields to zero (offset 0x04 to 0x24)
  thisObj[4] = 0;
  thisObj[5] = 0;
  thisObj[6] = 0;
  thisObj[7] = 0;
  thisObj[8] = 0;
  thisObj[9] = 0;

  // Default texture/sprite references (offset 0x28 and 0x2c)
  thisObj[0xb] = result;
  thisObj[0xa] = result;

  // Flags and state bytes
  *(byte *)((int)thisObj + 0x30) = 0;   // +0x30: some byte flag
  *(byte *)((int)thisObj + 0x31) = 1;   // +0x31: bitfield (initially 1)
  *(byte *)((int)thisObj + 0x32) = 0;   // +0x32: extra flag

  index = 0;
  charValue = '\0';
  hasScale9 = false;

  // Check if definition has properties
  if (*(short *)(definition + 0x20) != 0) {
    do {
      propEntry = *(int **)(*(int *)(definition + 0x1c) + index * 4);
      hash = propEntry[4];  // property identifier hash

      if (hash < 0x6b133109) {
        if (hash == 0x6b133108) {
          // "visible" or "enabled" property?
          if (*(char *)propEntry != '\0') {
            *(byte *)((int)thisObj + 0x31) |= 2;  // set bit 1
          }
        }
        else if (hash == 0x2a9ee1e3) {
          // Some character property (fontChar?)
          charValue = *(char *)propEntry;
        }
        else if (hash == 0x3a813f08) {
          // Position/Size rectangle (offset 0x10 - 0x1c)
          copyVal = *propEntry;  // pointer to rect struct
          thisObj[4] = *(undefined4 *)(copyVal + 0xc);
          thisObj[5] = *(undefined4 *)(copyVal + 0x10);
          thisObj[6] = *(undefined4 *)(copyVal + 0x14);
          thisObj[7] = *(undefined4 *)(copyVal + 0x18);
        }
      }
      else if (hash == 0x6f4556d6) {
        // "texture" or "sprite" property
        copyVal = *propEntry;
        thisObj[10] = copyVal;
        thisObj[0xb] = copyVal;
        hasScale9 = true;
      }
      else if (hash == 0x886ea447) {
        // Some byte flag (maybe alignment?)
        *(char *)((int)thisObj + 0x30) = *(char *)propEntry;
      }
      index++;
    } while (index < *(ushort *)(definition + 0x20));

    // If texture was set, we're done
    if (hasScale9) {
      return thisObj;
    }

    // If there is a charValue, try to resolve a font/texture from it
    if (charValue != '\0') {
      result = (*(code *)PTR_FUN_0110ac0c)(charValue);
      thisObj[0xb] = result;
      thisObj[10] = result;
      return thisObj;
    }
  }

  // Fallback: search for a "ninepatch" or "scale9" property by hash 0x136decc4
  index = 0;
  if (*(ushort *)(definition + 0x20) != 0) {
    propEntry = *(int **)(definition + 0x1c);
    while (true) {
      entryPtr = (undefined4 *)*propEntry;
      if (entryPtr[4] == 0x136decc4) {
        break;
      }
      index++;
      propEntry++;
      if (*(ushort *)(definition + 0x20) <= index) {
        return thisObj;
      }
    }
    // Check if we found the entry and it's of type 2 (scale9 grid)
    if ((entryPtr != (undefined4 *)0x0) && (entryPtr[5] == 2)) {
      result = (*(code *)PTR_FUN_0110ac08)(*entryPtr);
      thisObj[0xb] = result;
      thisObj[10] = result;
    }
  }
  return thisObj;
}