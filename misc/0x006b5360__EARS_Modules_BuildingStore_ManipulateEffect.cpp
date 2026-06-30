// Xbox PDB: EARS::Modules::BuildingStore::ManipulateEffect
// FUNC_NAME: DebrisPiece::loadOrUnload
// Address: 0x006b5360
bool DebrisPiece::loadOrUnload(int action, char immediate) {
    char nameBuffer[64];          // local_90
    Matrix4x4 transform;          // local_50 - 76 bytes (4x4 matrix + extra)
    float color[4];               // local_a0, local_9c, local_98, local_94
    int newHandle;                // local_a4
    int *nextPtr;                 // piVar1 initially at this+0x180
    char *nameSource;             // pcVar6

    if (immediate == 0) {
        // Quick cleanup path - just release something from sound system?
        if (action != 0) {
            if (action == 1) {
                FUN_004df650(); // likely releaseSound()
            }
            return true;
        }
        FUN_004df650(); // releaseSound()
        return true;
    }

    // Initialize default color from global
    color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 0.0f;
    // Actually the code stores _DAT_00d5780c into local_54, local_68, etc. but we simplify
    // The transform is set from this+0x10, 0x14, 0x18 (position)
    transform.setPosition(*(float*)(this + 0x10), *(float*)(this + 0x14), *(float*)(this + 0x18));
    // FUN_0044b4e0 likely initializes the full transform matrix from position
    FUN_0044b4e0(&transform, &color[0]); // color unused? Might set rotation to identity

    if (action == 0) {
        // Creation case
        nameSource = *(char**)(this + 0x10c);
        if (nameSource == nullptr) {
            nameSource = "default_name"; // DAT_0120546e
        }
        snprintf(nameBuffer, 64, "%s_%u", nameSource, *(uint*)(this + 0x38)); // this->mId
        FUN_004eacb0(&nameBuffer); // likely concatenate or register name
        // Create debris piece with ID-suffixed name
        newHandle = FUN_004df420(&newHandle, &color[0], &transform, 0x2ff, 4, 0, 0xffffffff, 0);
        nextPtr = (int*)(this + 0x180);
        if (*(int*)(this + 0x180) != 0) {
            *(int*)(*(int*)(this + 0x180) + 8) = 0; // clear previous next
            *nextPtr = 0;
        }
        *nextPtr = newHandle;
        if (newHandle != 0) {
            *(int**)(newHandle + 8) = nextPtr; // link back
        }
        if (*nextPtr == 0) {
            // First attempt failed - retry with base name without ID suffix
            nameSource = *(char**)(this + 0x10c);
            if (nameSource == nullptr) {
                nameSource = "default_name";
            }
            FUN_004eacb0(nameSource);
            newHandle = FUN_004df420(&newHandle, &color[0], &transform, 0x2ff, 4, 0, 0xffffffff, 0);
            FUN_00414db0(&newHandle); // likely addRef or register
            if (newHandle != 0) {
                *(int*)(newHandle + 8) = 0;
            }
        } else {
            // Success - also set color from source
            int *colorSource = FUN_008c74d0(*(uint*)(this + 0x40)); // mColorSourceId
            if (colorSource != 0) {
                uint packedColor = *(uint*)(colorSource + 0xfc);
                color[0] = (float)(packedColor & 0xff);
                color[1] = (float)((packedColor >> 8) & 0xff);
                color[2] = (float)((packedColor >> 16) & 0xff);
                color[3] = 0.0f;
                FUN_004df760(&color[0]); // set color on the new handle
            }
        }
        return *nextPtr != 0;
    } else if (action == 1) {
        // Destruction/release case
        int state = thunk_FUN_006b4860(); // some state check
        if ((state == 4) || (state == 3)) {
            nameSource = *(char**)(this + 0x11c);
        } else if (*(int*)(this + 0xfc) == 0) {
            state = thunk_FUN_006b4860();
            if (state != 2) {
                return false;
            }
            nameSource = *(char**)(this + 0x13c);
        } else {
            nameSource = *(char**)(this + 300); // 0x12c
        }
        if (nameSource == nullptr) {
            nameSource = "default_name";
        }
        if (*nameSource == '\0') {
            return false;
        }
        snprintf(nameBuffer, 64, "%s_%u", nameSource, *(uint*)(this + 0x38));
        int result = FUN_0045c740(&newHandle, &nameBuffer, &transform, 0x2ff, 4, 0, 0xffffffff, 0);
        FUN_00414db0(result);
        FUN_00414df0();
        bool success = *(int*)(this + 0x17c) == 0;
        if (!success) {
            result = FUN_0045c740(&newHandle, nameSource, &transform, 0x2ff, 4, 0, 0xffffffff, 0);
            FUN_00414db0(result);
            FUN_00414df0();
            success = *(int*)(this + 0x17c) == 0;
        }
        return !success;
    }
    return false;
}