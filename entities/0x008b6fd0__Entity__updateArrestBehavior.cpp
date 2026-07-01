// FUNC_NAME: Entity::updateArrestBehavior
void __thiscall Entity::updateArrestBehavior(int this, int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // +0x29c: arrestFlag (0 = not arrested, non-zero = arrested)
  if (*(int *)(this + 0x29c) == 0) {
    // Not arrested: clear the follower list
    piVar1 = (int *)(this + 0x2a8); // +0x2a8: followerList pointer
    *(undefined1 *)(this + 0x2a4) = 0; // +0x2a4: followerCount (set to 0)
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // likely free/freeList
      *piVar1 = 0;
    }
    // Call some reset function with a vector (probably position)
    local_c = *(undefined4 *)(this + 0x294); // +0x294: some position/vector
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);
    // Get current game time and call event scheduling function
    iVar2 = FUN_00471610(); // likely getGameTime or getTickCount
    FUN_006b0fd0(*(undefined4 *)(this + 0x194), iVar2 + 0x30, this, param_2); // scheduleEvent at time + 48 frames
    return;
  }
  // Arrested: set follower count to 1
  *(undefined1 *)(this + 0x2a4) = 1; // followerCount = 1
  piVar1 = (int *)(this + 0x2a8); // +0x2a8: followerList
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48; // param_2 points to an object, +0x48 is some member
  }
  if (*piVar1 != param_2) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // free old follower list
    }
    *piVar1 = param_2; // set new follower
    if (param_2 != 0) {
      *(undefined4 *)(this + 0x2ac) = *(undefined4 *)(param_2 + 4); // +0x2ac: back pointer or list head
      *(int **)(param_2 + 4) = piVar1; // pointer to this entity's follower list
    }
  }
  // Reset vector again
  local_c = *(undefined4 *)(this + 0x294);
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0);
  return;
}