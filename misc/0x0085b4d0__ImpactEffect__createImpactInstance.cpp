// FUNC_NAME: ImpactEffect::createImpactInstance
void __thiscall ImpactEffect::createImpactInstance(int thisPtr, int *params)
{
  undefined4 *puVar1;
  char cVar2;
  undefined2 uVar3;
  int *piVar4;
  int iVar5;
  int **ppiVar6;
  undefined4 uVar7;
  int iVar8;
  int *piVar9;
  short *psVar10;
  float10 fVar11;
  float fVar12;
  double dVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 local_2d;
  int *local_2c;
  int local_28;
  int local_24;
  float local_20;
  int local_1c;
  int *local_18;
  int *apiStack_14 [4];
  
  local_24 = *params;
  iVar5 = params[1];
  local_2c = (int *)0x0;
  
  // Check if both entities are alive (0x10 = entity, +0x80 = alive flag)
  if (*(char *)(*(char *)(local_24 + 0x10) + 0x80 + local_24) != '\x01') {
    return;
  }
  if (*(char *)(*(char *)(iVar5 + 0x10) + 0x80 + iVar5) != '\x01') {
    return;
  }
  
  // Get positions from entities (0x18 = position valid flag, 0x10 = position component offset)
  if (*(char *)(local_24 + 0x18) == '\x01') {
    local_28 = *(char *)(local_24 + 0x10) + local_24;
  }
  else {
    local_28 = 0;
  }
  if (*(char *)(iVar5 + 0x18) == '\x01') {
    local_20 = (float)(*(char *)(iVar5 + 0x10) + iVar5);
  }
  else {
    local_20 = 0.0f;
  }
  
  iVar8 = params[2];
  if (iVar8 == local_28) {
    local_24 = iVar5;
  }
  
  piVar4 = (int *)FUN_004afca0(local_24); // Get some component
  iVar5 = *(int *)(params[4] + 8);
  
  // Get collision info (0x10 = collision point/0x8 = variant)
  if (*(int *)(iVar5 + 8) == iVar8 + 0x10) {
    local_1c = FUN_005566a0(*(undefined4 *)(iVar5 + 0x10),*(undefined4 *)(iVar5 + 0x14));
  }
  else {
    local_1c = FUN_005566a0(*(int *)(iVar5 + 8),*(undefined4 *)(iVar5 + 0xc));
  }
  
  // Check if already processing impact
  if ((local_1c != 0) && ((*(uint *)(local_1c + 4) & 0x8000) != 0)) {
    FUN_0087c9a0();
    return;
  }
  
  // Find empty slot in impact instance array (0x168 = array start, 8 bytes per entry)
  iVar5 = 0;
  psVar10 = (short *)(thisPtr + 0x168);
  do {
    if (*psVar10 == 0) {
      iVar5 = iVar5 * 0x10 + thisPtr;
      uVar3 = FUN_009f7e60(); // Get impact type ID
      *(undefined2 *)(iVar5 + 0x168) = uVar3;
      *(int *)(iVar5 + 0x16c) = DAT_01205224; // Current time
      uVar7 = FUN_009f7ea0(); // Get impact position
      *(undefined4 *)(iVar5 + 0x174) = uVar7;
      break;
    }
    iVar5 = iVar5 + 1;
    psVar10 = psVar10 + 8;
  } while (iVar5 < 3); // Max 3 impact instances
  
  FUN_008590d0(&local_18,&local_24); // Check for existing impact
  if (local_18 != (int *)0x0) {
    *(char *)(local_18 + 5) = (char)local_18[5] + '\x01'; // Increment count
    return;
  }
  
  local_2d = 1;
  FUN_0085a910(thisPtr + 0xfc,&local_24,&local_2d); // Register impact
  
  // Check time since last impact
  if ((uint)(DAT_01205224 - *(int *)(thisPtr + 0x110)) < 2) {
    return;
  }
  
  // Calculate impact force
  if (piVar4 != (int *)0x0) {
    local_18 = (int *)0x0;
    cVar2 = (**(code **)(*piVar4 + 0x10))(0xa7039c8,&local_18); // Get velocity component
    if ((cVar2 != '\0') && (local_18 != (int *)0x0)) {
      fVar12 = *(float *)((int)local_20 + 0x134) - *(float *)(local_28 + 0x134); // Y difference
      fVar14 = *(float *)((int)local_20 + 0x138) - *(float *)(local_28 + 0x138); // Z difference
      fVar17 = *(float *)((int)local_20 + 0x130) - *(float *)(local_28 + 0x130); // X difference
      fVar15 = fVar14 * fVar14 + fVar12 * fVar12 + fVar17 * fVar17; // Distance squared
      fVar16 = 0.0f;
      if (fVar15 != 0.0f) {
        fVar16 = _DAT_00d5780c / SQRT(fVar15); // Normalize
      }
      // Project velocity onto collision normal (0x1a0 = velocity component +0x1a4 = another component +0x1a8 = third component)
      fVar12 = (*(float *)(local_28 + 0x1a8) * fVar14 * fVar16 +
                *(float *)(local_28 + 0x1a4) * fVar12 * fVar16 +
               *(float *)(local_28 + 0x1a0) * fVar16 * fVar17) -
               (*(float *)((int)local_20 + 0x1a8) * fVar14 * fVar16 +
                *(float *)((int)local_20 + 0x1a4) * fVar12 * fVar16 +
               *(float *)((int)local_20 + 0x1a0) * fVar16 * fVar17);
      goto LAB_0085b77f;
    }
  }
  fVar12 = (float)params[6]; // Use default impact force from params
LAB_0085b77f:
  
  // Scale impact force
  dVar13 = (double)(float)((uint)fVar12 & DAT_00e44680);
  FUN_00b9af10();
  apiStack_14[0] = (int *)(float)dVar13;
  fVar11 = (float10)FUN_009efd10(); // Random value
  local_18 = (int *)(float)fVar11;
  fVar11 = (float10)FUN_009efd10(); // Another random value
  local_20 = (float)fVar11;
  local_28 = *(undefined4 *)(thisPtr + 0xd8); // Damage multiplier
  dVar13 = (double)((float)local_18 + local_20);
  FUN_00b9af10();
  local_18 = (int *)((float)dVar13 * (float)apiStack_14[0]); // Randomized force
  dVar13 = _DAT_00d75488;
  FUN_00b9af10();
  apiStack_14[0] = (int *)(float)dVar13;
  dVar13 = DAT_00d75480;
  FUN_00b9af10();
  fVar12 = ((float)local_18 / ((float)apiStack_14[0] * (float)dVar13)) * DAT_00d5e288; // Final force calculation
  
  // Check if force exceeds threshold
  if (*(float *)(thisPtr + 0xdc) < fVar12) {
    fVar14 = *(float *)(thisPtr + 0xe0);
    if (fVar14 <= fVar12) {
      // Cap at maximum
      local_2c = (int *)(fVar14 * DAT_00d5ef84 * *(float *)(thisPtr + 0xe8));
    }
    else {
      // Scale between min and max
      ppiVar6 = (int **)(thisPtr + 0xe8);
      local_18 = (int *)(((float)*ppiVar6 / (fVar14 - *(float *)(thisPtr + 0xdc))) * fVar12);
      apiStack_14[0] = (int *)0x0;
      if (((float)local_18 < (float)*ppiVar6 || (float)local_18 == (float)*ppiVar6) &&
         (ppiVar6 = apiStack_14, 0.0f <= (float)local_18)) {
        ppiVar6 = &local_18;
      }
      local_2c = *ppiVar6;
    }
    
    // Apply damage multiplier
    if ((*(uint *)(*(int *)(thisPtr + 0xf8) + 0xc88) >> 2 & 1) != 0) {
      local_2c = (int *)(*(float *)(thisPtr + 0xec) * (float)local_2c);
    }
    
    if (0.0f < (float)local_2c) {
      *(int *)(thisPtr + 0x110) = DAT_01205224; // Record time of last impact
      
      if (*(float *)(thisPtr + 0x120) <= (float)local_2c) {
        *(uint *)(thisPtr + 0x1c0) = *(uint *)(thisPtr + 0x1c0) | 0x80000000; // Set death flag
      }
      
      local_18 = piVar4;
      if ((piVar4 != (int *)0x0) && (cVar2 = (**(code **)(*piVar4 + 0x78))(), cVar2 != '\0')) {
        cVar2 = (**(code **)(*piVar4 + 0x10))(0xf8b45dfb, apiStack_14);
        if (cVar2 == '\0') {
          // Create impact event
          iVar5 = FUN_009c8e50(0x48); // 0x48 = size of impact event
          if (iVar5 == 0) {
            iVar5 = 0;
          }
          else {
            iVar5 = FUN_0084dd20(); // Constructor
          }
          FUN_0044b210(*(undefined4 *)(thisPtr + 0xf8)); // Get source entity
          uVar7 = (**(code **)(**(int **)(thisPtr + 0xf8) + 0x1e4))(); // Get position
          FUN_0044b210(uVar7);
          iVar8 = FUN_00471610(); // Get player controller
          *(undefined8 *)(iVar5 + 0x14) = *(undefined8 *)(iVar8 + 0x30); // Copy transform
          *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(iVar8 + 0x38);
          *(int **)(iVar5 + 0x2c) = local_2c; // Impact force
          *(undefined4 *)(iVar5 + 0x30) = 3; // Type
          *(undefined4 *)(iVar5 + 0x38) = 3; // Subtype
          puVar1 = (undefined4 *)params[3]; // Impact position
          *(undefined4 *)(iVar5 + 0x20) = *puVar1;
          *(undefined4 *)(iVar5 + 0x24) = puVar1[1];
          *(undefined4 *)(iVar5 + 0x28) = puVar1[2];
          *(undefined4 *)(iVar5 + 0x3c) = 0;
          fVar12 = DAT_00d5ef84;
          *(int *)(iVar5 + 0x40) = DAT_01205224;
          FUN_00440590(&DAT_0112dd94, piVar4 + 0xf, fVar12, iVar5, 0); // Send event
        }
        else {
          // Alternative handling
          *(uint *)(thisPtr + 0x1c0) = *(uint *)(thisPtr + 0x1c0) | 0x80000000; // Set death flag
          piVar9 = (int *)FUN_006c12d0(piVar4, 0xa5975eb2); // Get component
          if ((piVar9 != (int *)0x0) && (iVar5 = (**(code **)(*piVar9 + 0x1e4))(), iVar5 != 0)) {
            local_18 = (int *)(**(code **)(*piVar9 + 0x1e4))(); // Get another component
          }
        }
      }
      
      // Create another impact event for player
      iVar5 = FUN_009c8e50(0x48);
      if (iVar5 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = FUN_0084dd20();
      }
      FUN_0044b210(piVar4);
      FUN_0044b210(local_18);
      iVar8 = FUN_00471610();
      *(undefined8 *)(iVar5 + 0x14) = *(undefined8 *)(iVar8 + 0x30);
      *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(iVar8 + 0x38);
      *(int **)(iVar5 + 0x2c) = local_2c;
      *(undefined4 *)(iVar5 + 0x30) = 3;
      *(undefined4 *)(iVar5 + 0x38) = 3;
      puVar1 = (undefined4 *)params[3];
      *(undefined4 *)(iVar5 + 0x20) = *puVar1;
      *(undefined4 *)(iVar5 + 0x24) = puVar1[1];
      *(undefined4 *)(iVar5 + 0x28) = puVar1[2];
      *(undefined4 *)(iVar5 + 0x3c) = 0;
      *(int *)(iVar5 + 0x40) = DAT_01205224;
      if (*(int *)(thisPtr + 0xf8) == 0) {
        iVar8 = 0;
      }
      else {
        iVar8 = *(int *)(thisPtr + 0xf8) + 0x3c; // +0x3c = component offset
      }
      FUN_00440590(&DAT_0112dd94, iVar8, DAT_00d5ef84, iVar5, 0);
    }
  }
  
  FUN_0085ae40(params, local_2c, local_1c); // Finalize impact
  return;
}