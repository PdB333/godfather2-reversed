// FUNC_NAME: EntityManager::createEntity
// Function at 0x00801de0: Creates a new entity (size 0x40) and registers it.
// If allocation fails, falls back to storing the argument in a global.
// +0x38: pointer/handle to associated data (argument param_2)

void __thiscall EntityManager::createEntity(int param_2) {
    char isReady = FUN_00481640();  // global state check (e.g., "isGameRunning")
    if (isReady) {
        void* newEntity = FUN_009c8e50(0x40);  // allocate 64 bytes
        if (newEntity != nullptr) {
            FUN_00801c90(newEntity);  // Entity constructor (takes this manager)
            *(void**)((int)newEntity + 0x38) = param_2;  // store param_2 in field +0x38
            FUN_00481690(newEntity);  // register entity (add to list, etc.)
        } else {
            _DAT_00000038 = param_2;  // global fallback when allocation fails
            FUN_00481690(nullptr);    // registration with null
        }
    }
}