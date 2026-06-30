// FUNC_NAME: Player::update
void __thiscall Player_update(int *this) // param_1 = this
{
  int unaff_ESI; // likely this pointer, but decompiler didn't assign properly
  
  // Call some base class update or manager function
  FUN_00ab4db0(&DAT_00e2aea0);
  
  // Check if player state is 1 (likely active/alive)
  if (*(int *)(unaff_ESI + 0xa4) == 1) {
    FUN_00ac2810(); // Possibly update input or controller
    if (*(int *)(unaff_ESI + 0xf8) != 0) {
      // Call some function on a sub-object at +0xf8 (likely a vehicle or mount)
      FUN_00ac3b80(*(int *)(unaff_ESI + 0xf8), 0, 0, 0);
      FUN_00ac2870(&DAT_00e2aea0); // Possibly end input processing
    }
  }
  
  // Check if there's a pending action/target at +0x11c
  if ((*(int *)(unaff_ESI + 0x11c) != 0) && (this != (int *)0x0)) {
    // Call virtual function at vtable+4 (likely some callback/notification)
    (**(code **)(*this + 4))(*(int *)(unaff_ESI + 0x11c), *(undefined4 *)(unaff_ESI + 0x128));
    // Clear the action/target references
    *(undefined4 *)(unaff_ESI + 0x11c) = 0;
    *(undefined4 *)(unaff_ESI + 0x128) = 0;
    *(undefined4 *)(unaff_ESI + 300) = 0; // +0x12C
  }
  
  // Update animation or movement
  FUN_005ea0d0();
  // Finalize update (possibly post-physics or cleanup)
  FUN_00ab4e70();
  return;
}