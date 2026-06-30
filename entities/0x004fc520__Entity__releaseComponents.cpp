// FUNC_NAME: Entity::releaseComponents
void __fastcall Entity::releaseComponents(unsigned int flags) {
    // Check and release the first sub-object pointer at +0xAC
    if (*(int*)(this + 0xAC) != 0) {
        subRelease(*(void**)(this + 0xAC), flags);
        *(int*)(this + 0xAC) = 0;
    }
    // Check and release the second sub-object pointer at +0xB0
    if (*(int*)(this + 0xB0) != 0) {
        subRelease(*(void**)(this + 0xB0), flags);
        *(int*)(this + 0xB0) = 0;
    }
    // Call base class cleanup (likely parent destruction)
    baseCleanup(this);
}