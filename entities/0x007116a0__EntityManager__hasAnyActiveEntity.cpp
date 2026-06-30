// FUNC_NAME: EntityManager::hasAnyActiveEntity
// Address: 0x007116a0
// Role: Checks if any entity in the manager's collection is active.
// The manager stores a count at offset 0x744 and calls a helper (0x00704110) per index.
// Returns true if any index returns nonzero.

bool __fastcall EntityManager::hasAnyActiveEntity(int thisPtr) {
    uint index = 0;
    bool result = false;
    uint count = *(uint *)(thisPtr + 0x744); // Number of entities managed

    if (count != 0) {
        do {
            int status = FUN_00704110(index); // Checks if entity at index is active
            if (status != 0) {
                result = true;
            }
            index++;
        } while (index < count);
    }
    return result;
}