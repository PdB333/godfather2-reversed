// FUNC_NAME: ObjectManager::deleteObject
// Address: 0x00497b40
// Deletes an object identified by the handle (param_1).
// This member function checks a root pointer at this+0, resolves the handle
// via an internal function, and then proceeds to clean up and deallocate.

void ObjectManager::deleteObject(int handle) {
    // Check if the manager's root pointer is valid (e.g. a list or tree)
    if (*(int*)this != 0) {
        // Local array for handle resolution: [input/output value, output pointer+8 offset]
        int resolveData[2];
        resolveData[0] = handle; // Initialize with the handle
        // Resolve handle to internal data structure
        FUN_004986e0(resolveData);

        // Determine the address to deallocate:
        // If the second element of resolveData is zero, no allocation; otherwise offset +8 (skip header)
        int deallocTarget;
        if (resolveData[1] == 0) {
            deallocTarget = 0;
        } else {
            deallocTarget = resolveData[1] + 8;
        }

        // Perform cleanup for the handle (e.g. remove from tracking)
        FUN_004988f0(&handle);
        // Deallocate the memory at the computed address
        FUN_00497ba0(deallocTarget);
    }
}