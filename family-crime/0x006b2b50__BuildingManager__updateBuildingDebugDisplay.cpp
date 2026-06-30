// FUNC_NAME: BuildingManager::updateBuildingDebugDisplay
void __thiscall BuildingManager::updateBuildingDebugDisplay(int thisPtr, char selected)
{
  int buildingId;
  undefined4 *buildingData;
  undefined1 *nameStr;
  undefined4 nameHash;
  int nodePtr;
  int *frameBuffer;
  undefined1 *tempStr;
  
  FUN_006b2910(); // likely updateDebugFrame
  buildingId = *(int *)(thisPtr + 0x194); // +0x194: currentBuildingId
  if ((buildingId != 0) && (buildingId != 0x48)) {
    buildingData = (undefined4 *)FUN_008c7550(*(undefined4 *)(thisPtr + 0x40)); // +0x40: buildingDataArray
    FUN_004d3ca0("dv_building_", 0xc, *buildingData, buildingData[1]); // format building name
    if (selected != '\0') {
      FUN_004d4300("_selected"); // append _selected suffix
    }
    tempStr = (undefined1 *)0x0;
    if (tempStr == (undefined1 *)0x0) {
      tempStr = &DAT_0120546e; // default string
    }
    nameHash = FUN_0060d740(tempStr); // hash the debug display name
    nodePtr = FUN_0049e120(nameHash); // find debug display node
    if (nodePtr != 0) {
      frameBuffer = (int *)(DAT_01206880 + 0x14); // +0x14: frameBuffer pointer
      **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e50d58; // setup debug draw command
      *frameBuffer = *frameBuffer + 4;
      *(int *)*frameBuffer = buildingId + 0xc; // building data offset
      *frameBuffer = *frameBuffer + 4;
      *(undefined4 *)*frameBuffer = nameHash;
      *frameBuffer = *frameBuffer + 4;
    }
    if (tempStr != (undefined1 *)0x0) {
      (*(code *)0x0)(tempStr); // likely deallocate tempStr (null placeholder)
    }
  }
  return;
}