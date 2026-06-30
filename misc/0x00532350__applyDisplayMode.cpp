// FUNC_NAME: applyDisplayMode
void applyDisplayMode(void)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  float local_20 [7];
  
  // Clamp minimum resolution index to at least 22 (0x16)
  if (DAT_012058d0 < 0x16) {
    DAT_012058d0 = 0x16;
  }
  // Clamp maximum resolution index to at most 22
  if (0x16 < DAT_00f15988) {
    DAT_00f15988 = 0x16;
  }
  _DAT_011f3a30 = 1;
  if (DAT_012058d0 < 7) {
    DAT_012058d0 = 7;
  }
  if (7 < DAT_00f15988) {
    DAT_00f15988 = 7;
  }
  _DAT_011f39f4 = 0;
  if (DAT_012058d0 < 0xe) {
    DAT_012058d0 = 0xe;
  }
  if (0xe < DAT_00f15988) {
    DAT_00f15988 = 0xe;
  }
  _DAT_011f3a10 = 0;
  if (DAT_012058d0 < 0x19) {
    DAT_012058d0 = 0x19;
  }
  if (0x19 < DAT_00f15988) {
    DAT_00f15988 = 0x19;
  }
  _DAT_011f3a3c = 5;
  if (DAT_012058d0 < 0x18) {
    DAT_012058d0 = 0x18;
  }
  if (0x18 < DAT_00f15988) {
    DAT_00f15988 = 0x18;
  }
  _DAT_011f3a38 = 0;
  if (DAT_012058d0 < 0xf) {
    DAT_012058d0 = 0xf;
  }
  if (0xf < DAT_00f15988) {
    DAT_00f15988 = 0xf;
  }
  _DAT_011f3a14 = 0;
  if (DAT_012058d0 < 0x1b) {
    DAT_012058d0 = 0x1b;
  }
  if (0x1a < DAT_00f15988) {
    DAT_00f15988 = 0x1b;
  }
  _DAT_011f3a44 = 1;
  // Set vsync/render mode (1,2,1)
  FUN_00417cf0(1,2,1);
  // Notify system of resolution change
  FUN_00609890(1);
  iVar1 = DAT_01218ee0;                   // New display mode index
  uVar4 = DAT_011f38f0;                   // Previous display mode index
  uVar7 = 0;
  // Search for new mode in mode list, clear its flags (low 2 bits)
  do {
    if ((&DAT_01218e50)[uVar7 * 2] == DAT_01218ee0) {
      if (uVar7 < 0x14) {
        (&DAT_01218e54)[uVar7 * 2] = (&DAT_01218e54)[uVar7 * 2] & 0xfffffffc;
      }
      break;
    }
    uVar7 = uVar7 + 1;
  } while (uVar7 < 0x14);
  // Apply new mode index and clear flags
  uVar3 = DAT_011f38f4;                   // Previous apply flags
  DAT_011f38f0 = iVar1;                   // Current mode = new mode
  DAT_011f38f4 = 0;                       // Clear flags
  FUN_00609340(0,uVar4,uVar3);            // Switch display mode
  FUN_0060db60(0,0,0,0x3f800000,0x3f800000); // Set viewport to full (0,0,1.0,1.0)
  // Update related systems
  FUN_0053c6f0();
  FUN_0053c670();
  // Handle old display context (if valid)
  if (uVar4 == 0xffffffff) {
LAB_0053254f:
    if (uVar4 < 0x1000) {
      puVar5 = &DAT_011a0f28 + uVar4 * 0x38; // Pointer to old mode's display context
      goto LAB_0053256b;
    }
  }
  else if (uVar4 < 0x1000) {
    iVar1 = uVar4 * 0x38;
    if ((&DAT_011a0f28 + iVar1 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar1] < 4)) {
      if (*(int *)(&DAT_011a0f44 + iVar1) != 0) {
        FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar1),0x200000);
      }
      *(uint *)(&DAT_011a0f34 + iVar1) = *(uint *)(&DAT_011a0f34 + iVar1) & 0xfcac8fff | 0x200000;
      FUN_006189c0();
    }
    goto LAB_0053254f;
  }
  puVar5 = (undefined1 *)0x0;
LAB_0053256b:
  // Compute scale ratios based on new mode's width and height (at offsets +2 and +4 as ushort)
  local_20[0] = DAT_00e2b1a4 / (float)*(ushort *)(puVar5 + 2); // X scale = screenWidth / modeWidth
  local_20[1] = 0.0;
  local_20[2] = 0.0;
  if (uVar4 < 0x1000) {
    puVar5 = &DAT_011a0f28 + uVar4 * 0x38;
  }
  else {
    puVar5 = (undefined1 *)0x0;
  }
  local_20[3] = DAT_00e2b1a4 / (float)*(ushort *)(puVar5 + 4); // Y scale = screenWidth / modeHeight (note: may be height, same divisor)
  // Apply scaling to overlay/window (index 7)
  if (DAT_0121be7c[7] != 0) {
    FUN_0060add0(DAT_0121bc24,DAT_0121be7c[7],local_20);
  }
  // Update primary overlay/window (index 0)
  if (*DAT_0121be7c != 0) {
    FUN_006063b0();
  }
  // Allocate a 13-float buffer for screen transform matrix
  puVar6 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
  uVar3 = DAT_00e2eff4;                    // Some screen dimension (height?)
  fVar2 = DAT_00e2b1a4;                    // Screen width
  if (puVar6 != (undefined4 *)0x0) {
    // Fill the matrix with screen dimensions and scaling factors
    *puVar6 = DAT_00e2eff4;
    puVar6[1] = fVar2;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = fVar2;
    puVar6[5] = fVar2;
    puVar6[6] = fVar2;
    puVar6[7] = 0;
    puVar6[8] = fVar2;
    puVar6[9] = uVar3;
    puVar6[10] = fVar2;
    puVar6[0xb] = fVar2;
    puVar6[0xc] = uVar3;
    puVar6[0xd] = uVar3;
    puVar6[0xe] = 0;
    puVar6[0xf] = fVar2;
    FUN_0060cde0();                        // Register the transform
  }
  FUN_00612e00();                          // Finalize display mode change
  DAT_0121bc20 = 0;                        // Clear scaling parameters
  DAT_0121bc24 = 0;
  FUN_00609890(1);                         // Update UI resolution
  FUN_004e3a70();                          // Return to previous state
  return;
}