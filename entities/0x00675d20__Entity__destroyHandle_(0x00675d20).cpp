// FUNC_NAME: Entity::destroyHandle (0x00675d20)
// Destructor/cleanup function that releases owned handles and frees memory.
// Handles are reference-counted structures with a header (4 ints before handle pointer).
// Param 'this' is a handle pointer; outPointer (in EDX) is optionally set to 0.
void __fastcall Entity::destroyHandle(int this, void **outPointer)
{
    int *handle;
    int refTable;
    int refIndex;
    int *refCounter;

    // If caller passed an output pointer, clear it (typical for operator delete)
    if (outPointer != nullptr) {
        *outPointer = 0;
    }

    // Release various subsystems (likely SIM, physics, audio, etc.)
    releaseSimPhysics();
    releaseSkeletonData();
    releaseModelInstance();   // called twice
    releaseCollectableData();
    releaseMissionHandle();
    releaseGameplayData();

    // Handle at +0x28
    handle = *(int **)(this + 0x28);
    if (handle != nullptr) {
        refTable = *handle;
        // Invalidate slot in the reference table
        *(undefined4 *)(*(int *)(refTable + 0xC) + handle[-2] * 4) = 0;
        // Decrement reference count
        refCounter = (int *)(refTable + 4);
        *refCounter = *refCounter - 1;
        // Free the handle's memory (header at -4 ints)
        (*(void (__cdecl *)(void *))DAT_01206694)(handle - 4);
    }

    // Handle at +0x38
    handle = *(int **)(this + 0x38);
    if (handle != nullptr) {
        refTable = *handle;
        *(undefined4 *)(*(int *)(refTable + 0xC) + handle[-2] * 4) = 0;
        refCounter = (int *)(refTable + 4);
        *refCounter = *refCounter - 1;
        (*(void (__cdecl *)(void *))DAT_01206694)(handle - 4);
    }

    // Handle at +0x3C
    handle = *(int **)(this + 0x3C);
    if (handle != nullptr) {
        refTable = *handle;
        *(undefined4 *)(*(int *)(refTable + 0xC) + handle[-2] * 4) = 0;
        refCounter = (int *)(refTable + 4);
        *refCounter = *refCounter - 1;
        (*(void (__cdecl *)(void *))DAT_01206694)(handle - 4);
    }

    releaseModelInstance();  // second call (duplicate of above)

    // Handle at +0x2C
    handle = *(int **)(this + 0x2C);
    if (handle != nullptr) {
        refTable = *handle;
        *(undefined4 *)(*(int *)(refTable + 0xC) + handle[-2] * 4) = 0;
        refCounter = (int *)(refTable + 4);
        *refCounter = *refCounter - 1;
        (*(void (__cdecl *)(void *))DAT_01206694)(handle - 4);
    }

    releaseMaterialInstance();
    releaseParticleEmitter();
    releaseTaaScreenEffect();

    // Handle at +0x14 (pointer to a sub-handle)
    refTable = *(int *)(this + 0xB4); // reference table pointer for this object
    handle = (int *)*(int *)(this + 0x14);
    if (handle != nullptr) {
        // Invalidate slot using index from handle[-2]
        *(undefined4 *)(*(int *)(refTable + 0xC) + *(int *)(handle - 2) * 4) = 0;
        refCounter = (int *)(refTable + 4);
        *refCounter = *refCounter - 1;
        // Free the handle memory (header at -4 ints)
        (*(void (__cdecl *)(void *))DAT_01206694)(handle - 4);
    }

    // Final cleanup of 'this' itself (the object handle)
    refTable = *(int *)(this + 0xB4);
    // Invalidate slot using index stored at this[-8]
    *(undefined4 *)(*(int *)(refTable + 0xC) + *(int *)(this - 8) * 4) = 0;
    refCounter = (int *)(refTable + 4);
    *refCounter = *refCounter - 1;
    // Free the object memory (header at -16 bytes)
    (*(void (__cdecl *)(void *))DAT_01206694)(this - 0x10);
}