// FUNC_NAME: SomeClass::initComponent
// Function address: 0x0098d5e0
// Identified role: Initialization stub for an engine object, likely a component or entity
// Calls baseInit then registers a member at offset +0x94 with a global manager (DAT_00d9176c)
// Parameters: 
//   this (ECX) = pointer to object instance

void __thiscall SomeClass::initComponent() {
    // Call base class or core initialization
    baseInit();
    
    // Register the object's sub-component (at offset +0x94) with the global manager
    // This likely associates this object with a system (e.g., networking, physics, or AI)
    registerWithGlobalManager(
        &g_someGlobalManager,          // global manager instance (DAT_00d9176c)
        reinterpret_cast<uintptr_t>(this) + 0x94,  // member at offset 0x94 (e.g., a pointer or ID)
        1,                              // some flag (active? persistent?)
        0,                              // other flags
        0,                              // more flags
        1                               // final flag (e.g., enable registration)
    );
}