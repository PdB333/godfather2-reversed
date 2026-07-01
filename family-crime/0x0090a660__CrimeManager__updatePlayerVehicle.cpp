// FUNC_NAME: CrimeManager::updatePlayerVehicle
void CrimeManager::updatePlayerVehicle(void) {
    // Lock critical section (mutex) to ensure thread safety
    enterCriticalSection(1);

    // Check if the game is currently active/running
    if (!isGameActive()) {
        return;
    }

    // Retrieve the CrimeManager singleton via its ID (stored in DAT_01131040)
    CrimeManager* pCrimeMgr = (CrimeManager*)getSingleton(DAT_01131040);
    if (pCrimeMgr == nullptr) {
        return;
    }

    // Check the state field at offset 0x1c: only proceed if state is 0 or 0x48
    // (likely an idle or action state)
    uint32_t state = *(uint32_t*)((char*)pCrimeMgr + 0x1c); // +0x1c state
    if (state != 0 && state != 0x48) {
        return;
    }

    // Global pointer to VehicleManager stored at 0x012233a0
    VehicleManager* pVehicleMgr = *(VehicleManager**)0x012233a0;
    // Access the active vehicle pointer at offset 4 of VehicleManager
    void* activeVehiclePtr = *(void**)((char*)pVehicleMgr + 4); // +0x04 active vehicle
    if (activeVehiclePtr == nullptr) {
        // No active vehicle: call spawn with null parameters (despawn/reset)
        spawnVehicle(nullptr, nullptr, 1);
    } else {
        // Recover the vehicle base object by subtracting offset 0x1f30 (member → container)
        BaseVehicle* pVehicle = (BaseVehicle*)((char*)activeVehiclePtr - 0x1f30);
        // Retrieve another singleton (e.g., VehicleSpawnManager) via DAT_01130fa0
        VehicleSpawnManager* pSpawnMgr = (VehicleSpawnManager*)getSingleton(DAT_01130fa0);
        spawnVehicle(pVehicle, pSpawnMgr, 1);
    }
}