// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(void* this) // This function is a constructor for the Entity class (or derived). Sets vtable, calls base constructor, then checks and possibly releases a resource handle at offset 0x58.
{
    *((int*)this) = (int)&PTR_LAB_00d6386c; // Set vtable pointer for this class

    // Call base class constructor (likely EntityBase or GameObject)
    FUN_0073f060(); // Assume this is a base constructor (e.g. EntityBase::EntityBase)

    // Check resource handle at offset 0x58 (offset 0x16 * 4)
    int* resourceHandle = (int*)((char*)this + 0x58);
    if (*resourceHandle != 0 && *resourceHandle != 0x48) {
        // If handle is valid (not 0 or INVALID=0x48) and platform is in a certain state (e.g. debug)
        int platformState = FUN_00806440(); // Could be getPlatformState() or isDebugMode()
        if (platformState == 2) {
            // Debug/log something (e.g., warning about invalid handle)
            FUN_00737940(0, 0); // Possibly debugPrint or assert
        }
    }

    // If the resource handle is non-zero, release it (likely destructs sub-object)
    if (*resourceHandle != 0) {
        FUN_004daf90(resourceHandle); // releaseHandle(resourceHandle)
    }

    // Post-construction cleanup or finalization
    FUN_004ac1e0(); // Could be postConstruct() or base finalizer
}