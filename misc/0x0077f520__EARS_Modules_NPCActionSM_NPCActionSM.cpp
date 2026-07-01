// Xbox PDB: EARS_Modules_NPCActionSM_NPCActionSM
// FUNC_NAME: NPC::init
undefined4 * __thiscall NPC::init(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0073e160(param_2,param_3);
  uVar2 = DAT_00d5ccf8;
  *this = &PTR_LAB_00d6924c;
  this[0x1c] = 0; // +0x70 - some pointer
  this[0x1d] = 0; // +0x74
  piVar1 = this + 0x1c;
  this[0x1e] = 0; // +0x78
  this[0x1f] = 0; // +0x7c
  *(undefined1 *)(this + 0x20) = 0; // +0x80 - byte
  *(undefined1 *)((int)this + 0x81) = 0; // +0x81 - byte
  this[0x22] = uVar2; // +0x88 - some value
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
    *piVar1 = 0;
  }
  iVar3 = this[0x17]; // +0x5c - pointer to some sub-object
  piVar1 = (int *)(iVar3 + 0x256c);
  *(undefined4 *)(iVar3 + 0x2564) = DAT_00d5ccf8; // +0x2564
  *(undefined4 *)(iVar3 + 0x2568) = 0; // +0x2568
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
    *piVar1 = 0;
  }
  *(undefined4 *)(iVar3 + 0x2578) = 0; // +0x2578
  FUN_009c8f10(*(undefined4 *)(iVar3 + 0x2574)); // +0x2574
  *(undefined4 *)(iVar3 + 0x2574) = 0; // +0x2574
  *(undefined4 *)(iVar3 + 0x257c) = 0; // +0x257c
  FUN_007f74f0();
  FUN_007f62b0();
  *(uint *)(iVar3 + 0x974) = *(uint *)(iVar3 + 0x974) | 1; // +0x974 - set bit 0
  FUN_00408240(&DAT_0112af44,"iMsgNpcCower");
  FUN_00408240(&DAT_0112af3c,"iMsgNpcFlee");
  iVar3 = _rand();
  this[0x21] = (float)iVar3 * DAT_00e44590 * DAT_00d5f520 + DAT_00d5f378; // +0x84 - random float
  return this;
}