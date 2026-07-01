// FUNC_NAME: Screen::updateScreenState
void __thiscall Screen::updateScreenState(int *this, int screenId, int transitionEffect, char bForceDeactivate)
{
  int iVar1;
  int *piVar2;
  code *pcVar3;
  
  piVar2 = DAT_01223484;  // global game manager pointer
  if ((bForceDeactivate == '\0') && (screenId != -1)) {
    // Activate/transition to this screen
    FUN_008a2d40(0);  // pushRenderContext
    iVar1 = **(int **)(DAT_012233a0 + 4); // current active screen object
    if (((iVar1 != 0) && (iVar1 != 0x1f30)) &&
       (FUN_00907ac0(0x1e,0x3f800000), *(char *)(iVar1 + 0x11ec) != '\0')) {
      // Set audio volume for channel 0x1e and check a flag at +0x11ec
      FUN_00907a50(0x1c,0x3f800000); // set audio volume for channel 0x1c
    }
    iVar1 = *piVar2; // dereference to get main engine object
    if (piVar2[2] == 0) {
      pcVar3 = *(code **)(iVar1 + 0x98); // vtable slot for update (if not paused)
    }
    else {
      pcVar3 = *(code **)(iVar1 + 0x80); // vtable slot for update (paused)
    }
    (*pcVar3)(); // call engine update
    FUN_008a4ae0(0); // popRenderContext
    (**(code **)(*this + 0x2c))(); // call this object's vtable slot 0x2c (e.g., draw)
  }
  else {
    // Deactivate this screen
    *(ushort *)((int)this + 0x66) = *(ushort *)((int)this + 0x66) & 0xfffe; // clear bit 0 (active bit?)
    (**(code **)(*this + 8))(); // call vtable slot 8 (deactivate/leave)
    *(ushort *)((int)this + 0x66) = *(ushort *)((int)this + 0x66) & 0xfffd; // clear bit 1 (transitioning?)
  }
  if (transitionEffect != 0) {
    FUN_009823b0(); // cameraShake
    FUN_009c8eb0(transitionEffect); // applyTransitionEffect
  }
  return;
}