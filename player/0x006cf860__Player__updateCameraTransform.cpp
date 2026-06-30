// FUNC_NAME: Player::updateCameraTransform
void __fastcall Player::updateCameraTransform(int this)
{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  // Check if camera target exists (+0xD0) and transform hasn't been updated yet (+0x188)
  if ((*(int *)(this + 0xd0) != 0) && (*(char *)(this + 0x188) == '\0')) {
    // Get camera target object
    iVar3 = FUN_004ee450(this + 0xd0);
    if ((iVar3 != 0) &&
       // Get camera target's transform component
       (iVar3 = FUN_004ee3a0(this + 0xd0,0), uVar2 = _DAT_00d5780c, iVar3 != 0 &&
        (*(undefined4 **)(iVar3 + 0x24) != (undefined4 *)0x0)))) {
      // Copy camera target's world transform (0x26 * 4 = 0x98 bytes) to player's camera transform
      uVar1 = *(undefined4 *)(this + 0xe0);
      puVar5 = *(undefined4 **)(iVar3 + 0x24);
      puVar6 = (undefined4 *)(this + 0xf0);
      for (iVar4 = 0x26; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      // Set camera position and orientation from player's transform
      *(undefined4 *)(this + 0x110) = uVar1;
      *(undefined4 *)(this + 0x114) = *(undefined4 *)(this + 0xe4);
      *(undefined4 *)(this + 0x118) = *(undefined4 *)(this + 0xe8);
      // Set camera up vector and FOV
      *(undefined4 *)(this + 0x138) = uVar2;
      *(undefined4 *)(this + 0x100) = DAT_00d5f208;
      uVar2 = DAT_00d5ef90;
      // Set camera near/far clip planes
      *(undefined4 *)(this + 0xf4) = 0x2d2307a5;
      *(undefined2 *)(this + 0x11c) = 0x81;
      *(undefined4 *)(this + 0x130) = uVar2;
      // Apply camera transform
      FUN_004ee5a0((undefined4 *)(this + 0xf0));
      // Mark camera transform as updated
      *(undefined1 *)(this + 0x188) = 1;
    }
    if (*(char *)(this + 0x188) != '\0') {
      // Update camera system
      FUN_004df870(&DAT_00e510b0);
      FUN_004df6e0();
      return;
    }
  }
  return;
}