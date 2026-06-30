// FUNC_NAME: ModuleRegistry::registerModules
// Address: 0x00611c20
// Role: Registers 20 module objects into a global linked list, assigning each an ID and slot number.
// Each module is a derived class with virtual functions at vtable+4 (getIdentifier) and vtable+0x10 (postInit).

void ModuleRegistry::registerModules() {
    // Global subsystem initialization
    initializeGlobalModuleData();  // originally FUN_00609f70

    // Array of 20 module object pointers at 0x00f15940
    // Each object has a vtable pointer at offset 0, plus 3 int fields:
    // +4: previous pointer (links into singly-linked list)
    // +8: hash/ID assigned by computeModuleHash
    // +12: slot number (incremented global counter)
    for (uint i = 0; i < 20; i++) {
        BaseModule* module = *(BaseModule**)((int)&PTR_PTR_00f15940 + i * 4);

        // Get an identifier from the module (e.g., string hash, GUID)
        uint identifier = module->getIdentifier();  // vtable+4

        // Compute a unique ID from the identifier and store at offset +8
        int moduleId = computeModuleHash(identifier);  // originally FUN_0060d740
        module->id = moduleId;

        // Final initialization step for this module (vtable+0x10)
        module->postInit();

        // Insert module at head of global linked list
        module->previous = (BaseModule*)global_previousPtr;  // DAT_012058ec
        global_moduleCount++;  // DAT_012058f8
        global_previousPtr = module;
        module->slot = global_moduleCount;  // offset +12
    }
}