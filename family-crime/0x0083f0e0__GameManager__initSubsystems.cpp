// FUNC_NAME: GameManager::initSubsystems
void __fastcall GameManager::initSubsystems(void* this) {
    // +0x00: vtable pointer
    *(int*)this = (int)&PTR_FUN_00d743b8;  // main vtable
    *(int*)((char*)this + 0x3C) = (int)&PTR_LAB_00d743a8; // interface vtable 1
    *(int*)((char*)this + 0x48) = (int)&PTR_LAB_00d743a4; // interface vtable 2

    // Initialize global subsystems (likely singletons)
    FUN_004086d0(&DAT_012069f4);  // e.g., g_InputManager
    FUN_004086d0(&DAT_0112dc60);  // e.g., g_NetworkManager
    FUN_004086d0(&DAT_0112dc44);  // e.g., g_AudioManager
    FUN_004086d0(&DAT_0112dc4c);  // e.g., g_RenderingManager

    // Further subsystem initialization
    FUN_00408310(&DAT_0112dc60);  // e.g., NetworkManager::startup
    FUN_00408310(&DAT_0112dc68);  // e.g., g_PhysicsManager
    FUN_00408310(&DAT_0112dc58);  // e.g., g_EntityManager
    FUN_00408310(&DAT_0112dc44);  // e.g., AudioManager::startup
    FUN_00408310(&DAT_0112dc4c);  // e.g., RenderingManager::startup

    // Initialize another major component
    FUN_0083e830(); // e.g., GodfatherGameManager::initCore

    // Cleanup any previously allocated sub-object at +0x138
    if (*(int*)((char*)this + 0x138) != 0) {
        FUN_004daf90((void*)((char*)this + 0x138)); // destructor
    }

    // Final global initialization steps
    FUN_004c2390(); // e.g., InputSystem::finalizeInit
    FUN_0046c640(); // e.g., ScriptEngine::registerFunctions
}