// FUNC_NAME: NetSession::cleanupResources
void __fastcall NetSession::cleanupResources(NetSession* thisPtr) {
    // +0x211c: boolean flag indicating whether a resource is active
    if (*(byte*)((uintptr_t)thisPtr + 0x211c) != 0) {
        FUN_004df600();              // release associated resource
        *(byte*)((uintptr_t)thisPtr + 0x211c) = 0; // clear flag
    }
    // +0x2120: pointer to a dynamically allocated object
    int* pResource = *(int**)((uintptr_t)thisPtr + 0x2120);
    if (pResource != nullptr) {
        FUN_0090c670();              // prerelease step (e.g., unlock, detach)
        FUN_009c8eb0(pResource);     // deallocate the resource
        *(int**)((uintptr_t)thisPtr + 0x2120) = nullptr; // clear pointer
    }
}