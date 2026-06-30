// FUNC_NAME: cleanupObjectResources
// Function address: 0x00612a60
// Releases all resource pointers stored in the object at given address.
// Global DAT_012058e8 stores the object pointer for later use (offset 0x8c, 0x90).
// Called from many destructors/cleanups (via callers like FUN_00530a60, etc.).

void __fastcall cleanupObjectResources(int objPtr)
{
    // Store object pointer globally (used later for offsets 0x8c and 0x90)
    gGlobalObjectPointer = objPtr;

    // Release the two main resource managers (renderer + audio?) at +0x10 and +0x14
    releaseResource(*(void**)(objPtr + 0x10)); // +0x10: renderer/manager1
    releaseResource(*(void**)(objPtr + 0x14)); // +0x14: audio/manager2

    // Offset 0x94: if non-null, release using a transform with default
    if (*(int*)(objPtr + 0x94) != 0) {
        gTempVec_x = gDefaultVec_x; // +0x012058d8
        gTempVec_y = gDefaultVec_y; // +0x012058dc
        releaseResourceWithTransform(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x94), &gTempVec);
    }

    // Series of conditionals: release each resource if non-null, using manager1/2 and default globals
    if (*(int*)(objPtr + 0x18) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x18), &gDefaultResource0);
    }
    if (*(int*)(objPtr + 0x1c) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x1c), &gDefaultResource1);
    }
    if (*(int*)(objPtr + 0x20) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x20), &gDefaultResource2);
    }
    if (*(int*)(objPtr + 0x24) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x24), &gDefaultResource3);
    }
    if (*(int*)(objPtr + 0x28) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x28), &gDefaultResource4);
    }
    if (*(int*)(objPtr + 0x2c) != 0) {
        releaseResourceWithFlags(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x2c), &gDefaultResource4, 3);
    }
    if (*(int*)(objPtr + 0x30) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x30), &gDefaultResource5);
    }
    if (*(int*)(objPtr + 0x34) != 0) {
        releaseResourceWithFlags(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x34), &gDefaultResource5, 3);
    }
    if (*(int*)(objPtr + 0x38) != 0) {
        releaseResourceWithFlags(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x38), &gDefaultResource6, 3);
    }
    if (*(int*)(objPtr + 0x3c) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x3c), &gDefaultResource7);
    }
    if (*(int*)(objPtr + 0x40) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x40), &gDefaultResource8);
    }
    if (*(int*)(objPtr + 0x44) != 0) {
        releaseResourceWithFlags(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x44), &gDefaultResource8, 3);
    }
    if (*(int*)(objPtr + 0x48) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x48), &gDefaultResource9);
    }
    if (*(int*)(objPtr + 0x4c) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x4c), &gDefaultResource10);
    }
    if (*(int*)(objPtr + 0x50) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x50), &gDefaultResource11);
    }
    if (*(int*)(objPtr + 0x54) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x54), &gDefaultResource12);
    }
    if (*(int*)(objPtr + 0x58) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x58), &gDefaultResource13);
    }
    if (*(int*)(objPtr + 0x5c) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x5c), &gDefaultResource14);
    }
    if (*(int*)(objPtr + 0x60) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x60), &gDefaultResource15);
    }
    if (*(int*)(objPtr + 0x64) != 0) { // offset 100 (0x64)
        releaseResourceWithTransform(*(void**)(objPtr + 0x10), *(void**)(objPtr + 0x64), &gDefaultResource15);
    }
    if (*(int*)(objPtr + 0x6c) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x6c), &gDefaultResource1);
    }
    if (*(int*)(objPtr + 0x70) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x70), &gDefaultResource16);
    }
    if (*(int*)(objPtr + 0x74) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x74), &gDefaultResource17);
    }
    if (*(int*)(gGlobalObjectPointer + 0x8c) != 0) {
        releaseResourceWithTransform(*(void**)(gGlobalObjectPointer + 0x10), *(void**)(gGlobalObjectPointer + 0x8c), &gDefaultCustom1); // DAT_01205900
    }
    if (*(int*)(gGlobalObjectPointer + 0x90) != 0) {
        releaseResourceWithTransform(*(void**)(gGlobalObjectPointer + 0x14), *(void**)(gGlobalObjectPointer + 0x90), &gDefaultCustom2); // DAT_01205910
    }
    if (*(int*)(objPtr + 0x78) != 0) {
        releaseResourceWithTransform(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x78), &gDefaultResource18);
    }
    if (*(int*)(objPtr + 0x7c) != 0) {
        releaseResourceWithDefault(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x7c), &gDefaultResource5);
    }
    if (*(int*)(objPtr + 0x80) != 0) {
        releaseResourceWithFlags(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x80), &gDefaultResource5, 3);
    }
    if (*(int*)(objPtr + 0x84) != 0) {
        releaseResourceWithFlags(*(void**)(objPtr + 0x14), *(void**)(objPtr + 0x84), &gDefaultResource6, 3);
    }
    if (*(int*)(objPtr + 0xa0) != 0) {
        finalCleanup(); // FUN_006063b0
    }
}