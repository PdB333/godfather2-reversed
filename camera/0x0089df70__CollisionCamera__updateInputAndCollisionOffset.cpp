// FUNC_NAME: CollisionCamera::updateInputAndCollisionOffset

void __thiscall CollisionCamera::updateInputAndCollisionOffset(int* this, float* inputVector)
{
    char isActive;
    int hashValue;
    int* someIntPtr;
    int unknownGlobal;
    float unaff_EBX; // value from EBX register, possibly a global or stored in a static
    float distanceCalc;
    float quatX, quatY, quatZ, quatW; // local quaternion components
    float positionX, positionY, positionZ; // position from current object
    float stackQuat[4]; // quaternion passed to setOffset
    float someFloat;

    // Determine a distance value: if field_08 is zero use 0, else subtract 72 and cast to float
    if (this[2] == 0) {
        quatX = 0.0f;
    } else {
        quatX = (float)(this[2] + -0x48);  // field_08 - 72
    }

    // Virtual call: set some distance (maybe camera distance)
    (*(void (__thiscall**)(int, float))(*(int*)this + 0x20))(this, quatX);

    // Virtual call: check if something is active
    isActive = (*(char (__thiscall**)(int))(*(int*)this + 0xc))(this);

    if (isActive == 0) {
        // Not active
        if (this[4] != 0) {
            // Call to reset or cancel something
            FUN_004df600();
        }
        this[7] = 0;  // clear hash
    } else {
        // Active branch
        if ((this[4] != 0) &&
            (this[7] != (((int)*inputVector * 0x21 + (int)inputVector[1]) * 0x21 + (int)inputVector[2]) * 0x21 + (int)inputVector[3]))
        {
            // Input changed, trigger update
            FUN_004df600();
            this[7] = 0;
        }

        if (this[4] == 0) {
            this[7] = 0;
            // Check a global (reg) value is non-zero and some other conditions
            if ((unaff_EBX != 0.0f) &&
                (isActive = FUN_00445250(), isActive != 0) &&
                (isActive = FUN_00420980(), isActive == 0))
            {
                // Build a quaternion from input vector
                quatX = *inputVector;
                quatY = inputVector[1];
                quatZ = inputVector[2];
                quatW = inputVector[3];
                // Allocate a resource (0x1ff = 511, maybe a hash or type)
                int resourceId = FUN_00471610(0x1ff, 0, unaff_EBX, 0xffffffff, 0);
                // Setup some structure and retrieve a hash
                int result = FUN_004df330(&stack0xffffffb8, &quatX, resourceId);
                FUN_00414db0(result);
                FUN_00414df0();
                someIntPtr = (int*)FUN_00445210(&stack0xffffffb8);
                this[7] = *someIntPtr;  // store hash
                FUN_004df710();
                *(unsigned char*)(((int)this) + 0x5c) = 0;  // clear byte at offset 0x5c
            }
            if (this[4] == 0) {
                return;
            }
        }

        // Check global pointer at DAT_012233a0+4
        unknownGlobal = *(int*)(*(int*)DAT_012233a0 + 4);
        if (unknownGlobal != 0 && unknownGlobal != 0x1f30) {
            // Get current frame data (no parameters)
            int frameData = FUN_00471610();
            // Read position offsets from the frame data
            quatX = *(float*)(frameData + 0x30);
            quatZ = *(float*)(frameData + 0x38);
            quatW = _DAT_00d5780c;  // some constant (maybe close distance threshold)
            quatY = 0.0f;

            // Virtual call to get current position (writes to stack)
            (*(void (__thiscall**)(int, float*))(*(int*)this + 4))(this, &positionX);
            // Stack variables: positionX, positionY (fStack_20), positionZ (fStack_1c) and unaff_EBX (fStack_28) are set by the virtual call
            // Note: align to actual decompiled locals
            // The call wrote to uStack_24, fStack_20, fStack_1c, etc.
            // Here we assume the call wrote to stack variables that correspond to position
            // Original: (**(code **)(*param_1 + 4))(&uStack_24);
            // Then: uStack_24 = 0; and subsequent subtraction uses local_44, fStack_40, fStack_3c, and unaff_EBX as fStack_28.
            // Since we cannot perfectly reconstruct the stack layout, we will use algebra that matches the decompiled logic.

            // After the virtual call, the code sets uStack_24=0 (zero out the first value returned? Probably a quaternion or vector)
            // Then it computes differences:
            // local_44 = local_44 - 0.0; (quatX already set, subtract 0)
            // fStack_40 = fStack_40 - fStack_20; (quatY - positionY)
            // fStack_3c = fStack_3c - fStack_1c; (quatZ - positionZ)
            // Then distance calculation: sqrt(local_44*local_44 + fStack_40*fStack_40 + (unaff_EBX - fStack_28)*(unaff_EBX - fStack_28))
            // Note: unaff_EBX acts as the fStack_28 value from the virtual call (maybe the 4th component, like w)
            // And _DAT_00d5780c is compared with the distance.

            // To match the decompiled, we treat the stack positions as the result of the virtual call.
            // For simplicity, we rename:
            // local_44 -> xDiff, fStack_40 -> yDiff, fStack_3c -> zDiff, unaff_EBX -> wDiff (fourth component from virtual call)
            // But the code uses unaff_EBX both as a global and as part of the position? That's inconsistent.
            // Actually the unaff_EBX in the distance calculation is the leftover from fStack_28, which originally came from the virtual call.
            // We'll just simulate as per decompiled.

            // To avoid confusion, we will use the exact variables from the decompiled but with comments.

            // After the virtual call, the code does:
            // uStack_24 = 0;  // zero out first component of returned quaternion? But then it uses local_44, fStack_40, fStack_3c, and unaff_EBX as if they are the target position.
            // Note that local_44, fStack_40, fStack_3c were already set to quatX, quatY, quatZ from frameData.
            // So we compute:
            // local_44 = local_44 - 0.0; (no change)
            // fStack_40 = fStack_40 - fStack_20; (quatY - positionY)
            // fStack_3c = fStack_3c - fStack_1c; (quatZ - positionZ)
            // fVar5 = sqrt(local_44*local_44 + fStack_40*fStack_40 + (unaff_EBX - fStack_28)*(unaff_EBX - fStack_28));
            // fStack_34 = 0.0;
            // if (_DAT_00d5780c < fVar5) {
            //     fStack_34 = fVar5 * DAT_00d5f374;
            // }
            // fStack_38 = 0.0;
            // uStack_30 = 0;
            // fStack_2c = _DAT_00d5780c;
            // FUN_004df870(&fStack_38); // pass quaternion with offset?

            // We'll implement accordingly with meaningful names.

            // After the virtual call, the result is placed in local variables.
            // Then we compute a distance and set a quaternion for offset.

            // I will reconstruct the exact operations using the same local variables.
            // The original local_44 (quatX) is reused, etc.

            // Let's define the stack layout as per the decompiled:
            float xDiff;   // local_44
            float yDiff;   // fStack_40
            float zDiff;   // fStack_3c
            float wDiff;   // unaff_EBX (as used in distance calc, from fStack_28)
            float dist;    // fVar5
            float threshold = _DAT_00d5780c;  // from global
            float multiplier = DAT_00d5f374;  // from global
            float offsetQuat[4];  // fStack_38, fStack_2c, fStack_34, uStack_30

            xDiff = quatX;   // from frameData+0x30
            yDiff = quatY;   // from frameData+0x38? Actually quatZ is from frameData+0x38, careful.
            // Original: local_44 = *(float *)(iVar4 + 0x30); fStack_3c = *(float *)(iVar4 + 0x38);
            // So local_44 = x, fStack_3c = z. Then fStack_40 = 0.0? Actually fStack_40 = 0.0 set above.
            // Let's re-evaluate assignment:
            // In the code: local_44 = *(float *)(iVar4 + 0x30); fStack_3c = *(float *)(iVar4 + 0x38); fStack_38 = _DAT_00d5780c; fStack_40 = 0.0;
            // So local_44 = x, fStack_40 = 0, fStack_3c = z, and fStack_38 = threshold.
            // Then after the virtual call (which writes to uStack_24 and presumably to the stack), we have:
            // uStack_24 = 0; (override first value)
            // local_44 = local_44 - 0.0; (unchanged)
            // fStack_40 = fStack_40 - fStack_20; (0 - positionY)
            // fStack_3c = fStack_3c - fStack_1c; (z - positionZ)
            // Also note: unaff_EBX is used as fStack_28 in distance, which came from virtual call.
            // So we must keep track: fStack_28 comes from the virtual call (the w component or something).
            // For simplicity, I will implement a version that logically matches, but maybe the decompiled is too convoluted. I'll produce the code with comments noting the virtual call.

            // I'll write the code as it appears, renaming locals.

            float frameX = *(float*)(unknownGlobal + 0x30);
            float frameZ = *(float*)(unknownGlobal + 0x38);
            // fStack_40 = 0.0
            // fStack_38 = threshold

            float cameraPosX, cameraPosY, cameraPosZ, cameraPosW; // from virtual call
            // call vfunc +4, writes to &cameraPosX (address of local)
            // Then uStack_24 = 0; means cameraPosX = 0

            // Reconstruct:
            float tempX = frameX;           // local_44
            float tempY = 0.0f;             // fStack_40
            float tempZ = frameZ;           // fStack_3c
            float tempW = threshold;        // fStack_38 (used as quat element? later overwritten)

            // Virtual call results (written to locals)
            float vcX, vcY, vcZ, vcW; // correspond to uStack_24, fStack_20, fStack_1c, fStack_28
            // Call: (*(code **)(*param_1 + 4))(&uStack_24);
            // After call, we set uStack_24 = 0; (vcX = 0)
            vcX = 0; // uStack_24 set to 0
            // The other values from the call remain: vcY = fStack_20, vcZ = fStack_1c, vcW = unaff_EBX (as fStack_28)
            // These are set by the virtual call (unknown).

            // Now compute differences:
            tempX = tempX - vcX; // = frameX - 0
            tempY = tempY - vcY; // = 0 - vcY
            tempZ = tempZ - vcZ; // = frameZ - vcZ
            // Note: unaff_EBX is used as vcW from the virtual call, and also as value for subtraction (unaff_EBX - fStack_28)
            // But unaff_EBX is also a register value that may be from earlier; the decompiler reuses it.
            // In the distance calc: (unaff_EBX - fStack_28) where fStack_28 = vcW.
            // So we need the unaff_EBX from the register. We'll use a variable for that register value, call it regW.
            float regW = unaff_EBX; // the register value from earlier context
            float dist = sqrt(tempX*tempX + tempY*tempY + (regW - vcW)*(regW - vcW));

            float retract = 0.0f; // fStack_34
            if (threshold < dist) {
                retract = dist * multiplier;
            }

            // Build offset quaternion:
            offsetQuat[0] = retract;      // fStack_34
            offsetQuat[1] = 0.0f;         // fStack_38? Actually fStack_38 was threshold but now overwritten? The assignment order: fStack_34 = retract; fStack_38 = 0.0; uStack_30 = 0; fStack_2c = threshold;
            // Actually after the if, the code sets:
            // fStack_34 = 0.0; then if condition -> fStack_34 = dist*mult;
            // Then fStack_38 = 0.0; uStack_30 = 0; fStack_2c = _DAT_00d5780c;
            // Then call FUN_004df870(&fStack_38);
            // But &fStack_38 is the address of fStack_38, which is offsetQuat[1]? In C array, passing &array[1] would be offsetQuat+1.
            // In the actual stack, fStack_38 is a separate float variable, not part of an array? The decompiled shows fStack_38, fStack_34, uStack_30, fStack_2c as separate locals.
            // The call passes &fStack_38, so it takes the address of fStack_38. For clarity, we'll treat it as a pointer to a 4-float structure.
            // We'll pack them into an array aligned to original order.

            // Compose the quaternion/vector for FUN_004df870:
            // fStack_38 = 0.0
            // uStack_30 = 0 (int zero)
            // fStack_2c = threshold
            // fStack_34 = retract

            // Order as passed: &fStack_38 -> points to float at fStack_38, then presumably the other fields sequentially in stack.
            // So the structure might be: { fStack_38, uStack_30, fStack_2c, fStack_34 }? But uStack_30 is int, so padding?
            // To keep it simple, we'll use a struct with appropriate offsets.
            // We'll define a local array of 4 floats and set them in the order they appear in the original stack.
            // The decompiled stack layout (after all assignments) is:
            // fStack_38 = 0.0
            // uStack_30 = 0 (int) but we can use float
            // fStack_2c = threshold
            // fStack_34 = retract
            // However, the call uses &fStack_38, so it treats those 4 floats as a quaternion? Possibly {0, 0, threshold, retract}? Not sure.
            // To avoid over-engineering, I'll just mimic the exact assignments and call.

            // Set the components as per the original code:
            float fStack_34_val = 0.0f;
            if (threshold < dist) {
                fStack_34_val = dist * multiplier;
            }
            float fStack_38_val = 0.0f;
            int uStack_30_val = 0;
            float fStack_2c_val = threshold;

            // Call with pointer to fStack_38_val (assume contiguous in memory as expected by callee)
            // Note: the callee expects a pointer to a structure that includes these four values.
            // We'll use a struct to ensure correct layout.
            struct OffsetData {
                float a; // fStack_38
                int b;   // uStack_30 (zero)
                float c; // fStack_2c
                float d; // fStack_34
            } offsetData = { fStack_38_val, uStack_30_val, fStack_2c_val, fStack_34_val };
            FUN_004df870(&offsetData);
            return;
        }
    }
    return;
}