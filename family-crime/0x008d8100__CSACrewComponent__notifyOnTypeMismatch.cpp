// FUNC_NAME: CSACrewComponent::notifyOnTypeMismatch
// Function address: 0x008d8100
// Checks if two entities have different type IDs, and if one is a specific type, notifies the manager.

void CSACrewComponent::notifyOnTypeMismatch(void* param_1, void* param_2)
{
    if (param_1 == nullptr || param_2 == nullptr) {
        return;
    }

    // Compare type fields at offset 0x1ed4 (likely type hash or ID)
    if (*(int*)((char*)param_2 + 0x1ed4) == *(int*)((char*)param_1 + 0x1ed4)) {
        return;
    }

    // Get current manager instance (singleton getter)
    void* manager = getManager(); // FUN_00806440
    if (manager == nullptr) {
        return;
    }

    // If the first entity has a specific type ID (0x637b907, likely "CSA" component or similar)
    if (*(int*)((char*)param_1 + 0x1ed4) == 0x637b907) {
        // Get the manager again (or a different one?) - note: duplicate call
        void* manager2 = getManager(); // FUN_00806440
        // Notify the manager about this entity type
        notifyManager(0x637b907, manager2); // FUN_008d8050
    }
}