// FUNC_NAME: ReliablePacketWindow::processIncomingPacket
void ReliablePacketWindow::processIncomingPacket(int param_1, int* param_2)
{ // 0x004e5ee0
  uint *puVar1;
  char cVar2;
  int *piVar3;
  undefined4 uVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *unaff_EDI; // this (ecx)
  int unaff_FS_OFFSET;

  FUN_00533cc0(); // unknown init/check
  *unaff_EDI = &PTR_FUN_00e371e8; // set vtable
  if (*(char *)(param_1 + 0xd) == '\0') { // flag at param_1+0x0d
    iVar6 = DAT_0119478c + -1; // circular buffer index manipulation
    iVar8 = DAT_0119478c + 2;
    if (iVar6 < 0) {
      iVar6 = 0x13; // wrap around to 19
    }
    else if (0x13 < iVar8) {
      iVar8 = DAT_0119478c + -0x12; // adjust
    }
    (&DAT_01194790)[iVar6] = (&DAT_01194790)[iVar6] + (&DAT_01194790)[iVar8];
    DAT_0119478c = iVar6;
    if (((((*param_2 != 0 || param_2[1] != 0) || (param_2[2] != 0 || param_2[3] != 0)) && // data checks
         (uVar7 = FUN_004e9270(), uVar7 != 0)) && ((uVar7 != 0xffffffff && (uVar7 < 0x1000)))) &&
       ((uVar7 * 0x38 != -0x11a0f28 && // offset sanity (likely 0xEE5F0D8)
        (piVar3 = *(int **)(&DAT_011a0f38 + uVar7 * 0x38), piVar3 != (int *)0x0)))) {
      *piVar3 = *piVar3 + 1;
    }
    FUN_004e5310(unaff_EDI); // unknown call
    if ((*(char *)((int)param_2 + 0x11) != '\0') && // flag at param_2+0x11
       (uVar7 = (*(code *)PTR_FUN_0110ac0c)(), (*(uint *)(unaff_EDI[1] + 0x84) & uVar7) == 0)) {
      *(undefined1 *)(param_1 + 0xc) = 1;
      return;
    }
    unaff_EDI[10] = 0;
    unaff_EDI[0xb] = 0;
    uVar4 = DAT_00e2b1a4;
    unaff_EDI[9] = param_2; // store packet pointer at this+0x24
    unaff_EDI[0xc] = uVar4;
    *(undefined1 *)(unaff_EDI + 0x17) = 0;
    cVar2 = (char)param_2[4]; // character type from packet
    if ((cVar2 == '\n') || (cVar2 == '\x04')) {
      uVar5 = 0xffff;
    }
    else {
      uVar5 = *(ushort *)(*(int *)(unaff_EDI[1] + 0x10) + 0x1e); // read from another object
      if ((cVar2 == '\x03') && ((uVar5 & 0x300) == 0x100)) {
        uVar5 = uVar5 & 0xfeff;
      }
    }
    *(ushort *)(unaff_EDI + 3) = uVar5 & 0x7ff | 0x1000;
    FUN_004ebb40(); // repeated cleanup
    FUN_004ebb40();
    FUN_004ebb40();
    FUN_004ebb40();
    FUN_004ebb40();
    if ((*(byte *)(param_2 + 5) & 0x10) != 0) {
      puVar1 = (uint *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + unaff_EDI[4]);
      *puVar1 = *puVar1 | 0x20000000;
    }
  }
  return;
}