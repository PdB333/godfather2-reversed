// FUNC_NAME: VehicleAI::updateSteeringAndThrottle
void __fastcall VehicleAI::updateSteeringAndThrottle(int this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  int local_170;
  int local_16c;
  int local_168;
  int local_164;
  int local_160;
  undefined4 local_15c;
  int local_158;
  undefined4 local_154;
  
  // Check if current action state is idle or specific state (0x48 = maybe "stopped")
  if ((*(int *)(this + 0xa0) == 0) || (*(int *)(this + 0xa0) == 0x48)) {
    iVar5 = *(int *)(this + 0x58); // +0x58: pointer to vehicle physics data
    iVar1 = *(int *)(iVar5 + 0x24fc); // +0x24fc: some target/waypoint index
    if ((iVar1 != 0) && (iVar1 != 0x48)) {
      iVar2 = FUN_00471610(); // Get current position
      iVar3 = FUN_00471610(); // Get target position
      fVar7 = *(float *)(iVar3 + 0x30) - *(float *)(iVar2 + 0x30); // delta X
      fVar8 = *(float *)(iVar3 + 0x34) - *(float *)(iVar2 + 0x34); // delta Y
      fVar9 = *(float *)(iVar3 + 0x38) - *(float *)(iVar2 + 0x38); // delta Z
      // Check distance squared against threshold
      if (_DAT_00d577a0 < fVar9 * fVar9 + fVar8 * fVar8 + fVar7 * fVar7) {
        FUN_006dc940(); // Some initialization/reset
        local_170 = *(int *)(iVar5 + 0x2bb4); // +0x2bb4: steering input
        local_16c = *(int *)(iVar5 + 0x2bb8); // +0x2bb8: throttle input
        local_168 = *(int *)(iVar5 + 0x2bbc); // +0x2bbc: brake input
        local_164 = *(int *)(iVar5 + 0x2bc0); // +0x2bc0: handbrake input
        if ((((local_170 == 0) && (local_16c == 0)) && (local_168 == 0)) && (local_164 == 0)) {
          // No inputs set, create default steering/throttle
          local_17c = 2; // Maybe steering type
          local_178 = 0x10; // Maybe throttle type
          local_174 = 0; // Maybe brake type
          iVar2 = FUN_009c8ed0(0x1c8, &local_17c); // Allocate input structure
          if (iVar2 == 0) {
            uVar4 = 0;
          }
          else {
            uVar4 = FUN_006dcd10(); // Initialize input
          }
          FUN_007c5b10(uVar4); // Apply input to vehicle
        }
        else {
          // Use existing inputs
          uVar4 = FUN_00446130(&local_170, 0); // Convert inputs to some format
          FUN_007c5b10(uVar4); // Apply input to vehicle
          iVar2 = *(int *)(this + 0xa0);
          if (iVar2 == 0) {
            FUN_006dce00(0x68); // Set action state to something
          }
          else {
            FUN_006dce00(iVar2 + 0x20); // Increment action state
          }
        }
        // Handle reference counting for steering/throttle objects
        if (iVar5 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = iVar5 + 0x48; // +0x48: some offset in vehicle data
        }
        if (local_160 != iVar2) {
          if (local_160 != 0) {
            FUN_004daf90(&local_160); // Release reference
          }
          local_160 = iVar2;
          if (iVar2 != 0) {
            local_15c = *(undefined4 *)(iVar2 + 4);
            *(int **)(iVar2 + 4) = &local_160; // Set up linked list
          }
        }
        if (local_158 != iVar1) {
          if (local_158 != 0) {
            FUN_004daf90(&local_158); // Release reference
          }
          local_158 = iVar1;
          if (iVar1 != 0) {
            local_154 = *(undefined4 *)(iVar1 + 4);
            *(int **)(iVar1 + 4) = &local_158; // Set up linked list
          }
        }
        FUN_006dd610(&local_160); // Calculate steering angle
        uVar4 = *(undefined4 *)(&DAT_00002494 + iVar5); // Get vehicle speed
        fVar6 = (float10)FUN_006dc860(uVar4, &local_160); // Calculate throttle based on steering
        iVar5 = *(int *)(this + 0xa0);
        if (iVar5 == 0) {
          iVar5 = 0;
        }
        else {
          iVar5 = iVar5 + -0x48; // Adjust action state
        }
        FUN_00424dc0(uVar4, iVar5, (float)(fVar6 * (float10)_DAT_00d5ca1c), 5, 0); // Apply throttle with speed factor
        if (local_158 != 0) {
          FUN_004daf90(&local_158); // Cleanup reference
        }
        if (local_160 != 0) {
          FUN_004daf90(&local_160); // Cleanup reference
        }
      }
    }
  }
  return;
}