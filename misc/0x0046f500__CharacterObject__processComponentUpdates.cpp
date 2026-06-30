// FUNC_NAME: CharacterObject::processComponentUpdates

void __thiscall CharacterObject::processComponentUpdates(void) {
    // Initialize component iterator for this object with type filter 0xb390b11a
    ComponentIterator::begin(this, 0xb390b11a);

    int zeroVal = 0;
    int globalCounter = g_frameCounter;
    ComponentNode* currentNode = local_5c;  // Local variable not actually used correctly; loop modifies local_5c
    uint currentIndex = local_ac;
    // The loop iterates over components until no more

    while (true) {
        // Determine if the iteration uses a linked list or array
        bool hasMore = false;
        if (local_b8 == '\0') {
            hasMore = (currentNode != nullptr);
        } else {
            hasMore = (currentIndex < local_a8);
        }
        if (!hasMore) break;

        // Get current component node
        ComponentNode* node = (local_b8 == '\0') ? currentNode : &local_a4;

        // Check the component type
        uint tag;
        if (*(short*)((char*)node + 6) == 0x25e3) {
            tag = *(ushort*)((char*)node + 4);  // Read short at offset 4
        } else {
            tag = *(uint*)((char*)node + 4);    // Read dword at offset 4
        }

        if (tag == 1) {
            // Process transform component
            TransformData transform;
            ComponentData::readTransform(&transform);  // FUN_0043ac60

            // Calculate vector magnitudes from the three vectors in transform
            float x1 = transform.vec1[0], y1 = transform.vec1[1], z1 = transform.vec1[2];
            float x2 = transform.vec2[0], y2 = transform.vec2[1], z2 = transform.vec2[2];
            float x3 = transform.vec3[0], y3 = transform.vec3[1], z3 = transform.vec3[2];

            // Store magnitudes as int (lossy)
            this->speed = (int)sqrt(x1*x1 + y1*y1 + z1*z1);
            this->accelMagnitude = (int)sqrt(x2*x2 + y2*y2 + z2*z2);
            this->forceMagnitude = (int)sqrt(x3*x3 + y3*y3 + z3*z3);

            // Store vector components
            this->velocity.x = (int)x1;
            this->velocity.y = (int)y1;
            this->velocity.z = (int)z1;
            this->velocity.pad = zeroVal;

            this->acceleration.x = (int)x2;
            this->acceleration.y = (int)y2;
            this->acceleration.z = (int)z2;
            this->acceleration.pad = zeroVal;

            this->force.x = (int)x3;
            this->force.y = (int)y3;
            this->force.z = (int)z3;
            this->force.pad = zeroVal;

            // Set timing-related field to global counter
            this->timestamp = globalCounter;

            // Notify that update is complete
            notifyUpdateComplete();  // FUN_006101b0

            // Call virtual apply function at vtable slot 0x1A (since +0x68 from vtable base)
            (this->vtable->applyTransform)();
        } else if (tag == 4) {
            // Process damage/hit component
            if (node->extraData != nullptr) {
                this->hitCount++;  // Increment byte at offset 0x161
            }
        }

        // Advance to next component
        if (local_b8 == '\0') {
            // Linked list advancement: node contains offset to next
            if ((int)currentIndex < 0) {
                local_5c = (ComponentNode**)((char*)currentNode + (int)currentNode);
                ComponentIterator::advance();  // FUN_0043b140
                currentNode = local_5c;
                currentIndex = local_ac;
            } else if ((int)currentIndex < (int)(local_a8 - 1)) {
                currentIndex++;
                local_5c = (ComponentNode**)((char*)currentNode + (int)currentNode);
                currentNode = (ComponentNode**)((char*)currentNode + (int)currentNode);
                currentIndex = local_ac;
            } else {
                local_5c = (ComponentNode**)&endMarker;  // DAT_01163cf8
                currentNode = (ComponentNode**)&endMarker;
            }
        } else {
            // Array advancement using bitmask to skip empty slots
            currentIndex++;
            local_ac = currentIndex;
            if (currentIndex != local_a8) {
                // Check if slot is occupied using bitmask at local_b4
                if ((*((byte*)(local_b4 + (currentIndex >> 3)) & (1 << (currentIndex & 7))) == 0) {
                    local_a4 = local_b0;
                    local_9c = *local_b0;
                    local_b0 = local_b0 + 1;
                } else {
                    local_a4 = nullptr;
                    local_9c = 0;
                }
            }
        }
    }
}