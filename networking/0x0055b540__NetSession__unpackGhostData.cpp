// FUNC_NAME: NetSession::unpackGhostData

void __thiscall NetSession::unpackGhostData(int *this, void *streamData)
{
  undefined4 **ppCurrentItem;
  undefined4 *pItemData;
  undefined4 **ppItemPtr;
  uint currentIndex;
  uint itemCount;
  bool bItemPresent;
  char bUseBitmask;
  int bitfieldBase;
  undefined4 *pBuffer;
  uint localIndex;
  uint localCount;
  undefined4 *currentItem;
  short localShort;
  undefined4 localWord;
  undefined4 **pItemStorage;
  
  beginDeserialization(streamData);
  validateMagicNumber(streamData, 0x55645e11);
  pItemStorage = pItemStorage;
  currentIndex = localIndex;
  while( true ) {
    if (bUseBitmask == 0) {
      bItemPresent = *pItemStorage == (undefined4 *)0x0;
    }
    else {
      bItemPresent = currentIndex == localCount;
    }
    if (bItemPresent) break;
    ppItemPtr = &currentItem;
    if (bUseBitmask == 0) {
      ppItemPtr = pItemStorage;
    }
    if (*(short *)((int)ppItemPtr + 6) == 0x25e3) {
      pItemData = (undefined4 *)(uint)*(ushort *)(ppItemPtr + 1);
    }
    else {
      pItemData = ppItemPtr[1];
    }
    if ((int)pItemData - 1 < 4) {
      ppItemPtr = &currentItem;
      if (bUseBitmask == 0) {
        ppItemPtr = pItemStorage;
      }
      if (*(short *)((int)ppItemPtr + 6) == 0x25e3) {
        if (*ppItemPtr == (undefined4 *)0x0) {
          ppItemPtr = (undefined4 **)&DAT_00e2a89b;
        }
        else {
          ppItemPtr = (undefined4 **)((int)ppItemPtr[2] + (int)*ppItemPtr);
        }
      }
      else {
        ppItemPtr = ppItemPtr + 2;
      }
      // virtual call at vtable+0x94: likely unpackGhostForIndex
      (*(void (**)(void *, undefined4 **))(this[0] + 0x94))(this + (int)(pItemData + 0x3a), ppItemPtr);
      pItemStorage = pItemStorage;
      currentIndex = localIndex;
    }
    else {
      switch(pItemData) {
      case (undefined4 *)0x5:
        ppItemPtr = &currentItem;
        if (bUseBitmask == 0) {
          ppItemPtr = pItemStorage;
        }
        this[0x1e4] = (int)ppItemPtr[2];
        break;
      case (undefined4 *)0x6:
        ppItemPtr = &currentItem;
        if (bUseBitmask == 0) {
          ppItemPtr = pItemStorage;
        }
        this[0x1e6] = (int)ppItemPtr[2];
        break;
      case (undefined4 *)0x7:
        ppItemPtr = &currentItem;
        if (bUseBitmask == 0) {
          ppItemPtr = pItemStorage;
        }
        this[0x1e7] = (int)ppItemPtr[2];
        break;
      case (undefined4 *)0x8:
        ppItemPtr = &currentItem;
        if (bUseBitmask == 0) {
          ppItemPtr = pItemStorage;
        }
        this[0x1e5] = (int)ppItemPtr[2];
        break;
      case (undefined4 *)0x9:
        ppItemPtr = &currentItem;
        if (bUseBitmask == 0) {
          ppItemPtr = pItemStorage;
        }
        if (*(short *)((int)ppItemPtr + 6) == 0x25e3) {
          if (*ppItemPtr == (undefined4 *)0x0) {
            ppItemPtr = (undefined4 **)&DAT_0120e700;
          }
          else {
            ppItemPtr = (undefined4 **)((int)ppItemPtr[2] + (int)*ppItemPtr);
          }
        }
        else {
          ppItemPtr = ppItemPtr + 2;
        }
        this[0x1c8] = (int)*ppItemPtr;
        this[0x1c9] = (int)ppItemPtr[1];
        this[0x1ca] = (int)ppItemPtr[2];
        this[0x1cb] = (int)ppItemPtr[3];
        break;
      case (undefined4 *)0xa:
        ppItemPtr = &currentItem;
        if (bUseBitmask == 0) {
          ppItemPtr = pItemStorage;
        }
        if (*(short *)((int)ppItemPtr + 6) == 0x25e3) {
          if (*ppItemPtr == (undefined4 *)0x0) {
            ppItemPtr = (undefined4 **)&DAT_0120e700;
          }
          else {
            ppItemPtr = (undefined4 **)((int)ppItemPtr[2] + (int)*ppItemPtr);
          }
        }
        else {
          ppItemPtr = ppItemPtr + 2;
        }
        this[0x1cc] = (int)*ppItemPtr;
        this[0x1cd] = (int)ppItemPtr[1];
        this[0x1ce] = (int)ppItemPtr[2];
        this[0x1cf] = (int)ppItemPtr[3];
      }
    }
    if (bUseBitmask == 0) {
      if ((int)currentIndex < 0) {
        pItemStorage = (undefined4 **)((int)pItemStorage + (int)*pItemStorage);
        FUN_0043b140(); // advance linked list
        pItemStorage = pItemStorage;
        currentIndex = localIndex;
      }
      else if ((int)currentIndex < (int)(localCount - 1)) {
        localIndex = currentIndex + 1;
        pItemStorage = (undefined4 **)((int)pItemStorage + (int)*pItemStorage);
        pItemStorage = (undefined4 **)((int)pItemStorage + (int)*pItemStorage);
        currentIndex = localIndex;
      }
      else {
        pItemStorage = (undefined4 **)&DAT_01163cf8;
        pItemStorage = (undefined4 **)&DAT_01163cf8;
      }
    }
    else {
      localIndex = currentIndex + 1;
      currentIndex = localIndex;
      if (localIndex != localCount) {
        localShort = (short)localIndex;
        if ((*(byte *)((localIndex >> 3) + bitfieldBase) & (byte)(1 << ((byte)localIndex & 7))) == 0) {
          localWord = *pBuffer;
          currentItem = pBuffer;
          pBuffer = pBuffer + 1;
        }
        else {
          currentItem = (undefined4 *)0x0;
          localWord = 0;
        }
      }
    }
  }
  return;
}