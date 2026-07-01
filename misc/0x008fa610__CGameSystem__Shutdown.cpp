// FUNC_NAME: CGameSystem::Shutdown

void __thiscall CGameSystem::Shutdown(IUnknown* pInterface, uint bCleanup) {
    char queryResult;
    void* pObject = nullptr;
    uint64_t timeA, timeB;
    int* pTimeSource;

    // Query interface with GUID 0x10e5319e
    queryResult = pInterface->QueryInterface(0x10e5319e, &pObject);
    if (queryResult == 0) {
        pObject = nullptr;
    } else if (pObject != nullptr) {
        // Call virtual method at offset 0x28c (likely Shutdown/Release)
        ((ISomeSystem*)pObject)->Release(1); // +0x28c

        if (*(int*)((char*)this + 0x160) != 0) { // +0x160: some flag or pointer
            pTimeSource = (int*)FUN_00471610(); // getTimeSource()
            timeA = *(uint64_t*)(pTimeSource + 6);  // +0x30
            timeB = *(uint64_t*)((char*)pTimeSource + 0x38); // +0x38
        }
        FUN_005fde60(&timeA); // register shutdown timing
    }

    FUN_0083f630(0, (uint64_t*)&pObject, pInterface, bCleanup, 0); // cleanup interface

    if (pObject != nullptr) {
        FUN_00878980(*(int*)((char*)this + 0x178)); // release sub-object at +0x178

        if (bCleanup != 0 && (pObject[0x322] | 0x1000) != pObject[0x322]) {
            ((ISomeSystem*)((int*)pObject)[0x16])->SomeMethod(0x10); // +0x28 on vtable at +0x58
            pObject[0x322] |= 0x1000; // set flag at offset 0xC88
        }

        int* pSystem = (int*)FUN_00542d70(); // getGlobalSystem()
        if (pSystem != nullptr) {
            *(ushort*)((char*)pSystem + 200) |= 8; // set bits at offset 200
        }
    }
}