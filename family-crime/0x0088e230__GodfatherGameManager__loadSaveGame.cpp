// FUNC_NAME: GodfatherGameManager::loadSaveGame
void __thiscall GodfatherGameManager::loadSaveGame(int this, undefined4 saveData)
{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int *piVar5;
  undefined4 uVar6;
  void *pvVar7;
  int iVar8;
  uint uVar9;
  int local_140 [79]; // temporary hash storage
  
  FUN_0046c710(saveData); // begin reading save data
  if (*(int *)(this + 0x68) != 0) {
    FUN_009c8f10(*(int *)(this + 0x68)); // free existing hash array
    *(undefined4 *)(this + 0x68) = 0;
  }
  piVar5 = local_140;
  for (iVar8 = 0x4e; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar5 = -0x1e98fd1; // initial hash value
    piVar5 = piVar5 + 1;
  }
  *(undefined1 *)(this + 0x80) = 0; // hashCount1
  *(undefined1 *)(this + 0x81) = 0; // hashCount2
  *(undefined1 *)(this + 0x82) = 0; // hashCount3
  uVar9 = 0;
  FUN_0043aff0(saveData,0x999826da); // start reading section
  cVar4 = FUN_0043b120(); // check for more data
  if (cVar4 == '\\0') {
    do {
      FUN_0043b210(); // read next token
      iVar8 = FUN_0043ab70(); // get token type
      cVar4 = (char)uVar9;
      if (iVar8 - 2U < 0x32) { // hash type 1 (0x02-0x33)
        FUN_0043b210();
        piVar5 = (int *)FUN_0043abc0(); // read 4 ints
        iVar8 = *piVar5;
        if (((iVar8 != 0) || (piVar5[1] != 0)) || ((piVar5[2] != 0 || (piVar5[3] != 0)))) {
          iVar1 = piVar5[1];
          iVar2 = piVar5[2];
          iVar3 = piVar5[3];
          *(char *)(this + 0x80) = *(char *)(this + 0x80) + '\\x01';
          local_140[uVar9] = ((iVar8 * 0x21 + iVar1) * 0x21 + iVar2) * 0x21 + iVar3;
          uVar9 = (uint)(byte)(cVar4 + 1);
        }
      }
      else if (iVar8 - 0x34U < 8) { // hash type 2 (0x34-0x3B)
        FUN_0043b210();
        piVar5 = (int *)FUN_0043abc0();
        iVar8 = *piVar5;
        if (((iVar8 != 0) || (piVar5[1] != 0)) || ((piVar5[2] != 0 || (piVar5[3] != 0)))) {
          iVar1 = piVar5[1];
          iVar2 = piVar5[2];
          iVar3 = piVar5[3];
          *(char *)(this + 0x81) = *(char *)(this + 0x81) + '\\x01';
          local_140[uVar9] = ((iVar8 * 0x21 + iVar1) * 0x21 + iVar2) * 0x21 + iVar3;
          uVar9 = (uint)(byte)(cVar4 + 1);
        }
      }
      else if (iVar8 - 0x3cU < 0x14) { // hash type 3 (0x3C-0x4F)
        FUN_0043b210();
        piVar5 = (int *)FUN_0043abc0();
        iVar8 = *piVar5;
        if ((((iVar8 != 0) || (piVar5[1] != 0)) || (piVar5[2] != 0)) || (piVar5[3] != 0)) {
          iVar1 = piVar5[1];
          iVar2 = piVar5[2];
          iVar3 = piVar5[3];
          *(char *)(this + 0x82) = *(char *)(this + 0x82) + '\\x01';
          local_140[uVar9] = ((iVar8 * 0x21 + iVar1) * 0x21 + iVar2) * 0x21 + iVar3;
          uVar9 = (uint)(byte)(cVar4 + 1);
        }
      }
      else {
        switch(iVar8) {
        case 0: // string field at +0x50
          FUN_0043b210();
          uVar6 = FUN_0043ab90();
          FUN_004089b0(this + 0x50,uVar6);
          break;
        case 1: // string field at +0x58
          FUN_0043b210();
          uVar6 = FUN_0043ab90();
          FUN_00408980(this + 0x58,uVar6);
          break;
        case 0x50: // byte field at +0x83
          iVar8 = FUN_0043b210();
          *(undefined1 *)(this + 0x83) = *(undefined1 *)(iVar8 + 8);
          break;
        case 0x51: // byte field at +0x84
          iVar8 = FUN_0043b210();
          *(undefined1 *)(this + 0x84) = *(undefined1 *)(iVar8 + 8);
          break;
        case 0x52: // string field at +0x60
          FUN_0043b210();
          uVar6 = FUN_0043ab90();
          FUN_00408980(this + 0x60,uVar6);
          break;
        case 0x53: // int field at +0x6c (shifted)
          iVar8 = FUN_0043b210();
          *(int *)(this + 0x6c) = *(int *)(iVar8 + 8) << 0x14;
          break;
        case 0x54: // array at +0x70
          iVar8 = this + 0x70;
          FUN_0043b210(iVar8);
          FUN_0043ad10(iVar8);
        }
      }
      FUN_0043b1a0(); // end token
      cVar4 = FUN_0043b120(); // check for more
    } while (cVar4 == '\\0');
    if ((char)uVar9 != '\\0') {
      pvVar7 = (void *)FUN_009c8e80(uVar9 * 4); // allocate hash array
      if (pvVar7 == (void *)0x0) {
        pvVar7 = (void *)0x0;
      }
      else {
        _vector_constructor_iterator_(pvVar7,4,uVar9,(_func_void_ptr_void_ptr *)&LAB_00401f30);
      }
      *(void **)(this + 0x68) = pvVar7;
      if ((char)uVar9 != '\\0') {
        iVar8 = 0;
        do {
          *(undefined4 *)(iVar8 + *(int *)(this + 0x68)) =
               *(undefined4 *)((int)local_140 + iVar8);
          iVar8 = iVar8 + 4;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
      }
    }
  }
  return;
}