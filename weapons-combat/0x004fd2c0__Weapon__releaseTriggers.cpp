// FUNC_NAME: Weapon::releaseTriggers
void __thiscall Weapon::releaseTriggers(void)
{
  int iVar1;
  undefined4 *puVar2;
  int this;
  
  *(uint *)(this + 0x78) = *(uint *)(this + 0x78) | 1; // Set currentTriggerFlags bit 0 (primary trigger released?)
  iVar1 = *(int *)(this + 0x80); // +0x80: left hand slot
  if (iVar1 != 0) {
    // Clear muzzle flash flag (0x20000) on left trigger slot
    if ((*(uint *)(iVar1 + 0xc) & 0x20000) == 0) {
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x20000;
      FUN_0051b120(); // Animation::setMuzzleFlash or similar
    }
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffbffff; // Clear flag 0x40000
    iVar1 = *(int *)(this + 0x80);
    puVar2 = *(undefined4 **)(iVar1 + 8);
    if (puVar2 != (undefined4 *)0x0) {
      *puVar2 = 0;
      *(undefined4 *)(iVar1 + 8) = 0; // Clear left hand slot reference
    }
  }
  iVar1 = *(int *)(this + 0x84); // +0x84: right hand slot
  if (iVar1 != 0) {
    // Same clear for right trigger slot
    if ((*(uint *)(iVar1 + 0xc) & 0x20000) == 0) {
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x20000;
      FUN_0051b120();
    }
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffbffff;
    iVar1 = *(int *)(this + 0x84);
    puVar2 = *(undefined4 **)(iVar1 + 8);
    if (puVar2 != (undefined4 *)0x0) {
      *puVar2 = 0;
      *(undefined4 *)(iVar1 + 8) = 0; // Clear right hand slot reference
    }
  }
  *(undefined4 *)(this + 0x7c) = 0; // +0x7c: triggerTimer
  return;
}