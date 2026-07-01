// FUNC_NAME: GodfatherGameManager::processShot
int GodfatherGameManager::processShot(int thisPtr, uint shotType, int weaponData, int hitNodeIndex, float spreadAngle, float damageMultiplier, float minDamage, float maxDamage, float *headshotMultiplier, int hitBoneIndex, int impactEffect) {
  char cVar5;
  int iVar2;
  float fVar3;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float fVar14;
  double dStack_20;
  float fStack_18;
  float fStack_10;
  int uStack_8;
  
  // Get pointer to shot data array at offset 0x588
  char *shotDataArray = (char *)(thisPtr + 0x588);
  int localThis = thisPtr;
  int returnValue = 1;
  
  // Validate shot data exists
  if (((*shotDataArray != '\0') && (weaponData != 0)) && (-1 < hitNodeIndex)) {
    // Normalize damageMultiplier to [0, DAT_00e2af34)
    for (fVar14 = DAT_011274f0 * damageMultiplier * DAT_00e2af34; fVar14 < 0.0;
        fVar14 = fVar14 + DAT_00e2af34) {
    }
    for (; DAT_00e2af34 < fVar14; fVar14 = fVar14 - DAT_00e2af34) {
    }
    
    // Clamp minDamage to [0, DAT_00e2b1a4]
    if (minDamage <= DAT_00e2b1a4) {
      if (minDamage < 0.0) {
        minDamage = 0.0;
      }
    } else {
      minDamage = DAT_00e2b1a4;
    }
    
    // Clamp maxDamage to [0, DAT_00e2b1a4]
    if (maxDamage <= DAT_00e2b1a4) {
      if (maxDamage < 0.0) {
        maxDamage = 0.0;
      }
    } else {
      maxDamage = DAT_00e2b1a4;
    }
    
    // Clamp spreadAngle to [0, DAT_00e2b04c]
    if (spreadAngle <= DAT_00e2b04c) {
      if (spreadAngle < 0.0) {
        spreadAngle = 0.0;
      }
    } else {
      spreadAngle = DAT_00e2b04c;
    }
    
    // Calculate slot index from shot type (lower 16 bits * 0xf8)
    int slotIndex = (shotType & 0xffff) * 0xf8;
    int shotSlotPtr = slotIndex + 0x5a0 + thisPtr;
    
    // Validate shot slot data
    if (((*(int *)(slotIndex + 0x5b8 + thisPtr) != 0) && (*(int *)(shotSlotPtr + 0xdc) != 0)) &&
       ((*(int *)(shotSlotPtr + 0xe0) == 0 && (iVar6 = FUN_005e9d10(), iVar6 != 0)))) {
      // Begin shot processing
      FUN_00c9eac0();
      FUN_00c9cd40(1,0);
      FUN_00c9eb20();
      FUN_00c9eae0();
      FUN_005efb60();
    }
    
    // Process shot effect
    FUN_005e9fe0();
    
    // Store shot parameters
    *(float *)(shotSlotPtr + 0x10) = minDamage;
    *(float *)(shotSlotPtr + 4) = spreadAngle;
    *(float *)(shotSlotPtr + 8) = fVar14; // normalized damageMultiplier
    *(float *)(shotSlotPtr + 0x14) = maxDamage;
    *(int *)(shotSlotPtr + 0x18) = *(int *)(weaponData + 8);
    *(int *)(shotSlotPtr + 0xec) = hitBoneIndex;
    *(int *)(shotSlotPtr + 0xf0) = impactEffect;
    
    iVar6 = *(int *)(weaponData + 8);
    
    // Validate weapon data and hit node
    if (((iVar6 != 0) && (hitNodeIndex < *(int *)(iVar6 + 4))) &&
       (iVar7 = *(int *)((hitNodeIndex + 1) * 0x10 + iVar6), iVar7 != 0)) {
      cVar5 = FUN_005ee610(thisPtr, iVar7 + iVar6);
      if (cVar5 != '\0') {
        fVar14 = minDamage * maxDamage;
        returnValue = 1;
        
        // Get state variables
        iVar6 = FUN_005e9d50();
        iVar7 = FUN_005e9d50();
        iVar8 = FUN_005e9d50();
        iVar9 = FUN_005e9d50();
        iVar10 = FUN_005e9d10();
        iVar11 = FUN_005e9d10();
        iVar12 = FUN_005e9d10();
        iVar13 = FUN_005e9d10();
        
        FUN_00c9eac0();
        
        // Handle damage based on various states
        if (iVar6 != 0) {
          fVar3 = fVar14;
          // Check for headshot flag at offset 0x9089
          if (*(char *)(thisPtr + 0x9089) == '\0') {
            fVar3 = 0.0;
          }
          FUN_00ca4e90(0, fVar3);
        }
        
        if (iVar7 != 0) {
          FUN_00ca4e90(0, 0);
        }
        
        if (iVar8 != 0) {
          FUN_00ca4e90(0, fVar14);
        }
        
        if (iVar9 != 0) {
          FUN_00ca4e90(0, *(int *)(shotSlotPtr + 0x10));
        }
        
        if (iVar10 != 0) {
          FUN_00ca4e90(0, *(int *)(shotSlotPtr + 8));
        }
        
        if (iVar11 != 0) {
          FUN_00ca4e90(0, *(int *)(shotSlotPtr + 4));
        }
        
        // Handle headshot multiplier
        if (iVar12 != 0) {
          FUN_005e9930();
          FUN_00c9cbe0(*(int *)(thisPtr + 0x580), *(int *)(iVar12 + 0x10), 0, &dStack_20);
          dStack_20 = 0.0;
          fStack_10 = *headshotMultiplier;
          fStack_18 = 0.0;
          
          // Clamp headshot multiplier
          if (0.0 < fStack_10) {
            if (DAT_00e2b1a4 <= fStack_10) {
              fStack_10 = DAT_00e2b1a4;
            }
          } else {
            fStack_10 = 0.0;
          }
          uStack_8 = 0;
          FUN_00c9cd40(0, &dStack_20);
          
          // Apply special headshot effect at offset 0x8c in headshotMultiplier array
          if (headshotMultiplier[0x23] != 0.0) {
            dStack_20 = *(double *)(*(int *)(thisPtr + 0x580) + 8) + _DAT_00e44860;
            fStack_18 = headshotMultiplier[2];
            fStack_10 = headshotMultiplier[1];
            
            if (0.0 < fStack_10) {
              if (DAT_00e2b1a4 <= fStack_10) {
                fStack_10 = DAT_00e2b1a4;
              }
            } else {
              fStack_10 = 0.0;
            }
            uStack_8 = 0;
            FUN_00c9cd40(0, &dStack_20);
            *(double *)(shotSlotPtr + 0xb0) = dStack_20;
            *(int *)(shotSlotPtr + 0xac) = 0;
          }
        }
        
        // Handle hit bone index
        if (iVar13 != 0) {
          fVar14 = (float)hitBoneIndex;
          if (hitBoneIndex < 0) {
            fVar14 = fVar14 + DAT_00e44578;
          }
          FUN_00ca4e90(0, fVar14);
        }
        
        FUN_00c9eae0();
        
        // Check for successful hit registration
        cVar5 = FUN_005ebfa0(thisPtr, *(int *)(shotSlotPtr + 0xf0), shotSlotPtr + 0xbc);
        if (cVar5 == '\0') {
          returnValue = 0;
        }
      }
    }
  }
  return returnValue;
}