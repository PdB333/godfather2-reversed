// FUNC_NAME: PhysicsObject::applyForces
// Function address: 0x004f8aa0
// This function applies forces (impulses, continuous forces) to a physics object, likely a vehicle or character.
// It computes direction from current position to target, normalizes, and applies various force types based on flags.

void __thiscall PhysicsObject::applyForces(void* thisPtr, PhysicsBody* body, const float* targetPos, float deltaTime, int param4, int param5) {
    // Global constants and globals (renamed from DAT_*)
    const float kEpsilon = *reinterpret_cast<float*>(0x00e2cbe0); // Threshold for distance squared
    const float kInvSqrtFactor = *reinterpret_cast<float*>(0x00e2b1a4); // Factor for inverse sqrt normalization
    const float kSpeedThreshold = *reinterpret_cast<float*>(0x00e2e210); // Threshold for speed-based effects
    const float kOtherThreshold = *reinterpret_cast<float*>(0x00e2b05c); // Another threshold
    const float kOffsetConstant = *reinterpret_cast<float*>(0x00e44564); // Constant used in final adjustment

    // Global pointer to physics system (0x012234c4 + 0x18)
    struct PhysicsSystem* physSys = *reinterpret_cast<PhysicsSystem**>(*reinterpret_cast<int*>(0x012234c4) + 0x18);
    // Global function pointer (0x01206688) - used conditionally
    bool (*globalCheckFunc)(PhysicsBody*) = reinterpret_cast<bool (*)(PhysicsBody*)>(0x01206688);

    // --- Compute current position from thisPtr using FS segment ---
    // The FS offset 0x2c likely yields a thread-specific pointer; then +8 yields a structure with a world transform at +0x80
    // The specific field at this+0x10 is an offset into that transform's data (probably index into an array of positions)
    int* fsBase = *reinterpret_cast<int**>(__readfsdword(0x2c)); // Unaff_FS_OFFSET = FS:[0x2c]
    int* worldTransformPtr = *reinterpret_cast<int**>(fsBase[0] + 8); // Maybe "worldTransformArray" or "physicsWorld"
    float* positionPtr = reinterpret_cast<float*>(worldTransformPtr + 0x80 / 4 + *(int*)(thisPtr + 0x10)); // +0x80 offset from worldTransform start

    float currentPos[4];
    currentPos[0] = positionPtr[0];
    currentPos[1] = positionPtr[1];
    currentPos[2] = positionPtr[2];
    currentPos[3] = positionPtr[3];

    // --- Compute direction vector from current to target ---
    float dirVec[4];
    dirVec[0] = targetPos[0] - currentPos[0];
    dirVec[1] = targetPos[1] - currentPos[1];
    dirVec[2] = targetPos[2] - currentPos[2];
    dirVec[3] = targetPos[3] - currentPos[3]; // Usually 0 or 1 in homogeneous coords

    // --- Normalize direction with threshold ---
    float distSq = dirVec[0]*dirVec[0] + dirVec[1]*dirVec[1] + dirVec[2]*dirVec[2];
    float invLen;
    if (distSq <= kEpsilon) {
        invLen = 0.0f; // Zero vector if too close
    } else {
        invLen = kInvSqrtFactor / sqrtf(distSq); // Scaling factor for normalization
    }
    dirVec[0] *= invLen;
    dirVec[1] *= invLen;
    dirVec[2] *= invLen;

    // --- Check cancellation flag ---
    // The byte at this+0x24, first byte (low bit) is a flag
    if ((*reinterpret_cast<byte*>(thisPtr + 0x24) & 1) != 0) {
        int cancelFlag = 0;
        // Call a method on body (likely querying some state) with hash 0xd80c71d2
        bool result = body->vtable->methodAtOffset0x10(body, 0xd80c71d2, &cancelFlag);
        if (result && cancelFlag != 0) {
            return; // Cancel force application
        }
    }

    // --- Apply basic force if physics system is present ---
    if (physSys != nullptr) {
        uint* flagsPtr = reinterpret_cast<uint*>(thisPtr + 0x24); // Pointer to flag/parameter block at this+0x24
        // Check if force type 0xe (index 14) is nonzero
        if (flagsPtr[0xe] != 0) {
            // Build an optional impulse vector from flags
            float impulseVec[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            float* impulsePtr = nullptr;
            if ((*flagsPtr & 4) != 0) {
                // Load impulse from flags[0x12..0x15] (indices 18,19,20,21)
                impulseVec[0] = static_cast<float>(flagsPtr[0x12]);
                impulseVec[1] = static_cast<float>(flagsPtr[0x13]);
                impulseVec[2] = static_cast<float>(flagsPtr[0x14]);
                impulseVec[3] = static_cast<float>(flagsPtr[0x15]);
                impulsePtr = impulseVec;
                if ((*flagsPtr & 8) != 0) {
                    // Scale impulse w component by deltaTime
                    impulseVec[3] = static_cast<float>(flagsPtr[0x16]) * impulseVec[3] * deltaTime;
                }
            }
            // Call function at physSys+8 to apply impulse
            // Parameters: body, direction, forceType14, flags[0xf]*deltaTime, flags shifted, optional impulse
            physSys->vtable->methodAtOffset0x08(body, dirVec, flagsPtr[0xe],
                static_cast<float>(flagsPtr[0xf]) * deltaTime,
                (*flagsPtr >> 1) & 0xffffff01, impulsePtr);
        }

        // Apply another force from fields at offset 0x40 and 0x44 within the flags block
        int* flagsPtrInt = reinterpret_cast<int*>(thisPtr + 0x24);
        if (flagsPtrInt[0x40 / 4] != 0) { // +0x40 (int)
            physSys->vtable->methodAtOffset0x0c(body, dirVec, flagsPtrInt[0x40 / 4],
                *reinterpret_cast<float*>(reinterpret_cast<int>(flagsPtrInt) + 0x44) * deltaTime);
        }

        // --- Apply continuous/rotational force if speed exceeds threshold ---
        float speed = *reinterpret_cast<float*>(reinterpret_cast<int>(flagsPtrInt) + 0x2c);
        if (speed > kSpeedThreshold) {
            // Get some object from this+4->offset 0x20
            int* someObject = *reinterpret_cast<int**>(reinterpret_cast<int*>(thisPtr + 4) + 0x20 / 4);
            // Call function 0x004f95f0 (likely object allocator or factory) with hash and object
            int* resultObj = (int*)FUN_004f95f0(0x32223764, someObject);
            if (resultObj != nullptr) {
                // Extract integers from resultObj (subtract 0x48 from offsets 2 and 4)
                int offset1 = (resultObj[2] != 0) ? (resultObj[2] - 0x48) : 0;
                int offset2 = (resultObj[4] != 0) ? (resultObj[4] - 0x48) : 0;
                // Call methods on resultObj
                int method14Result = resultObj->vtable->methodAtOffset0x14(resultObj);
                // Clamp speed using kOtherThreshold
                float clampedSpeed = speed;
                if (static_cast<float>(resultObj[6]) >= kOtherThreshold) {
                    clampedSpeed = static_cast<float>(resultObj[6]);
                }
                int method1cResult = resultObj->vtable->methodAtOffset0x1c(resultObj);
                // Call physSys+4 to apply continuous force
                physSys->vtable->methodAtOffset0x04(resultObj, body, currentPos, clampedSpeed * deltaTime,
                    *reinterpret_cast<int*>(reinterpret_cast<int>(flagsPtrInt) + 0x28), // flags[0x28]
                    offset1, offset2, method14Result, param4, method1cResult, param5);
            }
        }
    }

    // --- Final adjustment based on angular/other thresholds ---
    uint angularFlags = *reinterpret_cast<uint*>(reinterpret_cast<int>(flagsPtrInt) + 0x30);
    uint angularFlags2 = *reinterpret_cast<uint*>(reinterpret_cast<int>(flagsPtrInt) + 0x34);
    if (static_cast<float>(angularFlags & *reinterpret_cast<uint*>(0x00e44680)) > kSpeedThreshold ||
        static_cast<float>(angularFlags2 & *reinterpret_cast<uint*>(0x00e44680)) > kSpeedThreshold) {
        // Check using global function or fallback method
        bool applyAdjustment;
        if (globalCheckFunc == nullptr) {
            float result = 0.0f;
            bool check = body->vtable->methodAtOffset0x10(body, 0x4f3368d0, &result);
            applyAdjustment = (check && result != 0.0f);
        } else {
            applyAdjustment = globalCheckFunc(body);
        }
        if (applyAdjustment) {
            float scale = *reinterpret_cast<float*>(reinterpret_cast<int>(flagsPtrInt) + 0x30) * deltaTime;
            float adjustedDir[4];
            adjustedDir[0] = scale * dirVec[0];
            adjustedDir[1] = scale * dirVec[1];
            adjustedDir[2] = scale * dirVec[2];
            adjustedDir[3] = *reinterpret_cast<float*>(reinterpret_cast<int>(flagsPtrInt) + 0x34) * deltaTime + scale * dirVec[3];
            // Subtract constant and zero out some components, then call math function
            float temp[3];
            temp[0] = adjustedDir[0];
            temp[1] = adjustedDir[1];
            temp[2] = adjustedDir[2];
            temp[0] = kOffsetConstant - adjustedDir[3]; // note: order might be flipped
            temp[1] = 0.0f;
            temp[2] = 0.0f;
            FUN_0066d1d0(&adjustedDir, temp); // Likely a vector math operation (e.g., cross product, reflection)
        }
    }
}