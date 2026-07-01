// FUNC_NAME: ActionManager::processActionEvent
undefined1 __thiscall ActionManager::processActionEvent(ActionManager *this, undefined4 param_2, float param_3, undefined4 param_4, int actionId, undefined4 param_6)
{
  int *entityPtr;
  int *targetPtr;
  int iVar3;
  char canPerform;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  undefined1 returnVal;
  undefined4 uVar9;
  undefined1 local_65;
  Vector3 deltaVec;
  Vector3 targetPos;
  Vector3 entityPos;
  Vector3 diffVec;
  
  local_65 = 1;
  switch(actionId) {
  case 0x23: // Start combo
    entityPtr = (int *)this->entity; // this+0x17*4 = offset 0x5C? Actually param_1[0x17] is offset 0x5C
    FUN_007f63e0(0); // reset combo state?
    FUN_0076c090(); // update combo flags?
    iVar3 = *(int *)(entityPtr + 0x24cc); // +0x24cc: some state
    if ((((iVar3 != 0) && (iVar3 != 0x48)) && ((*(uint *)(entityPtr + 0x249c) >> 2 & 1) != 0)) &&
       (canPerform = FUN_007178e0(), canPerform != '\0')) {
      return 1; // can start
    }
    goto LAB_0076cde5;
  case 0x24: // Play hit reaction
    returnVal = 0x3f; // success
    (**(code **)(*(int *)this + 0x2c))(this->hitReactionAnimPlayer,1,1,0,1.0f,1.0f);
    return returnVal;
  case 0x25: // Apply damage
    if ((*(int *)(this->entity + 0x24cc) != 0) &&
       (iVar7 = *(int *)(this->entity + 0x24cc) + -0x48, iVar7 != 0)) {
      FUN_00470230(iVar7, param_3 * g_timeDelta, 0); // apply damage with scaling
      return 1;
    }
    break;
  case 0x26: // Throw object
    entityPtr = (int *)this->entity;
    if (((entityPtr[0x933] != 0) && (entityPtr[0x933] != 0x48)) &&
       ((((uint)entityPtr[0x927] >> 2 & 1) != 0 && (canPerform = FUN_007178e0(), canPerform != '\0')))) {
      uVar5 = FUN_00711680(); // get current target
      FUN_007166d0(&diffVec, uVar5); // get target world position
      FUN_0072a0b0(&diffVec); // set object position to target?
      entityPtr[0x7d6] = entityPtr[0x7d6] | 0x400000; // set flag (disable physics?)
      (**(code **)(*(int *)entityPtr + 0x264))(); // finalize throw
      entityPtr[0x7d6] = entityPtr[0x7d6] & 0xffbfffff; // clear flag
      return 1;
    }
LAB_0076cde5:
    this->flags = this->flags | 1; // this+0x21*4 = offset 0x84
    return 1;
  case 0x27: // End combo
    FUN_00716700(); // increment combo step
    this->comboCounter = this->comboCounter + 1; // this+0x1f*4 = offset 0x7C
    return 1;
  case 0x28: // Play block
    returnVal = 0x3f;
    (**(code **)(*(int *)this + 0x2c))(this->blockAnimPlayer,1,0,1,1.0f,1.0f);
    return returnVal;
  case 0x29: // Reset action
    FUN_007166e0(); // reset animation state
    return 1;
  case 0x2a: // Melee attack
    entityPtr = (int *)this->entity;
    canPerform = (**(code **)(*(int *)entityPtr + 0x1bc))(); // check if can attack
    if ((canPerform != '\0') && (piVar6 = (int *)FUN_00711680(), piVar6 != (int *)0x0)) {
      (**(code **)(*(int *)entityPtr + 0x48))(&diffVec); // get entity world position
      (**(code **)(*(int *)piVar6 + 0x48))(&targetPos); // get target world position
      deltaVec.x = diffVec.x - targetPos.x;
      deltaVec.y = diffVec.y - targetPos.y;
      deltaVec.z = diffVec.z - targetPos.z;
      FUN_0043a210(&deltaVec, &deltaVec); // normalize
      iVar7 = **(int **)(g_globalManager + 4); // dereference global pointer
      if (((iVar7 != 0) &&
          (((piVar1 = (int *)(iVar7 + -0x1f30), piVar1 != (int *)0x0 && // check if object is valid
            (*(int *)(iVar7 + -0x5c) == entityPtr[0x7b5])) && (piVar1 != piVar6)))) &&
         ((iVar7 = FUN_00716420(), iVar7 != 0 && // check range?
          (canPerform = FUN_00713f90(&diffVec, &targetPos, g_throwDistance, piVar1, &deltaVec), canPerform == '\0'
          )))) { // line of sight check
        uVar9 = 0;
        uVar5 = FUN_006fbc40(0,0); // allocate effect
        FUN_007f96a0(0,0x94,uVar5,uVar9); // spawn attack effect
        FUN_006fbc70(); // finalize
        return 1;
      }
    }
    break;
  case 0x2b: // Use item
    canPerform = FUN_00730210(); // check if can use item
    if (canPerform != '\0') {
      uVar9 = 0;
      uVar5 = FUN_006fbc40(0,0);
      FUN_007f96a0(0,0,uVar5,uVar9); // spawn use effect
      FUN_006fbc70();
      return 1;
    }
    canPerform = FUN_0072d630(); // check if can do special
    uVar5 = 0;
    if (canPerform != '\0') {
      uVar9 = FUN_006fbc40(0,0);
      FUN_007f96a0(0x8b85f37b,0,uVar9,uVar5); // spawn special effect
      FUN_006fbc70();
      return 1;
    }
    uVar9 = FUN_006fbc40(0,0);
    FUN_007f96a0(0x90621df4,0,uVar9,uVar5); // spawn default effect
    FUN_006fbc70();
    return 1;
  case 0x2c: // Set aim state
    this->aimState = g_aimStateGlobal; // this+0x1d*4 = offset 0x74
    return 1;
  default:
    local_65 = FUN_0073e610(param_2, param_3, param_4, actionId, param_6); // base class handler
  }
  return local_65;
}