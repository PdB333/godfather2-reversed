// FUNC_NAME: BuildingManager::updateBuildingOwnership
void __fastcall BuildingManager::updateBuildingOwnership(int this)
{
  int *familyManager;
  int *familyList;
  int familyCount;
  int **familyIter;
  int *currentFamily;
  int i;
  int j;
  int *buildingNode;
  int tempThis;
  int *nextBuildingNode;
  
  tempThis = this;
  familyManager = (int *)FUN_00ad8d40(); // likely FamilyManager::getInstance()
  currentFamily = (int *)0x0;
  i = 0;
  if ((familyManager != (int *)0x0) &&
     (familyManager = (int *)(**(code **)(*familyManager + 0x34))(), familyManager != (int *)0x0)) {
    currentFamily = (int *)(**(code **)(*familyManager + 0x24))(); // getFirstFamily
    i = (**(code **)(*currentFamily + 0x3c))(0); // getFamilyCount
  }
  if (*(int *)(this + 0x3c) == 0) { // +0x3C: buildingListHead
    buildingNode = (int *)0x0;
    familyIter = buildingNode;
  }
  else {
    buildingNode = (int *)**(undefined4 **)(*(int *)(this + 0x3c) + 8); // get first building node
    familyIter = buildingNode;
  }
  do {
    if (familyIter == (int *)0x0) {
      return;
    }
    j = 0;
    if (0 < i) {
      do {
        int *family = (int *)(**(code **)(*currentFamily + 0x24))(j); // getFamilyByIndex
        int familyId = (**(code **)(*family + 0xc))(); // getFamilyId
        if (familyId == *buildingNode) { // compare with building's family ID
          int **nextPtr = (int **)buildingNode[2]; // +8: next building node
          goto LAB_0065d948;
        }
        j = j + 1;
      } while (j < i);
    }
    j = tempThis;
    FUN_0065d650(tempThis, buildingNode); // BuildingManager::removeBuildingFromList
    if (*(int *)(j + 0x3c) == 0) {
      nextBuildingNode = (int *)0x0;
      familyIter = &nextBuildingNode;
    }
    else {
      buildingNode = (int *)**(undefined4 **)(*(int *)(j + 0x3c) + 8);
      familyIter = &buildingNode;
    }
LAB_0065d948:
    familyIter = *nextPtr;
  } while( true );
}