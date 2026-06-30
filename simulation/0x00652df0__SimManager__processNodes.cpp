// FUNC_NAME: SimManager::processNodes

// Function address: 0x00652df0
// Role: Iterates a linked list of nodes (head at this+0x11C), updates timers, calls a virtual callback,
// and frees each node via FUN_009c8eb0. Global timers are used for decay and clamping.

void __thiscall SimManager::processNodes(void) {
    // Save global time step (float)
    float timeStep = DAT_00e2b04c;

    // Head of node list
    int32_t* nodePtr = *(int32_t**)((uint8_t*)this + 0x11C); // &this->nodeListHead (offset +0x11C)

    while (nodePtr != nullptr) {
        // Current node
        uint8_t* node = (uint8_t*)nodePtr;

        // Advance head to next node (node offset +0x10)
        *(int32_t**)((uint8_t*)this + 0x11C) = *(int32_t**)(node + 0x10);

        // If node's first byte is non-zero, set a flag at this+0xF4 (byte offset)
        if (*node != '\0') {
            *(uint8_t*)((uint8_t*)this + 0xF4) = 1; // this->someFlag = 1
        }

        // Check bitmask 0x0C at this+0xB8 (byte offset)
        if ((*(uint8_t*)((uint8_t*)this + 0xB8) & 0x0C) != 0) {
            // Decay field at this+0x1BC (int interpreted as float) and clamp to timeStep
            float val = (float)(*(int32_t*)((uint8_t*)this + 0x1BC)) * DAT_00e2cd54;
            if (val < timeStep) {
                val = timeStep;
            }
            *(int32_t*)((uint8_t*)this + 0x1BC) = (int32_t)val;

            // Subtract global from field at this+0x1B8, clamp to timeStep
            float otherVal = (float)(*(int32_t*)((uint8_t*)this + 0x1B8)) - DAT_00e2b1a4;
            if (otherVal < timeStep) {
                otherVal = timeStep;
            }
            *(int32_t*)((uint8_t*)this + 0x1B8) = (int32_t)otherVal;
        }

        // Call virtual function at vtable offset 0x40 (0x10th virtual) with node as argument
        (**(void (__thiscall**)(uint8_t*))(*((uint32_t**)this) + 0x40))(node); // this->vtable[0x10](node)

        // Free/release the node
        FUN_009c8eb0(node);

        // Re-read global and head pointer for next iteration
        timeStep = DAT_00e2b04c;
        nodePtr = *(int32_t**)((uint8_t*)this + 0x11C);
    }

    // Restore global time step (safety measure)
    DAT_00e2b04c = timeStep;
}