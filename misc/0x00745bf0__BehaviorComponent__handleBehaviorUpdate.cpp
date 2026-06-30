// FUNC_NAME: BehaviorComponent::handleBehaviorUpdate

// Function address: 0x00745bf0
// This function processes different types of behavior updates (messages) for an AI component.
// It distinguishes between two message types: one for distance-based checks (type 0x1b2d5c51)
// and one for activation (type 0x485311a7). The function updates a linked list of active
// entries and modifies state fields based on the message type.

void __thiscall BehaviorComponent::handleBehaviorUpdate(BehaviorComponent *this, BehaviorUpdateMessage *message)
{
    int *listHeadPtr;
    int activeEntry;
    int positionA;
    int positionB;
    float dx, dy, dz;
    int chosenState;
    float distanceSq;
    float thresholdSq;

    // Determine the message type by calling the virtual function on the message object
    int messageType = message->getType();

    if (messageType == 0x1b2d5c51) { // Distance-based update
        // Get two position objects (likely transforms or entities)
        positionA = getPosition();   // FUN_00471610
        positionB = getPosition();   // FUN_00471610

        // Compute difference vector (positionB - positionA)
        dx = *(float *)(positionB + 0x30) - *(float *)(positionA + 0x30);
        dy = *(float *)(positionB + 0x34) - *(float *)(positionA + 0x34);
        dz = *(float *)(positionB + 0x38) - *(float *)(positionA + 0x38);

        // Retrieve the sensor/perception component (offset +0x68)
        SensorData* sensor = *(SensorData**)((char*)this + 0x68);

        // Compare squared distance against the threshold at offset +0x70 of sensor
        distanceSq = dx*dx + dy*dy + dz*dz;
        if (sensor->activationThresholdSq <= distanceSq) {
            chosenState = sensor->stateOutOfRange;   // offset +0x6c
        } else {
            chosenState = sensor->stateInRange;      // offset +0x68
        }

        // Determine the current active entry from the component's list head (offset +0x5c)
        if (*(int*)((char*)this + 0x5c) == 0) {
            activeEntry = 0;
        } else {
            activeEntry = *(int*)((char*)this + 0x5c) - 0x48; // Adjust to node base
        }

        // Manage linked list: insert/remove the active entry in the message's list (offset +0x19 * 4 = +0x64)
        listHeadPtr = (int*)((char*)message + 0x64); // &message->activeListHead
        if (activeEntry == 0) {
            activeEntry = 0;
        } else {
            activeEntry = activeEntry + 0x48; // Re-adjust? This seems odd, maybe a different calculation
        }

        if (*listHeadPtr != activeEntry) {
            if (*listHeadPtr != 0) {
                removeFromList(listHeadPtr); // FUN_004daf90
            }
            *listHeadPtr = activeEntry;
            if (activeEntry != 0) {
                message->activeListNext = *(int*)(activeEntry + 4); // offset +0x1a *8? Actually +0x68 relative to message
                *(int**)(activeEntry + 4) = listHeadPtr; // Link the node
            }
        }

        // Update message fields from sensor data
        message->stateField1 = chosenState;                          // offset +0x18
        message->stateField2 = sensor->additionalState;              // offset +0x74
    }
    else if (messageType == 0x485311a7) { // Activation update
        initializeUpdate(message); // FUN_00745060

        // Check if a specific state (offset +0x0c) equals 3
        if (*(int*)((char*)this + 0x0c) == 3) {
            playAnimation(1); // FUN_0075b520

            int targetBase = *(int*)(*(int*)((char*)this + 0x58) + 0x24c4);
            if (targetBase == 0) {
                targetBase = 0;
            } else {
                targetBase -= 0x48; // Adjust to node base
            }
            setDestination(targetBase); // FUN_0075bc60
        }

        // Get the path/waypoint component (offset +0x70)
        int pathComponent = *(int*)((char*)this + 0x70);
        if (pathComponent == 0) {
            pathComponent = 0;
        } else {
            pathComponent -= 0x50; // Adjust base
        }

        // Set some entity reference at offset +0x98 of the path component
        *(int*)(pathComponent + 0x98) = *(int*)((char*)this + 0x58);

        // Set a byte flag at this+100 (0x64) - maybe activation flag
        setActivationFlag(*(char*)((char*)this + 100)); // FUN_0075c4e0

        if (*(int*)((char*)this + 0x70) != 0) {
            finalizeUpdate(); // FUN_0075b920
            return;
        }
        finalizeUpdate(); // FUN_0075b920
    }
    return;
}