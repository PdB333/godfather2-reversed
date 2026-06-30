// FUNC_NAME: EntityManager::processActiveObjects
int EntityManager::processActiveObjects(void)
{
    int currentNode;
    uint flags;
    int playerPtr;
    int entityPtr;
    int otherPlayerPtr;
    float savedX;
    float savedY;
    float savedZ;
    float savedW;
    int result;

    result = 0;
    if (*(int *)(this + 0x60) != 0) {
        FUN_0056fbb0();
        savedX = 0.0f;
        savedZ = 0.0f;
        savedY = 0.0f;
        savedW = *(float *)&DAT_00e2b1a4;  // Initialize W with constant
        playerPtr = FUN_00578ad0();  // Get player/camera entity
        if (playerPtr != 0) {
            // Save player's transform (quaternion or position+rotation)
            savedX = *(float *)(playerPtr + 0x10);
            savedY = *(float *)(playerPtr + 0x14);
            savedZ = *(float *)(playerPtr + 0x18);
            savedW = *(float *)(playerPtr + 0x1c);
            FUN_00414aa0();  // Apply some transform operation
        }

        // Check if processing is not disabled (bit 12 of manager flags)
        if ((*(uint *)(this + 0x10) >> 0xc & 1) == 0) {
            // Iterate through the intrusive linked list of active objects
            for (currentNode = *(int *)(this + 0x124); currentNode != 0; currentNode = *(int *)(currentNode + 0x124)) {
                if (playerPtr == 0) {
                    return 0;
                }
                // Skip invalid entries (ID == -1)
                if (*(int *)(currentNode + 0x14) != -1) {
                    // Check if this object needs to be reset (state match)
                    if ((*(int *)(currentNode + 0x11c) == 1) && (*(int *)(currentNode + 0x110) == 1)) {
                        *(int *)(currentNode + 0x1c) = 0;
                    }

                    otherPlayerPtr = FUN_00578ad0();  // Re-fetch player (may have changed)
                    
                    // If object is active and has certain flags set, clear high bit and process
                    if ((*(char *)(currentNode + 0x30) == '\0') &&
                        (flags = *(uint *)(currentNode + 0x10), (flags & 3) != 0) &&
                        ((flags >> 0x1c & 1) != 0)) {
                        *(uint *)(currentNode + 0x10) = flags & 0xefffffff;
                        FUN_00572580();  // Process state change
                    }

                    // If we have a valid player pointer, the player has a transform,
                    // and current object needs processing
                    if (((otherPlayerPtr != 0) && (*(int *)(otherPlayerPtr + 0x38) != 0)) &&
                        ((*(int *)(playerPtr + 0x38) != 0 &&
                          ((FUN_00571db0(), *(char *)(currentNode + 0x120) == '\0' &&
                           (entityPtr = *(int *)(currentNode + 0x60), entityPtr != 0)))))) {

                        // Determine which action to take based on entity type/state
                        if ((*(char *)(entityPtr + 1) == '\0') ||
                            ((**(byte **)(entityPtr + 0xc) & 0x3f) != 0xe)) {
                            if (*(int *)(currentNode + 0x110) == 0) {
                                playerPtr = FUN_00583460(otherPlayerPtr);  // Action: approach/follow target
                            } else {
                                playerPtr = FUN_00583610(savedX);  // Action: use stored position
                            }
                        } else {
                            playerPtr = FUN_00582f90(0);  // Action: flee/disengage
                        }
                        FUN_0056fb60();  // Finalize processing
                    }
                }
            }
        }

        // Restore player transform after processing
        if (playerPtr != 0) {
            *(float *)(playerPtr + 0x10) = savedX;
            *(float *)(playerPtr + 0x14) = savedY;
            *(float *)(playerPtr + 0x18) = savedZ;
            *(float *)(playerPtr + 0x1c) = savedW;
            FUN_00414aa0();  // Restore transform operation
        }
    }
    return result;
}