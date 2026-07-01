// FUNC_NAME: SomeManager::getTypeId
// Function at 0x00965980: Returns a type identifier (default 2) from a manager object.
// The manager is obtained via a singleton getter (FUN_00965910).
// Offsets: +0x4c is a pointer to a pointer to a structure with a type field at +0x10.
//          +0x50 is a validity flag/pointer.

int SomeManager::getTypeId() {
    SomeManager* pManager = reinterpret_cast<SomeManager*>(FUN_00965910());
    if (pManager != nullptr && pManager->field_0x50 != 0) {
        // Dereference: pManager->field_0x4c is a pointer to a pointer.
        // The inner pointer points to an object with a 4-byte type field at offset 0x10.
        return *(int*)(*(int**)(reinterpret_cast<char*>(pManager) + 0x4c) + 0x10);
    }
    return 2; // Default type
}