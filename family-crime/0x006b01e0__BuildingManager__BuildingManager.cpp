// FUNC_NAME: BuildingManager::BuildingManager
// Address: 0x006b01e0
// This is the constructor for the BuildingManager singleton.
// It sets up vtables, allocates internal data, registers building-related
// message strings, and subscribes to events.

BuildingManager* __thiscall BuildingManager::BuildingManager(BuildingManager* this, uint param2)
{
    // Set initial vtables (may be overridden later)
    this->vfptr0 = &BuildingManager_vtable0_initial;       // PTR_LAB_00d5dfd8
    this->vfptr4 = &BuildingManager_vtable4_initial;       // PTR_FUN_00e2f19c (secondary interface)
    this->field_08 = 1;
    this->field_0C = 0;

    // Call base Manager constructor
    BaseManager::constructor();                            // FUN_0049c610

    // Temporary vtable for offset 0x18
    this->vfptr18_initial = &BuildingManager_vtable18_initial; // PTR_LAB_00e30fe0

    // Final vtables (all set to specific ones)
    this->vfptr0 = &BuildingManager_vtable0_final;        // PTR_FUN_00d5e1dc
    this->vfptr4 = &BuildingManager_vtable4_final;        // PTR_LAB_00d5e1cc
    this->vfptr10 = &BuildingManager_vtable10;            // PTR_LAB_00d5e1c0
    this->vfptr18 = &BuildingManager_vtable18;            // PTR_LAB_00d5e1b0

    // Zero a bunch of fields
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;

    // Allocate a block of 128 bytes (likely for a dynamic array)
    this->allocatedData = (char*)allocate(0x80);          // FUN_009c8e80(0x80)
    this->allocatedCapacity = 0x10;                       // 16 elements? or byte capacity?
    this->field_30 = 0;
    this->field_34 = 0;
    this->field_38 = 0;
    this->field_3C = 0;

    // Zero out the block from offset 0x68 to 0x104 (40 fields)
    // This likely corresponds to an array of message handler pointers
    for (int i = 0; i < 40; ++i) {
        this->messageHandlers[i] = 0;
    }

    // Register building-related message strings (global static IDs)
    // FUN_00408240 registers a string and returns a handle stored in global variables.
    // These handles are used later for message mapping.
    g_iMsgBuildingChangedOwner = registerMessage("iMsgBuildingChangedOwner");        // DAT_0112a620
    g_iMsgBuildingExploded = registerMessage("iMsgBuildingExploded");                // DAT_0112a5e0
    g_iMsgBuildingChangedState = registerMessage("iMsgBuildingChangedState");        // DAT_0112a600
    g_iMsgBuildingClosePending = registerMessage("iMsgBuildingClosePending");        // DAT_0112a650
    g_iMsgBuildingForcedOpenForMission = registerMessage("iMsgBuildingForcedOpenForMission"); // DAT_0112a660
    g_iMsgBuildingLoaded = registerMessage("iMsgBuildingLoaded");                    // DAT_0112a628
    g_iMsgBuildingUnloaded = registerMessage("iMsgBuildingUnloaded");                // DAT_0112a5b4
    g_iMsgBuildingLockDoors = registerMessage("iMsgBuildingLockDoors");              // DAT_0112a5f0
    g_iMsgBuildingUnlockDoors = registerMessage("iMsgBuildingUnlockDoors");          // DAT_0112a5e8
    g_iMsgBuildingDoorIsNearby = registerMessage("iMsgBuildingDoorIsNearby");        // DAT_0112a5d8
    g_iMsgBuildingWindowIsNearby = registerMessage("iMsgBuildingWindowIsNearby");    // DAT_0112a610
    g_iMsgBuildingWindowExplode = registerMessage("iMsgBuildingWindowExplode");      // DAT_0112a648
    g_iMsgBuildingDespawnNpcs = registerMessage("iMsgBuildingDespawnNpcs");          // DAT_0112a640
    g_iMsgBuildingStaffChanged = registerMessage("iMsgBuildingStaffChanged");        // DAT_0112a5a4
    g_iMsgBuildingElectricityChange = registerMessage("iMsgBuildingElectricityChange"); // DAT_0112a5c4
    g_iMsgLuaGetVenueStats = registerMessage("iMsgLuaGetVenueStats");                // DAT_0112a5bc
    g_iMsgLuaGetPlayerVenue = registerMessage("iMsgLuaGetPlayerVenue");              // DAT_0112a5ac
    g_iMsgPlayerExitedBuilding = registerMessage("iMsgPlayerExitedBuilding");        // DAT_0112a5cc
    g_iMsgPlayerEnteredBuilding = registerMessage("iMsgPlayerEnteredBuilding");      // DAT_0112a618
    g_iMsgPlayerVenueUnderAttackStarted = registerMessage("iMsgPlayerVenueUnderAttackStarted"); // DAT_0112a608
    g_iMsgPlayerVenueUnderAttackEnded = registerMessage("iMsgPlayerVenueUnderAttackEnded");   // DAT_0112a59c
    g_iNeoMsgBuildingChangedOwner = registerMessage("iNeoMsgBuildingChangedOwner");  // DAT_0112a630
    g_iMsgPlayerLostVenue = registerMessage("iMsgPlayerLostVenue");                  // DAT_0112a594
    g_iMsgExtortionSuccessPending = registerMessage("iMsgExtortionSuccessPending");  // DAT_0112a5f8
    g_iMsgExtortionSuccessComplete = registerMessage("iMsgExtortionSuccessComplete"); // DAT_0112a658
    g_iMsgBuildingStoreDeleted = registerMessage("iMsgBuildingStoreDeleted");        // DAT_0112a638

    // Map Lua-related messages to the manager's secondary vtable (interface)
    // FUN_00408900(puVar1, &msgID, 0x8000) likely registers a handler
    if (g_iMsgLuaGetVenueStats != 0) {
        mapMessageToHandler(this->vfptr4, &g_iMsgLuaGetVenueStats, 0x8000); // FUN_00408900
    }
    if (g_iMsgLuaGetPlayerVenue != 0) {
        mapMessageToHandler(this->vfptr4, &g_iMsgLuaGetPlayerVenue, 0x8000);
    }

    // Register the "BricknMortarRes" resource type (1 = maybe resource ID)
    registerResource("BricknMortarRes", 1);               // FUN_0049c6e0

    // Subscribe to an event with hash 0x32b7d466
    // param2 is likely a context ID or a parent object pointer
    subscribeToEvent(0x32b7d466, &this->vfptr18, param2); // FUN_00463980

    // Store singleton pointer globally
    g_BuildingManager = this;                              // DAT_0112a558 = param_1

    return this;
}