// FUNC_NAME: BlendController::updateBlend

int __thiscall BlendController::updateBlend(float* outBlendFactor) {
    int* pThis = reinterpret_cast<int*>(this);
    int* sourceA = reinterpret_cast<int*>(pThis[0x25]); // +0x94 - first source data (pointer)
    int* sourceB = reinterpret_cast<int*>(pThis[0x27]); // +0x9c - second source data (pointer)

    // Early exit if either source is missing - attempt to reset
    if (sourceA == nullptr || sourceB == nullptr) {
        this->shutdown(0); // FUN_005fea70(0) - likely reset/blend completion
        sourceA = reinterpret_cast<int*>(pThis[0x25]);
        sourceB = reinterpret_cast<int*>(pThis[0x27]);

        if (sourceA == nullptr || sourceB == nullptr) {
            int* target = reinterpret_cast<int*>(pThis[0x22]); // +0x88 - target pointer
            int* targetData = (target != nullptr) ? reinterpret_cast<int*>(pThis[0x24]) : nullptr; // +0x90

            // Copy target data to output (first 3 floats)
            pThis[0] = *targetData;
            pThis[1] = targetData[1];
            pThis[2] = targetData[2];

            pThis[0x30] = 0; // +0xc0 - blend progress
            this->removeFromList(reinterpret_cast<void**>(pThis + 0x1f)); // FUN_005f7ba0 - remove node at +0x7c
            this->removeFromList(reinterpret_cast<void**>(pThis + 0x22)); // +0x88
            this->removeFromList(reinterpret_cast<void**>(pThis + 0x25)); // +0x94

            if (pThis[0x1f] != 0 && pThis[0x21] != 0) { // +0x7c and +0x84
                int* pivotData = reinterpret_cast<int*>(pThis[0x21]); // +0x84 - data from linked node
                pThis[0x18] = pivotData[0]; // +0x60 - position x
                pThis[0x19] = pivotData[1]; // +0x64 - position y
                pThis[0x1a] = pivotData[2]; // +0x68 - position z
            }

            pThis[0x2d] |= 0x4001; // +0xb4 - set flags (bit 0 and bit 14)
            pThis[0x2c] = 0; // +0xb0 - reset some state

            if (reinterpret_cast<void(*)(void)>(pThis[0x29]) != nullptr) { // +0xa4 - callback
                reinterpret_cast<void(*)(void)>(pThis[0x29])();
            }
            return 3; // blend complete (reset and return new value)
        }
    } else {
        unsigned int flags = pThis[0x2d]; // +0xb4
        if ((flags >> 3 & 1) == 0 && pThis[0x38] == 1) { // +0xe0 - state?
            pThis[0x38] = 2;
        } else {
            if ((flags >> 5 & 1) == 0) {
                float currentBlend = static_cast<float>(pThis[0x42]); // +0x108 - current blend factor
                float storedBlend = static_cast<float>(pThis[0x41]); // +0x104 - stored blend factor
                if (storedBlend != currentBlend) {
                    pThis[0x40] = static_cast<int>(currentBlend); // +0x100 - save as int? (may be rounding)
                    pThis[0x41] = static_cast<int>(currentBlend);
                }
            }
            if ((flags >> 6 & 1) == 0) {
                float value2 = static_cast<float>(pThis[0x3f]); // +0xfc - another float
                float stored2 = static_cast<float>(pThis[0x3e]); // +0xf8
                if (stored2 != value2) {
                    pThis[0x3d] = static_cast<int>(value2); // +0xf4
                    pThis[0x3e] = static_cast<int>(value2);
                }
            }
        }
    }

    // Check if we need to compute distance between two sources
    if (((pThis[0x2d] >> 7 & 1) != 0) && // bit 7
        (pThis[0x1f] == pThis[0x25]) && // +0x7c == +0x94
        ((pThis[0x1f] == 0 || (pThis[0x21] == pThis[0x27])) && // +0x84 == +0x9c
         ((pThis[0x2d] >> 6 & 1) == 0))) {
        float* targetData2 = (pThis[0x22] != 0) ? reinterpret_cast<float*>(pThis[0x24]) : nullptr; // +0x88, +0x90
        float* sourceData = (pThis[0x25] != 0) ? reinterpret_cast<float*>(pThis[0x27]) : nullptr; // +0x94, +0x9c

        double diff = static_cast<double>(*sourceData - *targetData2);
        this->someCacheFunction(); // FUN_00b9a9fa - likely cache/macro
        float blendDelta = static_cast<float>(diff);
        pThis[0x3f] = static_cast<int>(blendDelta); // +0xfc
        pThis[0x3d] = static_cast<int>(blendDelta); // +0xf4
        pThis[0x3e] = static_cast<int>(blendDelta); // +0xf8
    }

    // Update linked list pointers: swap target/prev
    int* prevPtr = pThis + 0x1c; // +0x70
    int* currentPtr = pThis + 0x1f; // +0x7c
    if (prevPtr != currentPtr) {
        int val = *currentPtr;
        if (*prevPtr != val) {
            if (*prevPtr != 0) {
                this->freeNode(prevPtr); // FUN_004daf90 - remove old node
            }
            pThis[0x1c] = val;
            if (val != 0) {
                pThis[0x1d] = *(reinterpret_cast<int*>(val + 4)); // +0x74 - next pointer
                *reinterpret_cast<int**>(val + 4) = prevPtr; // link back
            }
        }
    }

    // Similarly for next pointer
    int* nextPtr = pThis + 0x22; // +0x88
    pThis[0x1e] = pThis[0x21]; // +0x78 = +0x84 (copy previous link)
    if (currentPtr != nextPtr) {
        int val = *nextPtr;
        if (*currentPtr != val) {
            if (*currentPtr != 0) {
                this->freeNode(currentPtr);
            }
            *currentPtr = val;
            if (val != 0) {
                pThis[0x20] = *(reinterpret_cast<int*>(val + 4)); // +0x80
                *reinterpret_cast<int**>(val + 4) = currentPtr;
            }
        }
    }

    pThis[0x21] = pThis[0x24]; // +0x84 = +0x90 (copy data pointer)

    // Another linked list update
    if (nextPtr != pThis + 0x25) { // +0x94
        int val = pThis[0x25];
        if (*nextPtr != val) {
            if (*nextPtr != 0) {
                this->freeNode(nextPtr);
            }
            *nextPtr = val;
            if (val != 0) {
                pThis[0x23] = *(reinterpret_cast<int*>(val + 4)); // +0x8c
                *reinterpret_cast<int**>(val + 4) = nextPtr;
            }
        }
    }
    pThis[0x24] = pThis[0x27]; // +0x90 = +0x9c

    this->commitListChanges(); // FUN_005f5ce0 - finalize list updates

    int currentIndex = pThis[0x30]; // +0xc0 - blend progress
    int totalDistance = pThis[0x31]; // +0xc4 - total distance (integer? but used as float)
    *outBlendFactor = static_cast<float>(currentIndex) - static_cast<float>(totalDistance);

    // Copy position from linked source
    int* posSource = (pThis[0x1f] != 0) ? reinterpret_cast<int*>(pThis[0x21]) : nullptr; // +0x7c, +0x84
    if (posSource != nullptr) {
        pThis[0x18] = *posSource;       // +0x60
        pThis[0x19] = posSource[1];     // +0x64
        pThis[0x1a] = posSource[2];     // +0x68
    }

    // Compute distance to target for clamping
    float* targetPos = (pThis[0x22] != 0) ? reinterpret_cast<float*>(pThis[0x24]) : nullptr; // +0x88, +0x90
    if (targetPos != nullptr) {
        float dx = static_cast<float>(pThis[0x18]) - targetPos[0];
        float dy = static_cast<float>(pThis[0x19]) - targetPos[1];
        float dz = static_cast<float>(pThis[0x1a]) - targetPos[2];
        pThis[0x31] = static_cast<int>(sqrt(dx*dx + dy*dy + dz*dz)); // +0xc4
    }

    pThis[0x30] = 0; // reset blend progress

    // Advance frame counter if callback exists
    if (reinterpret_cast<void*>(pThis[0x46]) != nullptr) { // +0x118 - callback object
        unsigned int currentFrame = pThis[0x48]; // +0x120 - frame counter
        int totalFrames = (**(int (__thiscall**)(void*))(*(int*)pThis[0x46] + 8))(); // vtable +8 -> getFrameCount
        if (currentFrame < static_cast<unsigned int>(totalFrames - 1)) {
            pThis[0x48] = currentFrame + 1;
        }
    }

    if (reinterpret_cast<void(*)(void)>(pThis[0x29]) != nullptr) {
        reinterpret_cast<void(*)(void)>(pThis[0x29])();
    }

    return 1; // blend in progress
}