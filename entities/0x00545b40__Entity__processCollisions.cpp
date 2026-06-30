// FUNC_NAME: Entity::processCollisions
void Entity::processCollisions() {
    // Virtual call at vtable+0x198: likely checks if this entity is active (e.g., on ground, not dying)
    if (!((code*)this->vtable[0x198])()) {
        return;
    }

    int flags = this->field_0x360; // [this+0xd8] - some flags (0=usual, non-zero=special)
    float localMatrix[16]; // copy of transform from offset 0x34
    memcpy(localMatrix, &this->field_0xd0, sizeof(localMatrix)); // 16 floats = 64 bytes

    // Some global constant (maybe gravity or scale)
    float globalScale = *(float*)0x00e2b1a4;

    if (flags == 0) {
        // Normal path: scale the translation part of the local matrix by the magnitude of a velocity
        int pPhysicsData = param_1[0xba]; // [this+0x2e8] - pointer to physics (e.g., linear velocity)
        float sqSum = *(float*)(pPhysicsData + 0x1a0) * *(float*)(pPhysicsData + 0x1a0)
                    + *(float*)(pPhysicsData + 0x1a4) * *(float*)(pPhysicsData + 0x1a4)
                    + *(float*)(pPhysicsData + 0x1a8) * *(float*)(pPhysicsData + 0x1a8);
        float magnitude = sqrt(sqSum); // FUN_00414a80

        // localMatrix[12..14] are translation components
        localMatrix[12] = (float)((double)localMatrix[12] * magnitude + (double)(*(float*)(&localMatrix[12])));
        localMatrix[13] = (float)((double)localMatrix[13] * magnitude + (double)localMatrix[13]);
        localMatrix[14] = (float)((double)localMatrix[14] * magnitude + (double)(*(float*)(&localMatrix[14])));
    } else {
        // Special path: check a flag from some global? then call other functions
        char* someFlag = (char*)FUN_009f1be0((int)&someStackVar + 3);
        if ((*someFlag == '\0') && (*(float*)(*(int*)(param_1[0xde] + 0x18) + 0x14) != *(float*)0x00e2b05c)) {
            FUN_009f2000();
        }
        FUN_0055da50();
        FUN_00470d00(localMatrix); // presumably updates physics
    }

    int pCollisionList = param_1[0xd9]; // [this+0x364] - pointer to collision overlap list
    if (pCollisionList != 0) {
        // Global count of collision pairs
        int pairCount = *(int*)0x00e445dc;
        // Global half-extent or something
        int globalHalf = *(int*)0x00e44598;
        // Some base pointer for list
        int listBase = *(int*)&localStack; // actually from stack, reconstructed as: listBase = &localArray[?]

        // Iterate through each pair (size 0x30 per entry)
        for (int i = 0; i < pairCount; i++) {
            int* entry = (int*)((int)listBase + i * 0x30);
            int objA = entry[0x20]; // offset +0x20 from entry
            int objB = entry[0x28]; // offset +0x28 from entry

            int* contactA = 0;
            if (objA != 0 && *(char*)(objA + 0x10) + objA != 0) { // alive check?
                if (FUN_004af8c0(&someLocalPtr, 0x2001)) { // allocate or get? unknown
                    contactA = someLocalPtr;
                }
            }
            int* contactB = 0;
            if (objB != 0 && *(char*)(objB + 0x10) + objB != 0) {
                if (FUN_004af8c0(&anotherLocalPtr, 0x2001)) {
                    contactB = anotherLocalPtr;
                }
            }

            // If both objects are valid and different, dispatch collision event
            if (contactA && contactB && contactA != contactB) {
                if (contactA == this) {
                    char flag = *(char*)(objA + 0x18); // some attribute from objA
                    void (*collisionHandler)(int*, int, int*) = (void (*)(int*, int, int*))((*(int*)contactB)[0xc8]); // vtable+0xc8
                    collisionHandler(contactB, (int)flag, (int*)(entry)); // passing entry as collision data
                } else if (contactB == this) {
                    char flag = *(char*)(objB + 0x18);
                    void (*collisionHandler)(int*, int, int*) = ((*(int*)contactA)[0xc8]);
                    collisionHandler(contactA, (int)flag, (int*)(entry));
                }
            }
        }

        // Cleanup TLS allocation for the list
        if ((int)localStackVar >= 0) {
            TlsGetValue(*(DWORD*)0x01139810);
            FUN_00aa26e0(listBase, (pairCount & 0x3fffffff) * 0x30, 0x17);
        }
    }
}