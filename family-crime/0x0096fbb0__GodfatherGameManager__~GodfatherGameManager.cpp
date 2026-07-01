// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* thisPtr)
{
    int iVar1;
    void** ppvVar2;

    // Set vtable pointers to destructor vtable
    ppvVar2 = (void**)(thisPtr + 4);
    *(void**)thisPtr = &PTR_FUN_00d8f218;          // vtable[0]
    *ppvVar2 = &PTR_LAB_00d8f1f4;                  // vtable[1]
    thisPtr[0x13] = &PTR_LAB_00d8f1f0;             // +0x4C
    thisPtr[0x14] = &PTR_LAB_00d8f1e0;             // +0x50

    // Unregister callbacks/handlers (third param = 1 likely means unregister)
    unregisterCallback(ppvVar2, &LAB_00969090, 1);
    unregisterCallback(ppvVar2, &LAB_00963ee0, 1);
    unregisterCallback(ppvVar2, &LAB_0096fba0, 1);
    unregisterCallback(ppvVar2, &LAB_0096ccb0, 1);
    unregisterCallback(ppvVar2, &LAB_0096ee00, 1);
    unregisterCallback(ppvVar2, &LAB_0096ee10, 1);

    // Cleanup global state
    cleanupGlobalState(&DAT_012069c4);
    allocateMemory(0x100, thisPtr + 0x14);          // +0x50

    // Critical section for global flag
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);
    DAT_011308b4 = 0;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);

    // Release many member pointers (offsets in dwords)
    releasePointer(thisPtr[0x32]);   // +0xC8
    releasePointer(thisPtr[0x33]);   // +0xCC
    releasePointer(thisPtr[0x39]);   // +0xE4
    releasePointer(thisPtr[0x3a]);   // +0xE8
    releasePointer(thisPtr[0x45]);   // +0x114
    releasePointer(thisPtr[0x46]);   // +0x118
    releasePointer(thisPtr[0x3b]);   // +0xEC
    releasePointer(thisPtr[0x3c]);   // +0xF0
    releasePointer(thisPtr[0x40]);   // +0x100
    releasePointer(thisPtr[0x3f]);   // +0xFC
    releasePointer(thisPtr[0x48]);   // +0x120
    releasePointer(thisPtr[0x49]);   // +0x124
    releasePointer(thisPtr[0x4a]);   // +0x128
    releasePointer(thisPtr[0x4b]);   // +0x12C
    releasePointer(thisPtr[0x4c]);   // +0x130
    releasePointer(thisPtr[0x4e]);   // +0x138
    releasePointer(thisPtr[0x4f]);   // +0x13C
    releasePointer(thisPtr[0x54]);   // +0x150
    releasePointer(thisPtr[0x55]);   // +0x154
    releasePointer(thisPtr[0x56]);   // +0x158
    releasePointer(thisPtr[0x57]);   // +0x15C
    releasePointer(thisPtr[0xac]);   // +0x2B0
    releasePointer(thisPtr[0x5b]);   // +0x16C

    // Static cleanup calls
    staticCleanup();
    staticCleanup();
    staticCleanup();

    cleanupSubsystemA();
    releasePointer(thisPtr[0xf9]);   // +0x3E4

    iVar1 = thisPtr[0xf4];           // +0x3D0
    if (iVar1 != 0) {
        releasePointer(*(int*)(iVar1 + 8));
        deleteObjectWithDestructor(iVar1);
    }
    if (thisPtr[0xf1] != 0) {       // +0x3C4
        releasePointer(thisPtr[0xf1]);
    }

    staticCleanup();
    cleanupSubsystemA();
    releasePointer(thisPtr[0xd6]);   // +0x358

    iVar1 = thisPtr[0xd1];           // +0x344
    if (iVar1 != 0) {
        releasePointer(*(int*)(iVar1 + 8));
        deleteObjectWithDestructor(iVar1);
    }
    if (thisPtr[0xce] != 0) {       // +0x338
        releasePointer(thisPtr[0xce]);
    }

    staticCleanup();
    cleanupSubsystemB();
    releasePointer(thisPtr[0x66]);   // +0x198

    iVar1 = thisPtr[0x61];           // +0x184
    if (iVar1 != 0) {
        releasePointer(*(int*)(iVar1 + 8));
        deleteObjectWithDestructor(iVar1);
    }
    if (thisPtr[0x5e] != 0) {       // +0x178
        releasePointer(thisPtr[0x5e]);
    }

    ppvVar2 = (void**)thisPtr[0x2c]; // +0xB0
    if (ppvVar2 != NULL) {
        if (ppvVar2[-1] == 0) {
            releasePointer(ppvVar2 - 1);
        } else {
            (**(code**)*ppvVar2)(3);
        }
    }

    finalCleanup();
    thisPtr[0x13] = &PTR_LAB_00d8de40;  // +0x4C, set to base vtable
    DAT_01129930 = 0;
    staticCleanup();
    return;
}