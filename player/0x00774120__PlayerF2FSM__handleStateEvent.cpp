// FUNC_NAME: PlayerF2FSM::handleStateEvent
undefined1 __thiscall PlayerF2FSM::handleStateEvent(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int eventId, undefined4 param_6)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  float10 extraout_ST0;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined1 uVar12;
  undefined1 result;
  float directionX;
  float directionY;
  float directionZ;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  
  result = 1;
  switch(eventId + -0x23) {
  case 0: // EVENT_ENTER_COVER
    uVar12 = 0;
    (**(code **)(*this + 0x2c))(0xa057c555,~*(byte *)(this + 0x21) & 1,1,0,0x3f800000,0x3f800000);
    this[0x21] = this[0x21] & 0xfffffffe; // Clear bit 0 (cover flag)
    return uVar12;
  case 1: // EVENT_LEAVE_COVER
    if (this[0x22] == 0) {
      iVar7 = -0x1764441b;
    }
    else {
      iVar7 = (-(uint)(this[0x22] != 1) & 6) + 0xd1913132;
    }
    uVar12 = 0;
    (**(code **)(*this + 0x2c))(iVar7,1,1,0,_DAT_00e51ca8,0x3f800000);
    return uVar12;
  case 2: // EVENT_CANCEL_COVER
    uVar12 = 0;
    (**(code **)(*this + 0x2c))(0xa899f917,1,1,0,0x3f800000,0x3f800000);
    this[0x21] = this[0x21] & 0xfffffff7; // Clear bit 3 (some cover state)
    return uVar12;
  case 3: // EVENT_COVER_MOVE
    if (this[0x22] != -1) {
      iVar7 = FUN_0077dd80(); // Get some game state
      if (iVar7 < 3) {
        if (((uint)this[0x21] >> 2 & 1) != 0) {
          this[0x21] = this[0x21] & 0xfffffffb; // Clear bit 2
          FUN_007ee320(this + 0x1c); // Stop cover movement
          return 1;
        }
      }
      else if (((uint)this[0x21] >> 2 & 1) == 0) {
        this[0x21] = this[0x21] | 4; // Set bit 2
        FUN_007ee2e0(this + 0x1c); // Start cover movement
        return 1;
      }
    }
    break;
  case 4: // EVENT_COVER_STOP
    if (((uint)this[0x21] >> 2 & 1) != 0) {
      FUN_007ee320(this + 0x1c); // Stop cover movement
      this[0x21] = this[0x21] & 0xfffffffb; // Clear bit 2
      return 1;
    }
    break;
  case 5: // EVENT_COVER_ATTACK
    uVar12 = 0;
    (**(code **)(*this + 0x2c))(0x43204eb2,1,1,0,0x3f800000,0x3f800000);
    return uVar12;
  case 6: // EVENT_COVER_LEAN
    FUN_00773d40(); // Get player entity
    iVar7 = this[0x17]; // +0x5C - some entity handle
    if ((iVar7 != 0) && (iVar2 = FUN_0043b870(DAT_01130950), iVar2 != 0)) {
      FUN_009995e0(0,0,0); // Get camera manager
      puVar5 = (undefined4 *)FUN_00994b40(); // Get camera
      if (*(int *)*puVar5 != 0) {
        piVar6 = (int *)FUN_006bea40(iVar7); // Get entity by handle
        iVar7 = (**(code **)(*piVar6 + 0x34))(); // Get transform
        if (iVar7 != 0) {
          // Calculate direction from entity to camera
          fStack_20 = *(float *)(iVar7 + 0x20); // Camera position X
          fStack_1c = *(float *)(iVar7 + 0x24); // Camera position Y
          fStack_18 = *(float *)(iVar7 + 0x28); // Camera position Z
          fVar9 = fStack_20 - *(float *)(iVar7 + 0x14); // Entity position X
          fVar10 = fStack_1c - *(float *)(iVar7 + 0x18); // Entity position Y
          fVar11 = fStack_18 - *(float *)(iVar7 + 0x1c); // Entity position Z
          fVar8 = fVar11 * fVar11 + fVar10 * fVar10 + fVar9 * fVar9;
          uStack_14 = 0;
          fStack_24 = 0.0;
          if (fVar8 != 0.0) {
            fStack_24 = _DAT_00d5780c / SQRT(fVar8); // 1/distance
            fVar10 = fVar10 * fStack_24;
            fVar11 = fVar11 * fStack_24;
            fVar9 = fStack_24 * fVar9;
            fStack_24 = fStack_24 * 0.0;
          }
          fVar8 = *(float *)(iVar7 + 0x2c); // Lean amount
          directionX = fVar8 * fVar9 * DAT_00e51cac; // Scale by lean factor
          directionY = fVar8 * fVar10 * _DAT_0112af08;
          directionZ = fVar8 * fVar11 * DAT_00e51cac;
          FUN_005417d0(DAT_00d5f374,&directionX,&fStack_20); // Apply lean
          return 1;
        }
      }
    }
    break;
  case 7: // EVENT_COVER_GRAB
    iVar7 = this[0x17]; // +0x5C
    if (((iVar7 != 0) && (cVar1 = FUN_0072d630(), cVar1 != '\0')) &&
       (iVar2 = FUN_007326c0(), iVar2 != 0)) {
      iVar3 = FUN_00471610(); // Get player position
      iVar4 = FUN_00471610(); // Get target position
      FUN_0045c470(iVar4 + 0x30,iVar3 + 0x30); // Calculate distance
      if (extraout_ST0 < (float10)_DAT_00e51568) { // Within grab range
        FUN_006f71b0(iVar7,iVar2); // Execute grab
        return 1;
      }
    }
    break;
  default:
    result = FUN_0073e610(param_2,param_3,param_4,eventId,param_6); // Default handler
  }
  return result;
}