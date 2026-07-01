// Xbox PDB: EARS_Apt_UIHud_HideWeaponWheel
// FUNC_NAME: PlayerSM::exitWeaponWheel
void __fastcall PlayerSM::exitWeaponWheel(int this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // If current state is not 0xf (WeaponWheel), exit it
  if (*(int *)(this + 0xec) != 0xf) {
    FUN_006915e0(*(int *)(this + 0xec));
    *(undefined4 *)(this + 0xec) = 0xf;
  }
  *(undefined4 *)(this + 0xf4) = 0;
  
  iVar2 = **(int **)(DAT_012233a0 + 4);
  if ((iVar2 != 0) && ((int *)(iVar2 + -0x1f30) != (int *)0x0)) {
    // Clear some flags on the player object
    *(uint *)(iVar2 + 0x570) = *(uint *)(iVar2 + 0x570) & 0xffefffff;
    *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) & 0xfffffff7;
    
    if (*(int *)(this + 0xd4) == 10) {
      // If current weapon is 10 (likely fists/unarmed)
      if ((*(uint *)(iVar2 + -0x1650) >> 10 & 1) != 0) {
        *(uint *)(iVar2 + 0x570) = *(uint *)(iVar2 + 0x570) | 0x80000;
        *(uint *)(iVar2 + 0x56c) = *(uint *)(iVar2 + 0x56c) & 0xfffdffff;
        if (*(int *)(iVar2 + -0x17e4) == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + -0x17e4) + -0x48;
        }
        FUN_00690820(iVar2);
      }
    }
    else {
      iVar1 = FUN_00705ab0(*(int *)(this + 0xd4));
      if (*(int *)(iVar2 + -0x17e4) == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar2 + -0x17e4) + -0x48;
      }
      if (iVar1 == 0) {
        if ((iVar3 != 0) && ((*(uint *)(iVar2 + -0x1650) >> 10 & 1) != 0)) {
          FUN_0093b6a0(iVar3,0);
        }
      }
      else if ((*(uint *)(iVar2 + -0x1650) >> 10 & 1) == 0) {
        (**(code **)(*(int *)(iVar2 + -0x1f30) + 600))(iVar1);
        *(uint *)(iVar2 + 0x56c) = *(uint *)(iVar2 + 0x56c) | 0x20000;
        FUN_00704b60(*(undefined4 *)(this + 0xd4));
      }
      else if (iVar1 == iVar3) {
        FUN_0093b6a0(iVar1,0);
      }
      else {
        FUN_00690820(iVar1);
        FUN_006901e0(0x11);
        FUN_006901e0(0x33);
        FUN_00704b60(*(undefined4 *)(this + 0xd4));
      }
    }
    FUN_005a04a0("HideWeaponWheel",0,&DAT_00d8a64c,0);
    if ((*(int *)(this + 0x60) == 0) && ((*(uint *)(this + 0x5c) & 0x40000008) == 0)) {
      FUN_005c1b40();
    }
    local_c = DAT_01130290;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    if (*(int *)(DAT_01223484 + 0xc) != 0) {
      FUN_0094dc50(1);
    }
  }
  return;
}