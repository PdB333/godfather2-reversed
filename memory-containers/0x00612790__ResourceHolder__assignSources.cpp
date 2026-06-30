// FUNC_NAME: ResourceHolder::assignSources
void __thiscall ResourceHolder::assignSources(int thisPtr, int sourceA, int sourceB) {
    // +0x10: first resource pointer
    if (sourceA != 0) {
        *(int *)(thisPtr + 0x10) = FUN_0060a380(); // allocate or reference from global pool
    }
    // +0x14: second resource pointer
    if (sourceB != 0) {
        *(int *)(thisPtr + 0x14) = FUN_0060a2e0(sourceB); // create from sourceB
    }
    FUN_006127d0(); // finalize initialization
}