// FUNC_NAME: SimManager::SimManager
// Function at 0x008cb030: Constructor of SimManager class
// The class appears to implement multiple interfaces (multiple vtable pointers).
// param2 and param3 are likely construction parameters from the caller.

SimManager* __thiscall SimManager::SimManager(int param2, int param3)
{
    // Call base class constructor (likely from FUN_004b60f0)
    BaseClassConstructor(param2, param3);
    
    // Set vtable pointer for interface at offset 0x2C
    // First assignment (overwritten later? Possibly a temporary vtable)
    this->field_0x2C = &vtable_SimManager_0x2C;
    
    // Clear low 2 bits of flags at offset 0x10 (byte operation)
    this->flagsAt0x10 &= 0xFC;
    
    // Set primary vtable pointer (offset 0x00)
    this->vtable = &vtable_SimManager;
    
    // Set second vtable pointer at offset 0x0C
    this->field_0x0C = &vtable_AnotherInterface;
    
    // Set final vtable pointer at offset 0x2C (overwrites previous)
    this->field_0x2C = &vtable_SimManager_0x2C_Second;
    
    // Initialize some global resource (e.g., a hash table or pool) with 0x1000 entries
    ResourceInit(&g_ResourceHandle, 0x1000);
    
    // Call sub-init with param2, param3, and pointer to member at offset 0x30 (this+0x30)
    // This likely initializes a sub-component starting at that offset.
    SubInit(param2, param3, &this->field_0x30);
    
    return this;
}