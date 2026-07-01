// FUNC_NAME: PlayerReputationTracker::updateNearestEntity
void PlayerReputationTracker::updateNearestEntity(float *self, int param_2, int param_3, float *posA, float *posB, float *velocity, float param_7, float param_8)
{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  undefined8 uStack_18;
  float deltaX;
  float deltaY;
  float deltaZ;
  
  pfVar2 = posB;
  pfVar1 = posA;
  deltaX = *posB - *posA;
  deltaY = posB[1] - posA[1];
  deltaZ = posB[2] - posA[2];
  
  // Check global game state
  if ((int *)**(int **)(DAT_012233a0 + 4) != (int *)0x0) {
    iVar3 = (**(code **)(*(int *)**(int **)(DAT_012233a0 + 4) + 0xc))();
    if (((iVar3 != 0) && (iVar3 != param_2)) && ((param_3 == 0 || (param_3 != iVar3)))) {
      // Convert posB to world space
      FUN_005e7ba0(&posB, 0);
      FUN_005e7a40(posB, &uStack_18);
      
      // Calculate distance between points
      fVar4 = (float)FUN_004a09b0(&uStack_18, pfVar1, pfVar2, &posA);
      
      // Check if within range and valid
      if (((fVar4 < (float)self[6]) && (DAT_00e44598 < (float)posA)) &&
         ((float)posA < DAT_00e446d8)) {
        self[6] = (float)fVar4;  // Update nearest distance (+0x18)
        
        // Copy target position to self (+0x1C to +0x24)
        *(undefined8 *)(self + 7) = *(undefined8 *)pfVar2;
        self[9] = pfVar2[2];
        
        // Calculate interpolated position
        uStack_18._0_4_ = (float)*(undefined8 *)pfVar1;
        uStack_18._4_4_ = (float)((ulonglong)*(undefined8 *)pfVar1 >> 0x20);
        uStack_18 = CONCAT44(deltaY * (float)posA + uStack_18._4_4_,
                             deltaX * (float)posA + (float)uStack_18);
        fVar5 = deltaZ * (float)posA + pfVar1[2];
        
        // Store interpolated start position (+0x00 to +0x08)
        *(undefined8 *)self = uStack_18;
        self[2] = fVar5;
        
        // Store interpolated end position (+0x0C to +0x14)
        *(undefined8 *)(self + 3) = uStack_18;
        self[5] = fVar5;
        
        // Apply velocity-based offset
        param_7 = DAT_00e44564 - param_7;
        *self = *velocity * param_7 + *self;
        self[1] = velocity[1] * param_7 + self[1];
        self[2] = velocity[2] * param_7 + self[2];
        self[3] = *velocity * param_8 + self[3];
        self[4] = velocity[1] * param_8 + self[4];
        self[5] = velocity[2] * param_8 + self[5];
      }
    }
  }
  return;
}