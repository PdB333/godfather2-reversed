// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(int thisPtr)
{
    // Release pointer at offset +0x19c if non-null
    if (*(int *)(thisPtr + 0x19c) != 0) {
        releaseResource(*(int *)(thisPtr + 0x19c));
        *(int *)(thisPtr + 0x19c) = 0;
    }
    // Detach attachment at offset +0x174 if present
    if (*(int *)(thisPtr + 0x174) != 0) {
        detachChild(*(int *)(thisPtr + 0x174), thisPtr);
    }
    // Cleanup global resource at +0xfc
    if (*(int *)(thisPtr + 0xfc) != 0) {
        globalCleanup();
    }
    // Clear component at +0xc0 if non-null
    if (*(int *)(thisPtr + 0xc0) != 0) {
        clearComponent(thisPtr);
        *(int *)(thisPtr + 0xc0) = 0;
    }
    // Deactivate component at +0x40 if active
    if (isComponentActive(*(int *)(thisPtr + 0x40)) != 0) {
        deactivateComponent(*(int *)(thisPtr + 0x40), thisPtr);
    }
    // Internal cleanup
    cleanupInternal();
    // Release component at +0x48 if active
    if (isComponent2Active(*(int *)(thisPtr + 0x48)) != 0) {
        releaseComponent2(*(int *)(thisPtr + 0x48), thisPtr);
    }
    // Call base destructor
    baseDestructor(thisPtr);
}