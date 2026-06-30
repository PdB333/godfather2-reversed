// FUNC_NAME: GameManager::frameTick
void GameManager::frameTick(char param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  DAT_01129a8c = DAT_01129a8c + 1; // Increment frame counter
  FUN_0040cce0(0,1); // Begin frame timing
  iVar1 = FUN_0040cd20(1,0); // Check if frame should be skipped
  FUN_00485600(); // Process input
  piVar2 = (int *)(DAT_01206880 + 0x14); // Get stream buffer pointer
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e501f0; // Write frame counter type
  *piVar2 = *piVar2 + 4;
  *(int *)*piVar2 = DAT_01129a8c; // Write current frame number
  *piVar2 = *piVar2 + 4;
  piVar2 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e501a0; // Write frame end marker
  *piVar2 = *piVar2 + 4;
  if (param_1 != '\\0') {
    local_c = DAT_0120ecb0; // Start time
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // Sleep for frame time
  }
  if (iVar1 != 0) {
    FUN_004869a0(); // Process network
    FUN_0040cd50(1); // End frame timing
  }
  if (param_1 != '\\0') {
    local_c = DAT_0120ecb8; // End time
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // Sleep for remaining time
  }
  FUN_00485180(); // Swap buffers
  FUN_00485280(); // Present frame
  FUN_0040e1b0(); // End frame
  return;
}