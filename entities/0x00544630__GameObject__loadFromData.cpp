// FUNC_NAME: GameObject::loadFromData
void __thiscall GameObject::loadFromData(GameObject *this, undefined4 paramData)
{
  int iCurObj;
  char cFound;
  int iVar2;
  undefined4 *pCurField;
  undefined4 **ppFieldIter;
  undefined4 unaff_EBX;
  undefined4 **ppFieldIter2;
  uint uFieldIndex;
  bool bValid;
  int *piStack_84; // Pointer to a node/object
  undefined4 *puStack_80; // Pointer B
  undefined4 *puStack_7c; // Pointer C
  undefined4 *puStack_78; // Pointer D
  char cStack_70; // flag: 0=simple list, 1=bitmasked
  int iStack_6c; // bitmask pointer
  undefined4 *puStack_68; // data pointer
  uint uStack_64; // current index
  uint uStack_60; // total count
  undefined4 *puStack_5c; // temp field
  undefined2 uStack_58; // short index
  undefined4 uStack_54; // temp value
  undefined4 **ppuStack_14; // field iterator

  FUN_00542b60(paramData); // likely base class init
  cFound = (this->vtable->method_0x198)(); // e.g., isInitialized?
  if (cFound == '\0') {
    iVar2 = FUN_004b9ca0(paramData,0x33a16735); // lookup string ID
    if (iVar2 == 0) {
      iVar2 = 0;
    } else {
      iVar2 = *(int *)(iVar2 + 0x14); // get some field
    }
    if (iVar2 != 0) {
      iVar2 = *(int *)(iVar2 + 8);
      iCurObj = *(int *)(iVar2 + 0xc);
      piStack_84 = (int *)0x0;
      do {
        iCurObj = iCurObj + -1;
        if (iCurObj < 0) goto LAB_005446ca;
        piStack_84 = *(int **)(*(int *)(iVar2 + 8) + iCurObj * 4);
        cFound = (this->vtable->method_0x24c)(piStack_84); // e.g., matchesType?
      } while (cFound == '\0');
      iVar2 = (piStack_84->vtable->method_0x18)(); // get some id/pointer
      this->mField_0xba = iVar2; // offset 0x2E8
LAB_005446ca:
      iVar2 = this->mField_0xba;
      FUN_00556c80(piStack_84,this,5); // attach object to this
      *(uint *)(iVar2 + 0x2c) = (uint)(this + 0xbc) >> 2 | 0xc0000000; // set flags on external obj
      FUN_0043b490(); // some debug/stat?
      FUN_009f01f0(0x2001,this,0); // log?
      FUN_009f01a0(); // 
    }
    if (this->mField_0xba == 0) {
      iVar2 = FUN_005627a0(); // allocate object
      this->mField_0xba = iVar2;
      FUN_00556ab0(0,0,this,5,0xffffffff); // init/register
      *(uint *)(iVar2 + 0x2c) = (uint)(this + 0xbc) >> 2 | 0xc0000000;
      FUN_0043b490();
      FUN_009f01f0(0x2001,this,0);
      FUN_009f01a0();
    }
    if (this->mField_0xba != 0) {
      *(undefined2 *)(this->mField_0xba + 0x96) = 0; // init short at +0x96
    }
    if (this->mField_0xba != 0) {
      FUN_009f4240(4,1,0); // log category 4, level 1
      FUN_009f3cc0(2); // log output?
    }
  }
  // Parse data fields (likely binary stream)
  piStack_84 = (int *)DAT_00e39f98;
  puStack_80 = DAT_00e446f4;
  puStack_78 = DAT_00e39f98;
  puStack_7c = DAT_00e2e714;
  FUN_0043aff0(paramData,0x197c1972); // begin parsing stream
  ppFieldIter2 = ppuStack_14;
  uFieldIndex = uStack_64;
  while( true ) {
    if (cStack_70 == '\0') {
      bValid = *ppFieldIter2 == (undefined4 *)0x0;
    } else {
      bValid = uFieldIndex == uStack_60;
    }
    if (bValid) break;
    ppFieldIter = &puStack_5c;
    if (cStack_70 == '\0') {
      ppFieldIter = ppFieldIter2;
    }
    if (*(short *)((int)ppFieldIter + 6) == 0x25e3) { // tag value?
      pCurField = (undefined4 *)(uint)*(ushort *)(ppFieldIter + 1);
    } else {
      pCurField = ppFieldIter[1];
    }
    switch(pCurField) {
    case (undefined4 *)0xb: // tag 11
      ppFieldIter = &puStack_5c;
      if (cStack_70 == '\0') {
        ppFieldIter = ppFieldIter2;
      }
      piStack_84 = (int *)ppFieldIter[2];
      break;
    case (undefined4 *)0xc: // tag 12
      ppFieldIter = &puStack_5c;
      if (cStack_70 == '\0') {
        ppFieldIter = ppFieldIter2;
      }
      puStack_80 = ppFieldIter[2];
      break;
    case (undefined4 *)0xd: // tag 13 (ignored)
      break;
    case (undefined4 *)0xe: // tag 14
      ppFieldIter = &puStack_5c;
      if (cStack_70 == '\0') {
        ppFieldIter = ppFieldIter2;
      }
      puStack_7c = ppFieldIter[2];
      break;
    case (undefined4 *)0xf: // tag 15
      ppFieldIter = &puStack_5c;
      if (cStack_70 == '\0') {
        ppFieldIter = ppFieldIter2;
      }
      puStack_78 = ppFieldIter[2];
    }
    if (cStack_70 == '\0') {
      if ((int)uFieldIndex < 0) {
        ppuStack_14 = (undefined4 **)((int)ppFieldIter2 + (int)*ppFieldIter2);
        FUN_0043b140(); // advance iterator
        ppFieldIter2 = ppuStack_14;
        uFieldIndex = uStack_64;
      } else if ((int)uFieldIndex < (int)(uStack_60 - 1)) {
        uStack_64 = uFieldIndex + 1;
        ppuStack_14 = (undefined4 **)((int)ppFieldIter2 + (int)*ppFieldIter2);
        ppFieldIter2 = (undefined4 **)((int)ppFieldIter2 + (int)*ppFieldIter2);
        uFieldIndex = uStack_64;
      } else {
        ppuStack_14 = (undefined4 **)&DAT_01163cf8;
        ppFieldIter2 = (undefined4 **)&DAT_01163cf8;
      }
    } else {
      uStack_64 = uFieldIndex + 1;
      uFieldIndex = uStack_64;
      if (uStack_64 != uStack_60) {
        uStack_58 = (short)uStack_64;
        if ((*(byte *)((uStack_64 >> 3) + iStack_6c) & (byte)(1 << ((byte)uStack_64 & 7))) == 0) {
          puStack_5c = puStack_68;
          uStack_54 = *puStack_68;
          puStack_68 = puStack_68 + 1;
        }
        else {
          puStack_5c = (undefined4 *)0x0;
          uStack_54 = 0;
        }
      }
    }
  }
  (this->vtable->method_0x238)(paramData); // end parse?
  FUN_00546010(this); // post-init
  cFound = (this->vtable->method_0x198)();
  if (cFound == '\0') {
    (this->vtable->method_0x244)(); // update?
    if (this->mField_0xe4 != 0) { // offset 0x390
      (this->vtable->method_0x240)(); // activate?
    }
  }
  else {
    FUN_009f2000(); // error/cleanup?
  }
  if (this->mField_0xd8 != 0) { // offset 0x360, pointer to a structure
    *(undefined4 *)(this->mField_0xd8 + 0xfc) = unaff_EBX; // +0xFC
    *(int **)(this->mField_0xd8 + 0x100) = piStack_84; // +0x100
    *(undefined4 **)(this->mField_0xd8 + 0xf0) = puStack_80; // +0xF0
    *(undefined4 **)(this->mField_0xd8 + 0xf4) = puStack_7c; // +0xF4
    *(undefined4 **)(this->mField_0xd8 + 0xf8) = puStack_78; // +0xF8
  }
  return;
}