// FUNC_NAME: PlayerActionableInfo::updateActionTimer
undefined4 __fastcall PlayerActionableInfo::updateActionTimer(int this)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint unaff_EBX;
  float fVar5;
  undefined4 local_8 [2];
  
  // Check global timers/conditions - possibly game pause or state
  if ((DAT_01205224 < *(uint *)(this + 0xac)) ||
     (DAT_00d5ef84 < *(float *)(DAT_0112af68 + 0x168))) {
    return 0;
  }
  local_8[0] = 0;
  // Call virtual function on some object to get a player instance
  cVar1 = (**(code **)(**(int **)(this + 0x5c) + 0x10))(0x10e5319e,local_8);
  uVar2 = -(uint)(cVar1 != '\0') & unaff_EBX;
  // Get some global object pointer
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
  }
  if (uVar2 == 0) {
    return 0;
  }
  // Check if player is in some state (e.g., not in combat)
  if (*(int *)(uVar2 + 0xb74) != 0) {
    return 0;
  }
  // Call some update function
  FUN_0086e440(0,&stack0xfffffff4);
  // Check player flags at +0xc88 for bit 12 (0x1000)
  if ((*(uint *)(uVar2 + 0xc88) >> 0xc & 1) != 0) {
    iVar3 = FUN_00471610();
    cVar1 = FUN_006c0050(iVar3 + 0x30,0,0);
    if (cVar1 == '\0') {
      cVar1 = FUN_00690150(4);
      fVar5 = DAT_0112dfe8;
      if (cVar1 != '\0') {
        fVar5 = DAT_0112dff0;
      }
      goto LAB_0086fdc4;
    }
  }
  // Default action timer value
  fVar5 = DAT_0112dfe0;
  // Check another flag at +0x8e0 bit 4
  if ((*(uint *)(iVar4 + 0x8e0) >> 4 & 1) != 0) {
    fVar5 = DAT_0112dfec;
  }
LAB_0086fdc4:
  // If timer value is negative, action is ready
  if (fVar5 < 0.0) {
    return 1;
  }
  // Handle timer cooldown
  if (_DAT_00e5410c < 0.0) {
    // Check if player is in a specific state (e.g., aiming)
    if (*(int *)(uVar2 + 0xf2c) == 1) {
      iVar4 = FUN_00471610();
      cVar1 = FUN_006c0050(iVar4 + 0x30,0,0);
      if (cVar1 != '\0') {
        // Check if timer has reached threshold
        if (DAT_00e445ac <= *(float *)(this + 0x9c)) {
          return 1;
        }
        // Increment timer
        *(float *)(this + 0x9c) = *(float *)(this + 0x9c) + DAT_012067e8;
        return 0;
      }
    }
    // Reset timer
    *(undefined4 *)(this + 0x9c) = 0;
  }
  return 0;
}