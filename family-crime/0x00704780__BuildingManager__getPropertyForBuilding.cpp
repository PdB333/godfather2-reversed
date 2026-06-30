// FUNC_NAME: BuildingManager::getPropertyForBuilding
uint __thiscall BuildingManager::getPropertyForBuilding(uint buildingPtr)
{
    // buildingPtr is a pointer to a Building object (or other entity)
    if (buildingPtr != 0)
    {
        // Read building type at offset +0x1ad (byte)
        uint type = *(byte *)(buildingPtr + 0x1ad);
        if (type < 0x23) // 0x23 = 35 possible types
        {
            // Return property from table at this+0x118 (byte array indexed by type)
            return *(byte *)((int)this + 0x118 + type);
        }
    }
    // Invalid case: return the original pointer with low byte cleared (error sentinel)
    return buildingPtr & 0xffffff00;
}