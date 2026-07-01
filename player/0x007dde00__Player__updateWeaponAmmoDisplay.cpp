// FUNC_NAME: Player::updateWeaponAmmoDisplay
void __fastcall Player::updateWeaponAmmoDisplay(int this)
{
  int iVar1;
  byte uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uStack_4;
  
  FUN_007f63e0(0x29); // likely some debug/profiling marker
  iVar3 = FUN_007ab1e0(); // get player state manager or similar
  iVar1 = *(int *)(this + 0x58); // +0x58: pointer to weapon/ammo data
  iVar5 = *(int *)(iVar3 + 0x340); // +0x340: current weapon slot index
  if (iVar5 == 0) {
    uStack_4 = *(undefined4 *)(iVar1 + 0x1dc0); // +0x1dc0: ammo count for slot 0
    uVar4 = *(uint *)(iVar1 + 0x8e0) >> 1; // +0x8e0: some flags, shift right 1
    iVar5 = (-(uint)((uVar4 & 1) != 0) & 0x70eebcfc) + 0x86b26309;
    if (*(int *)(iVar3 + 0x334) == 2) { // +0x334: maybe weapon type or mode
      uStack_4 = *(undefined4 *)(iVar1 + 0x1dd0); // +0x1dd0: alternate ammo count
      iVar5 = (-(uint)((uVar4 & 1) != 0) & 0xe967fefc) + 0x98540b3d;
    }
  }
  else if (iVar5 == 2) {
    uStack_4 = *(undefined4 *)(iVar1 + 0x1dc8); // +0x1dc8: ammo for slot 2
    iVar5 = (-(uint)((*(uint *)(iVar1 + 0x8e0) >> 1 & 1) != 0) & 0xfca64404) + 0xe66984f3;
  }
  else if (iVar5 == 3) {
    uStack_4 = *(undefined4 *)(iVar1 + 0x1dcc); // +0x1dcc: ammo for slot 3
    iVar5 = (-(uint)((*(uint *)(iVar1 + 0x8e0) >> 1 & 1) != 0) & 0x87bc8204) + 0x95f5ab4b;
  }
  else if (iVar5 == 1) {
    uStack_4 = *(undefined4 *)(iVar1 + 0x1dc4); // +0x1dc4: ammo for slot 1
    iVar5 = (-(uint)((*(uint *)(iVar1 + 0x8e0) >> 1 & 1) != 0) & 0xfca64404) + 0xfac29dc9;
  }
  else {
    uStack_4 = *(undefined4 *)(iVar1 + 0x1dc0); // default to slot 0 ammo
    iVar5 = -0x794d9cf7;
  }
  uVar2 = FUN_004ac480(iVar5, 0, *(uint *)(iVar1 + 0x6e8) >> 2, 1, 0, 1, 0, uStack_4); // some display/UI update function
  *(byte *)(this + 0x75) = uVar2; // +0x75: store result (maybe visibility flag)
  *(byte *)(this + 0x74) = 1; // +0x74: set to 1 (maybe dirty flag)
  FUN_00701f40(); // likely refresh UI or commit changes
  return;
}