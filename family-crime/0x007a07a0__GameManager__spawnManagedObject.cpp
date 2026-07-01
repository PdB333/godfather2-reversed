// FUNC_NAME: GameManager::spawnManagedObject
void __fastcall GameManager::spawnManagedObject(uint param_1)
{
    // Check if the game is active (e.g., not in menu, not paused)
    bool isActive = isGameActive();
    if (isActive) {
        // Allocate memory for a new managed object (size 0x38 = 56 bytes)
        ManagedObject* obj = (ManagedObject*)operator new(0x38);
        if (obj != nullptr) {
            // Call the constructor with the provided parameter
            ManagedObject* constructed = ManagedObject::ManagedObject(param_1);
            // Register the constructed object with the game manager
            registerManagedObject(constructed);
            return;
        }
        // Allocation failed, register null
        registerManagedObject(nullptr);
    }
    // Game not active, do nothing
}