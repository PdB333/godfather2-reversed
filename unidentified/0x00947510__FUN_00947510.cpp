// FUNC_NAME: UnknownClass::updateActionState
void __fastcall updateActionState(int this)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 local_28;
  undefined8 local_20;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  code *local_c;
  undefined4 local_8;
  undefined4 local_4;

  if (*(int *)(this + 0x148) != 0) {
    return;
  }
  local_4 = *(undefined4 *)(this + 0x11c);
  local_28 = *(undefined8 *)(this + 0x10c);
  local_20 = *(undefined8 *)(this + 0x114);
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = (code *)0x0;
  local_8 = 1;
  switch(*(int *)(this + 0x54)) {
  case 0:
    uVar2 = FUN_0094ca20(*(undefined4 *)(this + 0x50),this + 0x70,this + 0xd0,
                         *(undefined4 *)(this + 0xfc),*(undefined4 *)(this + 0xe0),
                         *(undefined4 *)(this + 0xe8),*(undefined4 *)(this + 0xc0),
                         this + 0xb4,*(undefined4 *)(this + 0x104),
                         *(undefined4 *)(this + 0x100),&local_28,0);
    break;
  case 1:
  case 4:
    if (*(int *)(this + 0x54) == 1) {
      iVar3 = FUN_009471d0();
    }
    else if (**(int **)(DAT_012233a0 + 4) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
    }
    if ((*(int *)(this + 0x50) == 0x25) && (cVar1 = FUN_0089c630(), cVar1 != '\0')) {
      *(undefined4 *)(this + 0xe0) = 0;
    }
    if (iVar3 == 0) goto switchD_00947577_default;
    uVar2 = FUN_0094cc00(*(undefined4 *)(this + 0x50),iVar3,this + 0xd0,
                         *(undefined4 *)(this + 0xfc),*(undefined4 *)(this + 0xe0),
                         *(undefined4 *)(this + 0xe4),*(undefined4 *)(this + 0xe8),
                         *(undefined4 *)(this + 0xec),*(undefined4 *)(this + 0xc0),
                         this + 0xb4,*(undefined4 *)(this + 0x104),
                         *(undefined4 *)(this + 0x100),&local_28);
    break;
  case 2:
    iVar3 = FUN_00947210();
    if (iVar3 == 0) goto switchD_00947577_default;
    uVar2 = FUN_0094cd40(*(undefined4 *)(this + 0x50),iVar3,this + 0xd0,
                         *(undefined4 *)(this + 0xfc),*(undefined4 *)(this + 0xe0),
                         *(undefined4 *)(this + 0xe4),*(undefined4 *)(this + 0xe8),
                         *(undefined4 *)(this + 0xc0),this + 0xb4,
                         *(undefined4 *)(this + 0x104),*(undefined4 *)(this + 0x100),&local_28
                        );
    break;
  case 3:
    uVar2 = FUN_0094ce60(*(undefined4 *)(this + 0x50),*(undefined4 *)(this + 0xb0),
                         *(undefined4 *)(this + 0xfc),*(undefined4 *)(this + 0xe0),
                         *(undefined4 *)(this + 0xc0),this + 0xb4,
                         *(undefined4 *)(this + 0x104));
    break;
  case 5:
  case 6:
    uVar2 = FUN_00947250();
    if (*(int *)(this + 0x54) == 6) {
      iVar3 = this + 0x70;
    }
    else {
      iVar3 = 0;
    }
    uVar2 = FUN_0094cf40(*(undefined4 *)(this + 0x50),uVar2,iVar3,this + 0xd0,
                         *(undefined4 *)(this + 0xfc),*(undefined4 *)(this + 0xe0),
                         *(undefined4 *)(this + 0xe4),*(undefined4 *)(this + 0xe8),
                         *(undefined4 *)(this + 0xec),*(undefined4 *)(this + 0xc0),
                         this + 0xb4,*(undefined4 *)(this + 0x104),
                         *(undefined4 *)(this + 0x100),&local_28);
    break;
  default:
    goto switchD_00947577_default;
  }
  *(undefined4 *)(this + 0x148) = uVar2;
switchD_00947577_default:
  if (*(int *)(this + 0x148) != 0) {
    FUN_00949d10(*(int *)(this + 0x148),*(byte *)(this + 0x108) & 1);
    FUN_00949d50(*(undefined4 *)(this + 0x148),*(undefined4 *)(this + 0xf0),
                 *(undefined4 *)(this + 0xf4),*(undefined4 *)(this + 0xf8));
    if (*(int *)(this + 0xec) == 2) {
      FUN_0094ac00(*(undefined4 *)(this + 0x148),*(undefined1 *)(this + 0x14c),
                   *(undefined1 *)(this + 0x14d),*(undefined1 *)(this + 0x14e));
    }
    *(uint *)(this + 0x108) = *(uint *)(this + 0x108) | 4;
  }
  if (DAT_01130638 == '\0') {
    FUN_004a8f30(this);
    FUN_009473d0();
  }
  if (local_18 != 0) {
    (*local_c)(local_18);
  }
  return;
}