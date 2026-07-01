// FUNC_NAME: GodfatherGameManager::reset
void __thiscall GodfatherGameManager::reset(GodfatherGameManager* this)
{
    // Clear state before deinitializing subsystem 1 (likely audio)
    (*(void(__thiscall**)(GodfatherGameManager*))(*(DWORD*)this + 0x38))(this);
    GodfatherGameManager::deinitializeAudioSystem(); // FUN_00ae96b0

    // Clear state before deinitializing subsystem 2 (likely input)
    (*(void(__thiscall**)(GodfatherGameManager*))(*(DWORD*)this + 0x38))(this);
    GodfatherGameManager::deinitializeInputSystem(); // FUN_00ae94b0

    // Clear state before deinitializing subsystem 3 (likely networking)
    (*(void(__thiscall**)(GodfatherGameManager*))(*(DWORD*)this + 0x38))(this);
    GodfatherGameManager::deinitializeNetworkSystem(); // FUN_00ae9390

    // Clear state before deinitializing subsystem 4 (likely physics)
    (*(void(__thiscall**)(GodfatherGameManager*))(*(DWORD*)this + 0x38))(this);
    GodfatherGameManager::deinitializePhysicsSystem(); // FUN_00ae9150

    // Get the object factory from the manager (vtable +0x34)
    ObjectFactory* factory = (ObjectFactory*)(*(ObjectFactory*(__thiscall**)(GodfatherGameManager*))(*(DWORD*)this + 0x34))(this);
    // Allocate a new object of size 0x10 (16 bytes) from the factory (vtable +0x38)
    void* newObject = (*(void*(__thiscall**)(ObjectFactory*, DWORD))(*(DWORD*)factory + 0x38))(factory, 0x10);
    // Initialize the allocated object with 10000 (e.g., max entities or timeout)
    (*(void(__thiscall**)(ObjectFactory*, DWORD))(*(DWORD*)factory + 0x10))(factory, 10000);

    // Clear state before final subsystem deinitialization
    (*(void(__thiscall**)(GodfatherGameManager*))(*(DWORD*)this + 0x38))(this);
    GodfatherGameManager::finalizeDeinitialization(); // FUN_00ae95d0
}