// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Set primary vtable pointer (offset +0x0)
    this->vtable = &PTR_FUN_00d771f4;
    // Set secondary vtable for interface at offset +0x3C
    *(void **)((uint8_t*)this + 0x3C) = &PTR_LAB_00d771e4;
    // Set secondary vtable for interface at offset +0x48
    *(void **)((uint8_t*)this + 0x48) = &PTR_LAB_00d771e0;

    // Call base constructor (likely EARS::Framework::Object)
    FUN_0088dd20(this);

    // Initialize sub-object at offset +0x6C (e.g., NetworkManager, InputManager)
    FUN_0088f0c0(*(void **)((uint8_t*)this + 0x6C));

    // Global system initialization (e.g., MemoryManager::init, Havok::init)
    FUN_0046c640();
}