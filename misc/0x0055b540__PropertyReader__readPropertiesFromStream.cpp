// FUNC_NAME: PropertyReader::readPropertiesFromStream
void __thiscall PropertyReader::readPropertiesFromStream(int *thisPtr, undefined4 streamHandle)
{
  // +0x1e4 (0x790) : int field_A
  // +0x1e6 (0x798) : int field_B
  // +0x1e7 (0x79c) : int field_C
  // +0x1e5 (0x794) : int field_D
  // +0x1c8 (0x720) : int field_E[4]
  // +0x1cc (0x730) : int field_F[4]

  undefined4 **ppuVar1;
  undefined4 *puVar2;
  undefined4 **ppuVar3;
  uint uVar4;
  bool bVar5;
  char isSparse; // local_64
  int bitmaskBase; // iStack_60
  undefined4 *dataPointer; // puStack_5c
  uint currentIndex; // local_58
  uint maxIndex; // local_54
  undefined4 *currentElement; // local_50
  short indexShort; // uStack_4c
  undefined4 elementData; // uStack_48
  undefined4 **currentNode; // local_8

  initPropertyReader(streamHandle);
  setLookupHash(streamHandle, 0x55645e11);
  ppuVar3 = currentNode;
  uVar4 = currentIndex;

  while (true) {
    // Determine end condition based on mode
    if (isSparse == '\0') {
      // Linked-list mode: end when node pointer is null
      bVar5 = *ppuVar3 == (undefined4 *)0x0;
    }
    else {
      // Sparse mode: end when index reaches max
      bVar5 = uVar4 == maxIndex;
    }
    if (bVar5) break;

    // Determine element pointer
    if (isSparse == '\0') {
      ppuVar1 = ppuVar3;
    }
    else {
      ppuVar1 = &currentElement;
    }

    // Read key from element
    // Extended format flag at offset 6
    if (*(short *)((int)ppuVar1 + 6) == 0x25e3) {
      puVar2 = (undefined4 *)(uint)*(ushort *)(ppuVar1 + 1); // key as ushort
    }
    else {
      puVar2 = ppuVar1[1]; // key as full dword
    }

    // Keys 1-4: call virtual handler
    if ((int)puVar2 - 1U < 4) {
      // Determine value pointer
      if (isSparse == '\0') {
        ppuVar1 = ppuVar3;
      }
      else {
        ppuVar1 = &currentElement;
      }
      if (*(short *)((int)ppuVar1 + 6) == 0x25e3) {
        // Extended: value is after inline data
        if (*ppuVar1 == (undefined4 *)0x0) {
          ppuVar1 = (undefined4 **)&DAT_00e2a89b; // default value?
        }
        else {
          ppuVar1 = (undefined4 **)((int)ppuVar1[2] + (int)*ppuVar1);
        }
      }
      else {
        ppuVar1 = ppuVar1 + 2; // skip key to get value
      }
      // Call virtual method at vtable+0x94 with this+offset (puVar2+0x3a) and value
      (**(code **)(*thisPtr + 0x94))(thisPtr + (int)(puVar2 + 0x3a), ppuVar1);
      ppuVar3 = currentNode;
      uVar4 = currentIndex;
    }
    else {
      // Handle keys 5-10 directly
      switch(puVar2) {
      case (undefined4 *)0x5:
        // Assign value to field at +0x790 (thisPtr[0x1e4])
        if (isSparse == '\0') {
          ppuVar1 = ppuVar3;
        }
        else {
          ppuVar1 = &currentElement;
        }
        thisPtr[0x1e4] = (int)ppuVar1[2]; // +0x790
        break;

      case (undefined4 *)0x6:
        // Assign value to field at +0x798 (thisPtr[0x1e6])
        if (isSparse == '\0') {
          ppuVar1 = ppuVar3;
        }
        else {
          ppuVar1 = &currentElement;
        }
        thisPtr[0x1e6] = (int)ppuVar1[2];
        break;

      case (undefined4 *)0x7:
        // Assign value to field at +0x79c (thisPtr[0x1e7])
        if (isSparse == '\0') {
          ppuVar1 = ppuVar3;
        }
        else {
          ppuVar1 = &currentElement;
        }
        thisPtr[0x1e7] = (int)ppuVar1[2];
        break;

      case (undefined4 *)0x8:
        // Assign value to field at +0x794 (thisPtr[0x1e5])
        if (isSparse == '\0') {
          ppuVar1 = ppuVar3;
        }
        else {
          ppuVar1 = &currentElement;
        }
        thisPtr[0x1e5] = (int)ppuVar1[2];
        break;

      case (undefined4 *)0x9:
        // Assign four dwords starting at +0x720 (thisPtr[0x1c8..0x1cb])
        if (isSparse == '\0') {
          ppuVar1 = ppuVar3;
        }
        else {
          ppuVar1 = &currentElement;
        }
        if (*(short *)((int)ppuVar1 + 6) == 0x25e3) {
          if (*ppuVar1 == (undefined4 *)0x0) {
            ppuVar1 = (undefined4 **)&DAT_0120e700; // default value
          }
          else {
            ppuVar1 = (undefined4 **)((int)ppuVar1[2] + (int)*ppuVar1);
          }
        }
        else {
          ppuVar1 = ppuVar1 + 2;
        }
        thisPtr[0x1c8] = (int)*ppuVar1;
        thisPtr[0x1c9] = (int)ppuVar1[1];
        thisPtr[0x1ca] = (int)ppuVar1[2];
        thisPtr[0x1cb] = (int)ppuVar1[3];
        break;

      case (undefined4 *)0xa:
        // Assign four dwords starting at +0x730 (thisPtr[0x1cc..0x1cf])
        if (isSparse == '\0') {
          ppuVar1 = ppuVar3;
        }
        else {
          ppuVar1 = &currentElement;
        }
        if (*(short *)((int)ppuVar1 + 6) == 0x25e3) {
          if (*ppuVar1 == (undefined4 *)0x0) {
            ppuVar1 = (undefined4 **)&DAT_0120e700; // default value
          }
          else {
            ppuVar1 = (undefined4 **)((int)ppuVar1[2] + (int)*ppuVar1);
          }
        }
        else {
          ppuVar1 = ppuVar1 + 2;
        }
        thisPtr[0x1cc] = (int)*ppuVar1;
        thisPtr[0x1cd] = (int)ppuVar1[1];
        thisPtr[0x1ce] = (int)ppuVar1[2];
        thisPtr[0x1cf] = (int)ppuVar1[3];
        break;
      }
    }

    // Advance to next element
    if (isSparse == '\0') {
      // Linked-list mode: nodes contain size prefix, go to next node
      if ((int)uVar4 < 0) {
        currentNode = (undefined4 **)((int)ppuVar3 + (int)*ppuVar3);
        advanceReader();
        ppuVar3 = currentNode;
        uVar4 = currentIndex;
      }
      else if ((int)uVar4 < (int)(maxIndex - 1)) {
        currentIndex = uVar4 + 1;
        currentNode = (undefined4 **)((int)ppuVar3 + (int)*ppuVar3);
        ppuVar3 = (undefined4 **)((int)ppuVar3 + (int)*ppuVar3);
        uVar4 = currentIndex;
      }
      else {
        currentNode = (undefined4 **)&DAT_01163cf8; // end marker
        ppuVar3 = (undefined4 **)&DAT_01163cf8;
      }
    }
    else {
      // Sparse mode: advance index, check bitmask
      currentIndex = uVar4 + 1;
      uVar4 = currentIndex;
      if (currentIndex != maxIndex) {
        indexShort = (short)currentIndex;
        if ((*(byte *)((currentIndex >> 3) + bitmaskBase) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
          elementData = *dataPointer;
          currentElement = dataPointer;
          dataPointer = dataPointer + 1;
        }
        else {
          currentElement = (undefined4 *)0x0;
          elementData = 0;
        }
      }
    }
  }
  return;
}