// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x008919e0
// Role: Constructor for GodfatherGameManager class. Calls base class constructor, then optionally allocates memory if the 'allocate' flag is set.

GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(bool allocate) {
    // Call base class constructor (likely EARSObject or similar)
    GodfatherGameManager::baseConstructor(); // FUN_00891480 - assumed base class init

    // If allocate flag is true, allocate memory for the class (size 0x188 = 392 bytes)
    if (allocate) {
        // FUN_0043b960 is likely a custom placement new or memory allocator
        // that takes the object pointer and size
        GodfatherGameManager::operator new(this, 0x188); // Allocation helper
    }

    return this;
}