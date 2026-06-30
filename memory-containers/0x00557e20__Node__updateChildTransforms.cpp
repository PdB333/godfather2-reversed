//FUNC_NAME: Node::updateChildTransforms
void __thiscall Node::updateChildTransforms(void) {
    uint combinedMask;
    int childIndex;
    int childPtr;
    float tempFloat;
    // Stack variables for matrix operations
    float matrixLocal[4][4]; // Actually 4x4? The stack has many floats, likely 4x4 matrix
    float matrixTemp[4][4];
    float deltaMatrix[4][4];
    // The decompiled shows many undefined4 and float, but we can treat as 4x4 matrix
    // Actually the code uses local_50 as a 16-byte? But then copies many values. Likely a 4x4 matrix (16 floats)
    // We'll use a struct or array.

    // Check dirty flag at +0x48
    if (*(char *)(this + 0x48) != '\0') {
        *(uint32_t *)(this + 0x3c) = 0;
    }
    combinedMask = *(uint32_t *)(this + 0x38) | *(uint32_t *)(this + 0x3c);
    *(uint32_t *)(this + 0x3c) = ~combinedMask | *(uint32_t *)(this + 0x3c);
    if ((*(char *)(this + 0x48) != '\0') || (~combinedMask != 0)) {
        *(char *)(this + 0x48) = 0;
        // Get child array descriptor: pointer to array and count
        childPtr = **(int **)(this + 0x30); // base pointer
        int count = (*(int **)(this + 0x30))[1]; // number of children
        int endPtr = childPtr + count * 0x70;
        while (childPtr < endPtr) {
            if ((combinedMask & 1) == 0) {
                // Initialize matrix to identity? DAT_00e2b1a4 is likely 0.0f or 1.0f
                // We'll assume it's 0.0f for position components, 1.0f for scale? Actually typical identity: diagonal 1, others 0.
                // The code sets local_44, local_34, local_24 to 0, local_14 to DAT_00e2b1a4 (maybe 1.0f for w?)
                // Then calls a virtual function to get child's local transform
                // The virtual function at (*(int *)(this+0x34))->vtable[0x8c] takes (matrixOut, childData+0x48, 1)
                // childData+0x48 is likely the local transform data inside the child structure (0x70 bytes)
                // We'll assume childData is a struct of size 0x70 with local transform at offset 0x48
                // The virtual function fills matrixLocal with the child's local transform
                (*(void (__thiscall **)(void *, float (*)[4], void *, int))(*(int *)(this + 0x34) + 0x8c))(
                    *(void **)(this + 0x34), matrixLocal, (void *)(childPtr + 0x48), 1);
                // Then set some stack variables to zero and call FUN_00417560 (likely identity or reset)
                // The code then copies matrixLocal from uStack_90 etc. Actually it's a bit messy.
                // We'll simplify: after the virtual call, we have matrixLocal.
                // Then call FUN_00417560() which might compute something.
                // Then copy matrixLocal to matrixTemp? Actually the code does:
                // local_50 = uStack_90; ... etc. That's copying the matrix from the virtual call output to local_50.
                // Then calls FUN_004b59d0(&local_50, auStack_d0) which might multiply or copy.
                // Then calls FUN_00aa1fc0(childPtr) - maybe update child's world transform?
                // Then subtracts parent position from the matrix's translation components.
                // Then calls FUN_00aa57b0() and FUN_00a6be20(auStack_d0) to apply.
                // We'll represent as matrix operations.
                // For simplicity, we'll assume matrixLocal is a 4x4 matrix.
                // The parent's position is at this+0x20,0x24,0x28,0x2c (likely x,y,z,w? w might be 1)
                // The code subtracts parent position from the matrix's translation (fStack_a0, fStack_9c, fStack_98, fStack_94)
                // So we compute delta = childWorld - parentWorld? Actually it's subtracting parent from child's world position.
                // Then applies that delta to the child.
                // We'll just replicate the logic with meaningful names.
                float parentPos[4];
                parentPos[0] = *(float *)(this + 0x20);
                parentPos[1] = *(float *)(this + 0x24);
                parentPos[2] = *(float *)(this + 0x28);
                parentPos[3] = *(float *)(this + 0x2c);
                // The matrixLocal is the child's local transform? Actually the virtual function gets child's local transform.
                // Then after some operations, we compute delta.
                // We'll call the helper functions as they are.
                FUN_00417560(); // unknown, but likely resets something
                // Copy matrixLocal to matrixTemp (the code does a lot of copying)
                // Then call FUN_004b59d0(&matrixLocal, &matrixTemp); // maybe multiply?
                FUN_004b59d0(&matrixLocal, &matrixTemp);
                // Then call FUN_00aa1fc0(childPtr); // update child?
                FUN_00aa1fc0(childPtr);
                // Subtract parent position from matrixTemp's translation
                matrixTemp[0][3] -= parentPos[0]; // assuming translation is in column 3
                matrixTemp[1][3] -= parentPos[1];
                matrixTemp[2][3] -= parentPos[2];
                matrixTemp[3][3] -= parentPos[3];
                // Then call FUN_00aa57b0() and FUN_00a6be20(&matrixTemp)
                FUN_00aa57b0();
                FUN_00a6be20(&matrixTemp);
            }
            combinedMask >>= 1;
            childPtr += 0x70;
        }
    }
}