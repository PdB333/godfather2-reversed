// FUNC_NAME: CameraManager::createCamera
// Address: 0x0059a8a0
// Creates a new camera from a definition and adds it to the camera list.
// Uses a slot manager (free list) for camera objects.
// Maintains a byte array of camera slot indices at this+0x7a, with count at this+0x79.

void __fastcall CameraManager::createCamera(uint *thisPtr)
{
    uint slotMgrPtr;
    int freeIdx;
    int *cameraObj;
    uint slotIdx;
    uint cameraDefPtr;

    // Check camera type (expected 0x10)
    if (*(short *)(thisPtr[2] + 2) != 0x10) {
        (**(code **)(*DAT_01205590 + 4))(); // error handler
    }

    slotMgrPtr = thisPtr[0x6f]; // +0x1BC: pointer to slot manager
    cameraDefPtr = thisPtr[2];  // +0x08: pointer to camera definition

    // Get a free slot index from the slot manager's free list
    freeIdx = *(int *)(slotMgrPtr + 0x28); // +0x28: current free index
    if (freeIdx != -1) {
        // Remove from free list: set current free to next, mark slot as -2 (allocated)
        *(int *)(slotMgrPtr + 0x28) = *(int *)(*(int *)(slotMgrPtr + 0x24) + freeIdx * 4);
        *(int *)(*(int *)(slotMgrPtr + 0x24) + freeIdx * 4) = 0xfffffffe;
    }

    // Store the new slot index in the camera index array at this+0x7a, indexed by current count
    *(char *)(*(byte *)((int)thisPtr + 0x79) + 0x7a + (int)thisPtr) = (char)freeIdx;

    // Check if the stored index is valid (not -1)
    if (*(char *)(*(byte *)((int)thisPtr + 0x79) + 0x7a + (int)thisPtr) == -1) {
        (**(code **)(*DAT_01205590 + 8))
            (DAT_01205590,
             "The Trinity create new camera index has exceeded the allocated array boundaries. Make sure cameras are being freed properly during the IGC!");
    }

    slotIdx = (uint)*(byte *)(*(byte *)((int)thisPtr + 0x79) + 0x7a + (int)thisPtr);
    slotMgrPtr = thisPtr[0x6f];

    // Verify the slot is marked as allocated (-2)
    if (*(int *)(*(int *)(slotMgrPtr + 0x24) + slotIdx * 4) != -2) {
        (**(code **)(*DAT_01205590 + 4))(); // error
    }

    // Get the camera object pointer from the slot manager's object array
    cameraObj = *(int **)(*(int *)(slotMgrPtr + 0x20) + slotIdx * 4);
    if (cameraObj != (int *)0x0) {
        // Call virtual function (likely camera init) with parameters from definition
        (**(code **)(*cameraObj + 4))
            (thisPtr, *(undefined4 *)(cameraDefPtr + 4), *(undefined4 *)(cameraDefPtr + 8),
             *(undefined4 *)(cameraDefPtr + 0xc));

        // If this is the first camera (count == 0), set its parent to null
        if (*(byte *)((int)thisPtr + 0x79) == 0) {
            cameraObj[0x1b] = 0; // +0x6C: parent camera pointer
            *(char *)((int)thisPtr + 0x79) = *(char *)((int)thisPtr + 0x79) + 1; // increment count
            *thisPtr = *thisPtr | 8; // set flag bit 3
            return;
        }

        // For subsequent cameras, set parent to the previous camera in the list
        slotMgrPtr = thisPtr[0x6f];
        // Read the previous camera's slot index from the array at this+0x79 (parent array)
        uint prevSlotIdx = (uint)*(byte *)(*(byte *)((int)thisPtr + 0x79) + 0x79 + (int)thisPtr);
        if (*(int *)(*(int *)(slotMgrPtr + 0x24) + prevSlotIdx * 4) != -2) {
            (**(code **)(*DAT_01205590 + 4))(); // error
        }
        cameraObj[0x1b] = *(int *)(*(int *)(slotMgrPtr + 0x20) + prevSlotIdx * 4); // set parent
        *(char *)((int)thisPtr + 0x79) = *(char *)((int)thisPtr + 0x79) + 1; // increment count
        *thisPtr = *thisPtr | 8; // set flag bit 3
        return;
    }

    // If camera object is null, error
    (**(code **)(*DAT_01205590 + 4))();
    return;
}