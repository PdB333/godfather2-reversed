// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x007f2cb0
// Constructs the global GodfatherGameManager singleton. Initializes vtable, stores the player object (param_2), and calls subsystem initialization.

GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, void* playerObject) {
    // Call base class constructor (likely MemoryManager or similar)
    FUN_0049c610(); // base::base()
    
    // Set up vtable pointers (offset +0x00 and +0x08 are vtable entries for class hierarchy)
    this->vtable0 = &PTR_FUN_00d70298;   // +0x00: primary vtable
    this->vtable2 = &PTR_LAB_00d7028c;   // +0x08: secondary vtable (initial)
    this->playerObject = playerObject;    // +0x0C: store player object reference
    
    // Reassign secondary vtable – possibly switching to derived class vtable
    this->vtable2 = &PTR_LAB_00d70294;    // +0x08: final vtable
    
    // Zero out a local struct (likely some initialization parameters)
    SomeInitStruct localInit = {0, 0, 0}; // local_c, local_8, local_4
    
    // Get or create a manager reference (e.g., EventScheduler instance)
    uVar1 = FUN_004dddd0(); // e.g., EventScheduler::getInstance()
    
    // Register this singleton with the engine (type 5)
    FUN_007f29c0(5, uVar1, &localInit); // GameManager::register(5, scheduler, &init)
    
    // Call a virtual function on the player object (vtable offset +0x08: init or start)
    (*(void (**)())(*(int*)this->playerObject + 8))(); // playerObject->vtable[2]()
    
    // Set a global initialization flag to 1
    FUN_0049c6e0(&DAT_00d70290, 1); // someGlobalFlag = true
    
    // Store pointer to this singleton in global variable
    DAT_01129968 = this;
    
    return this;
}