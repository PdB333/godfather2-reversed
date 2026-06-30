// FUNC_NAME: BuildingManager::CreateInstance
void __thiscall BuildingManager::CreateInstance(BuildingManager* this, undefined4 param2, undefined4 param3)
{
    // Allocate memory for a BuildingManager object (size 0x870 bytes)
    int allocation = FUN_009c8e50(0x870);
    if (allocation != 0) {
        // Call the actual constructor/initializer with the two parameters
        FUN_0053efc0(param2, param3);
    }
    // Note: param1 (this) is unused, likely the caller passes an allocator or context
}