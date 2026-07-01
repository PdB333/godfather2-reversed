// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(undefined4 *thisPtr)
{
    int someObject;
    char cVar2;
    int *manager;

    someObject = thisPtr[0x16]; // +0x58: pointer to some large object (e.g., player state)
    *thisPtr = &PTR_LAB_00d6fb70; // set vtable to derived class
    manager = (int *)getSomeManagerSingleton(); // e.g., InputManager::getInstance
    (**(code **)(*manager + 4))(thisPtr[0x1e]); // release resource at +0x78
    *(uint *)(someObject + 0x249c) &= 0xfffffeff; // clear bit 8 at offset 0x249c
    *(uint *)(someObject + 0x24a0) &= 0xfffffeff; // clear bit 8 at offset 0x24a0
    releaseResource(0x17); // stop audio stream or similar
    releaseResource(0x14); // stop another resource
    freeMemory(&DAT_00d6fb30); // free some global data
    cVar2 = isGameActive();
    if (cVar2 != '\0') {
        cVar2 = isPlayerInGame();
        if ((cVar2 != '\0') && (someObject != 0)) {
            manager = (int *)getManagerFromGlobal(DAT_01131018); // e.g., PlayerManager
            if (manager != (int *)0x0) {
                manager[6] &= 0xfffdffff; // clear bit 17 at offset 0x18
                (**(code **)(*manager + 0x3c))(0x3f800000); // set some float to 1.0f
                manager[6] |= 0x20000; // set bit 17
            }
        }
    }
    cVar2 = isGameActive();
    if (cVar2 != '\0') {
        setControllerState(1); // enable controller
        setControllerVibration(1); // enable vibration
    }
    if ((*(char *)(thisPtr + 0x1f) == '\0') && (thisPtr[0x16] != 0)) { // +0x7c flag, +0x58 pointer
        manager = (int *)getManagerFromGlobal(DAT_01131018);
        if (manager != (int *)0x0) {
            cVar2 = (**(code **)(*manager + 0x38))(); // check some condition
            if (cVar2 != '\0') {
                *(undefined1 *)(thisPtr + 0x1f) = 1; // set flag
                shutdownSomething(); // e.g., shutdown subsystems
            }
        }
    }
    cleanupSomething(); // general cleanup
    *thisPtr = &PTR_LAB_00d6b95c; // switch to base class vtable
    baseClassDestructor(); // call base destructor
    return;
}