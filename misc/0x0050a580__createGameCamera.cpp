// FUNC_NAME: createGameCamera
int createGameCamera()
{
    int managerPtr;
    int subPtr;
    int allocator;
    undefined4 allocParams[3];
    int newCamera;

    // Get the global game manager (e.g., GodfatherGameManager)
    managerPtr = FUN_00421170();
    if (managerPtr != 0) {
        // Dereference offset +0x14 to get a sub-manager (e.g., CameraManager or PlayerManager)
        subPtr = *(int *)(managerPtr + 0x14);
    } else {
        subPtr = 0;
    }

    newCamera = 0;
    if (subPtr != 0) {
        // Get the memory allocator (vtable-based)
        allocator = FUN_009c8f80();
        allocParams[0] = 2;          // alignment or type
        allocParams[1] = 0x10;       // maybe category
        allocParams[2] = 0;          // flags

        // Allocate 0xA0 bytes using the allocator's virtual function
        newCamera = (**(code **)*allocator)(0xa0, &allocParams);
        if (newCamera == 0) {
            return 0;
        }

        // Initialize the new camera object (constructor-like)
        FUN_0060ffd0();

        // Zero out two fields at offsets +0x90 and +0x94
        *(undefined4 *)(newCamera + 0x90) = 0;
        *(undefined4 *)(newCamera + 0x94) = 0;

        // Register the camera with the sub-manager (e.g., addCamera)
        FUN_004bfc10(subPtr, 0, 0, 0);
    }

    return newCamera;
}