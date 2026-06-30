// FUN_004c67d0: EARSObject::EARSObject
// Function address: 0x004c67d0
// Role: Constructor for EARSObject, initializes core system pointer and subsystem pointer, then calls post-construction handler.

void __thiscall EARSObject::EARSObject(void* thisPtr)
{
    // Initialize core system (e.g., game engine singleton) - offset +0x10
    *(void**)((int)thisPtr + 0x10) = CoreSystem::getInstance(); // FUN_0060a380

    // Initialize secondary subsystem from global manager - offset +0x14
    *(void**)((int)thisPtr + 0x14) = SubsystemManager::getSystem(&g_pGlobalManager); // FUN_0060a2e0 with PTR_DAT_0110a36c

    // Perform final construction steps
    postConstruct(); // FUN_006127d0
}