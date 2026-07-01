// FUNC_NAME: PathfindingGraph::findBestPathNode
undefined4 __thiscall PathfindingGraph::findBestPathNode(int this, int targetNodeId, undefined4 *outNode1, undefined4 *outNode2, undefined4 *outNode3)

{
  int iVar1;
  undefined4 *puVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int bestIndex = -1;
  int currentIndex = 0;
  int local_28;
  float deltaX;
  float deltaY;
  float deltaZ;
  undefined4 local_14;
  
  // Iterate through up to 9 path nodes (stored at +0x2e4, each 0x10 bytes)
  piVar8 = (int *)(this + 0x2e4);
  do {
    if (*piVar8 == 0) {
      iVar6 = 0;
    }
    else {
      iVar6 = *piVar8 + -0x48; // Adjust pointer to get node ID
    }
    if (iVar6 == targetNodeId) {
      bestIndex = currentIndex;
      if (currentIndex == -1) break;
      switch(currentIndex) {
      case 0:
      case 4:
        // Check if we should skip this node based on some condition
        if (((*(uint *)(this + 0x428) >> 1 & 1) != 0) ||
           (uVar7 = DAT_010c2678 & DAT_012054b4, DAT_012054b4 = DAT_012054b4 + 1,
           *(float *)(this + 0x380) <= *(float *)(&DAT_010c2680 + uVar7 * 4)))
        goto switchD_008f9e54_caseD_2;
        currentIndex = currentIndex + 2;
        break;
      default:
        break;
      case 2:
      case 6:
switchD_008f9e54_caseD_2:
        currentIndex = currentIndex + 1;
        break;
      case 8:
        goto switchD_008f9e54_caseD_8;
      }
      if (currentIndex != -1) goto LAB_008fa07c;
      break;
    }
    currentIndex = currentIndex + 1;
    piVar8 = piVar8 + 4;
  } while (currentIndex < 9);
  
switchD_008f9e54_caseD_8:
  // Get positions of two objects for direction calculation
  iVar6 = FUN_007ff880(); // Get some object
  if (iVar6 == 0) {
    iVar6 = FUN_00471610(); // Get another object
  }
  else {
    FUN_007ff880();
    iVar6 = FUN_00471610();
    FUN_007ff880();
  }
  pfVar3 = (float *)FUN_00471610(); // Get direction vector
  iVar4 = FUN_00471610(); // Get target position
  
  // Calculate delta vector between two positions
  deltaX = *(float *)(iVar4 + 0x30) - *(float *)(iVar6 + 0x30);
  deltaY = *(float *)(iVar4 + 0x34) - *(float *)(iVar6 + 0x34);
  deltaZ = *(float *)(iVar4 + 0x38) - *(float *)(iVar6 + 0x38);
  local_14 = 0;
  FUN_0056afa0(&deltaX, &deltaX); // Normalize delta
  
  // Determine which side of the direction vector we're on
  if (pfVar3[1] * deltaY + *pfVar3 * deltaX + pfVar3[2] * deltaZ < 0.0) {
    currentIndex = 4;
    local_28 = 0;
  }
  else {
    currentIndex = 0;
    local_28 = 4;
  }
  
  // Get node IDs from the two candidate positions
  iVar6 = *(int *)(currentIndex * 0x10 + 0x2f4 + this);
  iVar4 = currentIndex * 0x10 + this;
  if (iVar6 == 0) {
    iVar6 = 0;
  }
  else {
    iVar6 = iVar6 + -0x48;
  }
  iVar10 = *(int *)(iVar4 + 0x304);
  if (iVar10 == 0) {
    iVar10 = 0;
  }
  else {
    iVar10 = iVar10 + -0x48;
  }
  iVar1 = local_28 * 0x10 + this;
  if (*(int *)(iVar1 + 0x2f4) == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)(iVar1 + 0x2f4) + -0x48;
  }
  if (*(int *)(iVar1 + 0x304) == 0) {
    iVar9 = 0;
  }
  else {
    iVar9 = *(int *)(iVar1 + 0x304) + -0x48;
  }
  iVar4 = *(int *)(iVar4 + 0x2e4);
  
  // Compare node availability and decide which direction to go
  if ((((iVar4 == 0) || (iVar4 == 0x48)) &&
      ((byte)((iVar9 == 0) + (iVar5 == 0) * 2) <= (byte)((iVar10 == 0) + (iVar6 == 0) * 2)
      )) || ((currentIndex = local_28, *(int *)(iVar1 + 0x2e4) == 0 || (*(int *)(iVar1 + 0x2e4) == 0x48)
             ))) {
    if (currentIndex != -1) goto LAB_008fa07c;
  }
  else if ((*(int *)(this + 0x364) == 0) || (*(int *)(this + 0x364) == 0x48)) {
    currentIndex = 8;
    goto LAB_008fa07c;
  }
  currentIndex = bestIndex;
  if (bestIndex == -1) {
    return 0;
  }
  
LAB_008fa07c:
  // Clear old node reference if we found a new one
  if ((bestIndex != -1) &&
     (puVar2 = (undefined4 *)(bestIndex * 0x10 + 0x2e4 + this),
     *(int *)(bestIndex * 0x10 + 0x2e4 + this) != 0)) {
    FUN_004daf90(puVar2); // Release node reference
    *puVar2 = 0;
  }
  
  // Set output parameters
  iVar6 = currentIndex * 0x10 + this;
  *outNode1 = *(undefined4 *)(currentIndex * 0x10 + 0x2dc + this); // +0x2dc: node data 1
  *outNode2 = *(undefined4 *)((currentIndex + 0x2e) * 0x10 + this); // +0x2e0: node data 2
  piVar8 = (int *)(iVar6 + 0x2e4);
  
  // Update node reference
  if (targetNodeId == 0) {
    targetNodeId = 0;
  }
  else {
    targetNodeId = targetNodeId + 0x48;
  }
  if (*piVar8 != targetNodeId) {
    if (*piVar8 != 0) {
      FUN_004daf90(piVar8); // Release old reference
    }
    *piVar8 = targetNodeId;
    if (targetNodeId != 0) {
      *(undefined4 *)(iVar6 + 0x2e8) = *(undefined4 *)(targetNodeId + 4); // +0x2e8: next node pointer
      *(int **)(targetNodeId + 4) = piVar8; // Update linked list
    }
  }
  
  *outNode3 = *(undefined4 *)(&UNK_00d8143c + currentIndex * 4); // Some global data
  return 1;
}