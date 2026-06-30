// FUN_NAME: Building::Building(bool registerWithManager)
undefined4 __thiscall Building::Building(Building* this, byte registerWithManager)
{
    // Call base class constructor or initialization
    Building::initialize();

    // If register flag is set, register this building with building manager
    if ((registerWithManager & 1) != 0) {
        BuildingManager::registerBuilding(this);
    }
    return this;
}