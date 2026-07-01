// FUNC_NAME: BuildingManager::updateAllBuildings
void __thiscall BuildingManager::updateAllBuildings(void* context) {
    // this+0x68: head pointer of linked list of Building objects
    // this+0x64 (100): sentinel node (embedded in manager) that marks list end
    for (Building* building = *(Building**)(this + 0x68);
         building != (Building*)(this + 100);
         building = getNextBuilding(building)) { // FUN_00ab3c50 returns next node in list
        updateBuilding(building, context); // FUN_0088a960
    }
}