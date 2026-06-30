// FUNC_NAME: NetObject::initialize
void NetObject::initialize(int param_1, int param_2, uint param_3)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *unaff_ESI;
  undefined4 *unaff_EDI;
  
  puVar1 = (undefined4 *)unaff_ESI[0x10]; // +0x40: current ghost info
  if (puVar1 != unaff_EDI) {
    if (((puVar1 != (undefined4 *)0x0) && (*(short *)(puVar1 + 1) != 0)) &&
       (*(short *)((int)puVar1 + 6) = *(short *)((int)puVar1 + 6) + -1,
       *(short *)((int)puVar1 + 6) == 0)) {
      (**(code **)*puVar1)(1); // release ghost reference
    }
    unaff_ESI[0x10] = unaff_EDI; // +0x40: set new ghost info
    if ((unaff_EDI != (undefined4 *)0x0) && (*(short *)(unaff_EDI + 1) != 0)) {
      *(short *)((int)unaff_EDI + 6) = *(short *)((int)unaff_EDI + 6) + 1; // increment ref count
    }
  }
  unaff_ESI[0x11] = param_2; // +0x44: store parameter 2
  if (param_1 == 0) {
    FUN_0045cbe0(); // clear some state
    uVar2 = DAT_00e2b1a4;
    *unaff_ESI = DAT_00e2b1a4; // +0x00: set base value
    unaff_ESI[5] = uVar2; // +0x14
    unaff_ESI[10] = uVar2; // +0x28
    unaff_ESI[0xf] = 0; // +0x3c
    unaff_ESI[0xe] = 0; // +0x38
    unaff_ESI[0xd] = 0; // +0x34
    unaff_ESI[0xc] = 0; // +0x30
LAB_00556d2f:
    if (param_2 != 0) {
      uVar3 = FUN_0043b490(); // get some ID/timestamp
      goto LAB_00556d3e;
    }
  }
  else {
    FUN_005420c0(param_1 + 0xe0); // initialize from param_1 + 0xe0
    if (param_2 != 0) {
      FUN_00556fd0(param_1); // setup from param_1
      iVar4 = 0;
      if (*(int *)(param_1 + 0xc) != 0) {
        iVar4 = *(int *)(param_1 + 0xc);
      }
      if (unaff_ESI[0x18] != iVar4) { // +0x60: update some value
        unaff_ESI[0x18] = iVar4;
      }
      goto LAB_00556d2f;
    }
  }
  uVar3 = 0;
LAB_00556d3e:
  *(ulonglong *)(unaff_ESI + 0x13) = // +0x4c: pack network ID
       CONCAT44(*(undefined4 *)(*(int *)(DAT_01223480 + 0x54) + 0x34 + param_3 * 4),
                (uVar3 & 0xfff) << 0x10 | param_3 & 0x1f) | 0x3e0;
  *(undefined8 *)(unaff_ESI + 0x15) = 0xffffffff; // +0x54: set to -1
  unaff_ESI[0x17] = 0; // +0x5c: clear
  return;
}