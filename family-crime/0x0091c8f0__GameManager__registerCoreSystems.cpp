// FUNC_NAME: GameManager::registerCoreSystems
void GameManager::registerCoreSystems(void)
{
    // Retrieve system pointers by type IDs (likely enum values for different subsystems)
    undefined4 systemType2 = getSystemByID(2);   // e.g., AudioSystem
    undefined4 systemType1 = getSystemByID(1);   // e.g., InputSystem
    undefined4 systemType3 = getSystemByID(3);   // e.g., PhysicsSystem
    undefined4 systemType4 = getSystemByID(4);   // e.g., RenderSystem
    undefined4 systemType7 = getSystemByID(7);   // e.g., NetworkSystem
    undefined4 systemType8 = getSystemByID(8);   // e.g., UISystem
    undefined4 systemType9 = getSystemByID(9);   // e.g., AudioStreamSystem

    // Build array of system pointers
    undefined4 systemArray[7];
    systemArray[0] = systemType2;
    systemArray[1] = systemType1;
    systemArray[2] = systemType3;
    systemArray[3] = systemType4;
    systemArray[4] = systemType7;
    systemArray[5] = systemType8;
    systemArray[6] = systemType9;

    // Get the global system manager instance
    undefined4 manager = getSystemManager(DAT_00e54d0c); // DAT_00e54d0c likely a global singleton pointer

    // Register the list of systems with the manager, using a vtable or function table at LAB_0091b4d0
    registerSystemList(manager, systemArray, 7, &LAB_0091b4d0);
}