// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::~GodfatherGameManager(void) {
    int iVar1;

    // Call base class destructor (EARS::Framework::Object or similar)
    baseObjectCleanup();

    // If the "initialized" flag is set, release associated subsystem
    if (*(char *)(this + 0x211c) != '\0') {
        releaseSubsystem();              // e.g., AudioManager::shutdown
        *(byte *)(this + 0x211c) = 0;
    }

    iVar1 = *(int *)(this + 0x2120);     // pointer to a subsystem (e.g., SimManager*)
    if (iVar1 != 0) {
        releaseSubsystem(iVar1);         // e.g., SimManager::release
        deleteObject(iVar1);             // e.g., operator delete
        *(int *)(this + 0x2120) = 0;
    }

    return;
}