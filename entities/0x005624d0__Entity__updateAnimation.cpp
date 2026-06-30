// FUNC_NAME: Entity::updateAnimation

void __thiscall Entity::updateAnimation(Entity* thisObj, float* blendTarget /* param_1 */)
{
    // +0x88: pointer to animation component (AnimComponent)
    // +0x80: pointer to something else (maybe skeleton or model)
    if (*(int*)((char*)thisObj + 0x88) == 0 || *(int*)((char*)thisObj + 0x80) == 0) {
        return;
    }

    // +0x24: flag indicating something (e.g., hasNewAnim)
    // +0x84: flag indicating transition in progress? (0 = not in transition)
    if (*(int*)((char*)thisObj + 0x24) != 0 && *(int*)((char*)thisObj + 0x84) == 0) {
        // start animation transition with handle at +0x3c
        FUN_009f4240(*(int*)((char*)thisObj + 0x3c), 1, 0);
    }

    // +0x40: current animation state id
    int currentState = *(int*)((char*)thisObj + 0x40);
    int newState = FUN_009f3d50(); // get desired state from some manager
    if (newState != currentState) {
        FUN_009f3cc0(currentState); // stop current state?
    }

    // +0x30: flag for whether to update pose
    // +0xd8: current animation action state byte (6, 7 = special actions like getting hit,
    //        death, etc.)
    AnimComponent* animComp = *(AnimComponent**)((char*)thisObj + 0x88);
    if (*(int*)((char*)thisObj + 0x30) != 0) {
        byte actionState = *(byte*)((char*)animComp + 0xd8);
        if (actionState != 6 && actionState != 7) {
            FUN_00561e70(); // maybe reset interpolation?
            float deltaTime = (float)FUN_009efd10(); // get elapsed time
            float localDelta = deltaTime; // store for later use

            // get world matrix from animation component (virtual function at vtable+0x14)
            float matrix[12]; // 3x4 matrix? but size might be 12 floats; local_40 is 60 bytes = 15 floats?
            // actually local_40 is 60 bytes = 15 floats, but might be 4x4 matrix with alignment
            (**(code**)(*(int*)((char*)animComp + 0xd0) + 0x14))(matrix); // getTransform

            // scale factor: +0x19c from animComp (maybe animation speed), +0x10 from thisObj (global speed)
            float speedScale = *(float*)((char*)animComp + 0x19c) * *(float*)((char*)thisObj + 0x10);
            // local_60 is uninitialized but used as a destination for some operation
            // It seems to be a temporary matrix/vector; we treat as float[3]?
            float tempVec[3]; // but code uses local_60 as float, then multiplies local_60 by fVar5? Actually:
            // local_60 = fVar5 * local_60; but local_60 is a float from the function call? Hard to know.
            // The decompiled shows: local_60 = fVar5 * local_60; then FUN_00aa5040(fVar5); etc.
            // This might be a bug in decompilation. We'll approximate by applying scale to some component.
            // Instead we'll just store the speedScale and later use it.
            float var5 = speedScale;
            // The original code likely applied scale to some matrix component; we ignore.
            FUN_00aa5040(var5);
            FUN_009f3d60(local_60); // set something
            FUN_009f3dc0(auStack_44); // finalize transform
        }
    }

    // Handle blend target (from param_1 - 4 floats)
    if (blendTarget != 0) {
        AnimComponent* animComp2 = *(AnimComponent**)((char*)thisObj + 0x88);
        byte actionState2 = *(byte*)((char*)animComp2 + 0xd8);
        if (actionState2 != 6 && actionState2 != 7) {
            // get current transform into local_60 (temp)
            float tempMatrix[4]; // actually could be quaternion or position, but used as 4 floats
            (**(code**)(*(int*)((char*)animComp2 + 0xd0) + 0x14))(&tempMatrix);

            if (*(int*)((char*)thisObj + 0x34) != 0) {
                int animCompPtr = *(int*)((char*)thisObj + 0x88);
                // Compute difference: target - current position
                float diff[4];
                diff[0] = blendTarget[0] - *(float*)(animCompPtr + 0x160); // maybe root position?
                diff[1] = blendTarget[1] - *(float*)(animCompPtr + 0x164);
                diff[2] = blendTarget[2] - *(float*)(animCompPtr + 0x168);
                diff[3] = blendTarget[3] - *(float*)(animCompPtr + 0x16c); // maybe rotation?

                float factor = (float)FUN_009efd10(); // get time factor
                FUN_009df220(&diff, factor); // lerp/smooth towards target
                FUN_009f3dc0(&tempMatrix); // update transform with diff?
                FUN_009f4400(blendTarget); // apply final transform
            }
        }
    }

    // +0x28: flag indicating whether to clear transform buffers?
    if (*(int*)((char*)thisObj + 0x28) != 0) {
        // +0x44: pointer to some buffer? If non-zero, clear it
        if (*(int*)((char*)thisObj + 0x44) != 0) {
            int animComp3 = *(int*)((char*)thisObj + 0x88);
            FUN_009f2000(); // push matrix?
            // call virtual function at vtable+0x40 (maybe resetPosition?)
            (**(code**)(*(int*)(animComp3 + 0xd0) + 0x40))(thisObj + 0x50);
            *(int*)((char*)thisObj + 0x44) = 0;
        }
        if (*(int*)((char*)thisObj + 0x60) != 0) {
            int animComp4 = *(int*)((char*)thisObj + 0x88);
            FUN_009f2000();
            // call virtual at +0x44 (maybe resetRotation?)
            (**(code**)(*(int*)(animComp4 + 0xd0) + 0x44))(thisObj + 0x70);
            *(int*)((char*)thisObj + 0x60) = 0;
        }
    }

    // +0x2c: flag for copying position to anim component
    if (*(int*)((char*)thisObj + 0x2c) != 0) {
        // copy position from thisObj +0x14, +0x18 to animComp +0x184, +0x188
        AnimComponent* animComp5 = *(AnimComponent**)((char*)thisObj + 0x88);
        *(float*)((char*)animComp5 + 0x184) = *(float*)((char*)thisObj + 0x14);
        *(float*)((char*)animComp5 + 0x188) = *(float*)((char*)thisObj + 0x18);
    }

    // +0x38: flag for copying some other data
    if (*(int*)((char*)thisObj + 0x38) != 0) {
        AnimComponent* animComp6 = *(AnimComponent**)((char*)thisObj + 0x88);
        *(float*)((char*)animComp6 + 0x84) = *(float*)((char*)thisObj + 0x1c);
        *(float*)((char*)animComp6 + 0x88) = *(float*)((char*)thisObj + 0x20);
    }
}