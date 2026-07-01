// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

undefined4* __thiscall GodfatherGameManager::GodfatherGameManager(undefined4* this, undefined4 param2, undefined4 param3)
{
    int* piVar1;
    int iVar2;
    undefined4* puVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;

    // Call base class constructor (likely EARSObject or SimObject)
    EARSObject::EARSObject(param2, param3);
    
    // Set vtable pointer
    *this = &PTR_LAB_00d6e940;  // vtable for GodfatherGameManager
    
    // Initialize various fields to 0
    this[0x23] = 0;  // +0x8C
    this[0x1f] = 0;  // +0x7C
    this[0x1e] = 0;  // +0x78
    this[0x1d] = 0;  // +0x74
    *(undefined1*)(this + 0x24) = 0;  // +0x90 (byte)
    piVar1 = this + 0x32;  // +0xC8
    this[0x22] = 0;  // +0x88
    this[0x21] = 0;  // +0x84
    this[0x20] = 0;  // +0x80
    *piVar1 = 0;     // +0xC8
    this[0x33] = 0;  // +0xCC
    
    // Initialize memory/debug subsystem
    MemoryManager::init();
    
    this[0x4a] = 0;  // +0x128
    
    // Get singleton instance and clear some fields
    iVar2 = SimManager::getInstance();
    *(undefined8*)(iVar2 + 100) = 0;   // +0x64
    *(undefined4*)(iVar2 + 0x6c) = 0;  // +0x6C
    
    // Register event handlers (IDs: 0x18, 0x1c, 0x15, 0x21, 0x31)
    EventManager::registerHandler(0x18);
    EventManager::registerHandler(0x1c);
    InputManager::bindAction(0x15);
    InputManager::bindAction(0x21);
    EventManager::registerHandler(0x31);
    
    // Get input manager and set something
    puVar3 = (undefined4*)InputManager::getInstance();
    (**(code**)*puVar3)(2);  // InputManager::setMode(2)
    
    uVar6 = 1;
    uVar4 = 0;
    uVar5 = DAT_00d5f18c;  // Some global constant
    SimManager::registerSomething(0, DAT_00d5f18c, 1);
    AudioManager::playSound(uVar4, uVar5, uVar6);
    
    // More field initialization
    this[0x46] = 0;  // +0x118
    this[0x47] = 0;  // +0x11C
    this[0x48] = 0;  // +0x120
    this[0x49] = 0;  // +0x124
    this[0x31] = 0;  // +0xC4
    this[0x34] = 0;  // +0xD0
    
    // Free previous pointer if any
    if (*piVar1 != 0) {
        Memory::free(piVar1);
        *piVar1 = 0;
    }
    
    this[0x4a] = 0;  // +0x128
    
    // Get another singleton and set something
    puVar3 = (undefined4*)EntityManager::getInstance();
    (**(code**)*puVar3)(0x20);  // EntityManager::setMaxEntities(32)
    
    // More field initialization
    this[0x4b] = 0;  // +0x12C
    this[0x4c] = 0;  // +0x130
    this[0x2d] = 0;  // +0xB4
    this[0x2c] = 0;  // +0xB0
    this[0x2b] = 0;  // +0xAC
    this[0x30] = 0;  // +0xC0
    this[0x2f] = 0;  // +0xBC
    this[0x2e] = 0;  // +0xB8
    this[0x27] = 0;  // +0x9C
    this[0x26] = 0;  // +0x98
    this[0x25] = 0;  // +0x94
    this[0x2a] = 0;  // +0xA8
    this[0x29] = 0;  // +0xA4
    this[0x28] = 0;  // +0xA0
    this[0x4d] = 0;  // +0x134
    this[0x4e] = 0;  // +0x138
    
    // Allocate memory pool
    Memory::allocatePool(0x10, 0);
    
    return this;
}