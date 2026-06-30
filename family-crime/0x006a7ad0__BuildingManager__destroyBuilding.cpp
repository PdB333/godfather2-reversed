// FUNC_NAME: BuildingManager::destroyBuilding
void __fastcall BuildingManager::destroyBuilding(int *buildingManager)
{
  int buildingPtr;
  
  // Call base destructor or cleanup routine
  Building::~Building();
  
  // Free the building's name string (offset +0x14 = name string pointer)
  FUN_009c8f10(buildingManager[5]);
  
  // If there's a linked building (e.g., family house connection)
  buildingPtr = *buildingManager;
  if (buildingPtr != 0) {
    // Free the linked building's name string (offset +0x8 = name string pointer)
    FUN_009c8f10(*(undefined4 *)(buildingPtr + 8));
    // Destroy the linked building object
    FUN_009c8eb0(buildingPtr);
  }
  return;
}