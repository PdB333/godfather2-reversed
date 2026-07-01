// FUNC_NAME: PlayerAnimBlend::updateBlend
void __thiscall PlayerAnimBlend::updateBlend(int *this, float deltaTime) {
    float fVar1;
    float fVar2;
    int iVar3;
    int *piVar4;
    // Stack space for matrix transforms (multiple 4x4s)
    // local_2f8, local_2f4, local_2b0, local_2b8, etc.
    // We'll use meaningful names for the transforms.
    struct Transform { float m[16]; }; // Assume 4x4 matrix
    Transform blendResult; // local_278
    Transform localTransform; // local_2b0
    Transform otherLocalTransform; // local_2f4
    Transform sourceTransform; // local_198
    Transform targetTransform; // local_158
    Transform tempTransform1; // local_98
    Transform tempTransform2; // local_58
    Transform lerpTransform; // local_1f8
    Transform quat1; // local_118
    Transform quat2; // local_f8
    Transform finalMatrix; // local_d8
    // ... more temporaries

    // Check if blend is active and valid
    if ((((char)this[0x40a] != '\0') && (this[0x3ff] != 0)) && (this[0x3ff] != 0x48)) {
        // Initialize some matrices to zero (identity?) from global constant
        // _DAT_00d5780c is likely an identity matrix
        // We'll assume it's an identity matrix constant.
        blendResult = *(Transform*)&_DAT_00d5780c; // local_278
        // ... many more assignments to local matrices (actually they are separate variables, but we'll just note)

        // First branch: when blend timer is positive and indices match
        if ((this[0x404] == this[0x403]) && (0.0f < (float)this[0x407])) {
            // Determine blend type
            if (((char)this[0x406] == '\x01') && (*(char*)((int)this + 0x102a) != '\x01')) {
                // Type 1, sub-type not 1
                if (*(char*)((int)this + 0x102a) == '\x02') {
                    // Sub-type 2: get target object and call its getTransform
                    if (this[0x3ff] == 0) {
                        piVar4 = (int *)0x0;
                    } else {
                        piVar4 = (int *)(this[0x3ff] - 0x48); // Derive base pointer
                    }
                    (**(code **)(*piVar4 + 0x38))(&otherLocalTransform); // Get transform
                    FUN_00470040(this + 0x40b, DAT_00d5d70c, &DAT_00d71a80); // Set some parameter
                }
            } else {
                // Type 2: must have sub-type 1
                if ((char)this[0x406] != '\x02') {
                    return;
                }
                if (*(char*)((int)this + 0x102a) != '\x01') {
                    return;
                }
            }

            // Get this object's transform
            (**(code **)(*this + 0x38))(&localTransform);

            // Get other object's transform
            if (this[0x3ff] == 0) {
                piVar4 = (int *)0x0;
            } else {
                piVar4 = (int *)(this[0x3ff] - 0x48);
            }
            (**(code **)(*piVar4 + 0x38))(&otherLocalTransform);

            // Copy transforms: source from otherLocal's transform? (FUN_0044b4e0 likely copies matrix)
            FUN_0044b4e0(&sourceTransform, &otherLocalTransform); // local_198 from local_2f8? Actually order: first param is dest, second is src? We'll assume.
            FUN_0044b4e0(&targetTransform, &localTransform); // local_158 from local_2f8? Wait, the code: FUN_0044b4e0(auStack_198, auStack_2f8) and FUN_0044b4e0(auStack_158, auStack_2b8). So source from auStack_2f8 (which is from otherObject) and target from auStack_2b8 (this object's transform). So source = other, target = this.

            // Compute blended transform via FUN_007fcf30
            if (this[0x3ff] == 0) {
                iVar3 = 0;
            } else {
                iVar3 = this[0x3ff] - 0x48;
            }
            FUN_007fcf30(&blendResult, iVar3, &targetTransform, &tempTransform1, this + 0x402, this, &sourceTransform, &tempTransform2, this + 0x401);
            // parameters: blendResult, otherBase, target, temp1, index1, this, source, temp2, index2

            // If sub-type 2, call setTransform on other object
            if (*(char*)((int)this + 0x102a) == '\x02') {
                if (this[0x3ff] == 0) {
                    piVar4 = (int *)0x0;
                } else {
                    piVar4 = (int *)(this[0x3ff] - 0x48);
                }
                (**(code **)(*piVar4 + 0x2c))(&otherLocalTransform); // setTransform
            }

            // Depending on blend timer threshold
            if ((float)this[0x407] <= _DAT_00d577a0) {
                // Low timer: just set the blended result
                FUN_00449da0(&blendResult, &blendResult); // Likely apply to something
            } else {
                // High timer: interpolate with a factor
                if (*(char*)((int)this + 0x102a) == '\x02') {
                    FUN_00470040(this + 0x40b, this[0x409], &DAT_00d71a80);
                }
                fVar1 = (float)this[0x408];
                fVar2 = (float)this[0x407];
                // Convert source and target to quaternions or something
                FUN_0056dbe0(&sourceTransform, &quat1);
                FUN_0056dbe0(&blendResult, &quat2);
                // Lerp with factor (fVar1 - fVar2) / fVar1
                FUN_0056db60((fVar1 - fVar2) / fVar1, &quat1, &quat2, &lerpTransform);
                FUN_004177a0(&lerpTransform, &lerpTransform); // Normalize
                FUN_0056dc20(&lerpTransform, &finalMatrix); // Convert back to matrix
                FUN_00449da0(&blendResult, &finalMatrix); // Apply final matrix
                // Decrease timer
                fVar1 = (float)this[0x407];
                this[0x407] = (int)(fVar1 - deltaTime);
                if (fVar1 - deltaTime <= 0.0f) {
                    this[0x407] = 0;
                    if (((this[0x3ff] != 0) && (this[0x3ff] != 0x48)) &&
                       ((iVar3 = this[0x3ff], iVar3 != 0 && (iVar3 != 0x48)))) {
                        *(undefined4 *)(iVar3 + 0xfd4) = 0; // Signal end of blend
                        (**(code **)(*this + 0x2c))(&blendResult); // Apply final transform
                        return;
                    }
                }
            }
            // Apply blend result to this object
            (**(code **)(*this + 0x2c))(&blendResult);
            return;
        }

        // Second branch: when the condition above fails, but there is a pending transition
        if ((*(char*)((int)this + 0x1029) != '\0') &&
           ((((this[0x3ff] == 0) || (this[0x3ff] == 0x48)) ||
            (iVar3 = FUN_0043b870(DAT_01130950), iVar3 == 0)) ||
           ((*(uint *)(iVar3 + 0x4c) >> 1 & 1) == 0))) {
            // Get transforms
            (**(code **)(*this + 0x38))(&localTransform);
            if (this[0x3ff] == 0) {
                piVar4 = (int *)0x0;
            } else {
                piVar4 = (int *)(this[0x3ff] - 0x48);
            }
            (**(code **)(*piVar4 + 0x38))(&otherLocalTransform);

            // Copy transforms (swapped order compared to previous)
            FUN_0044b4e0(&sourceTransform, &otherLocalTransform); // from otherLocal
            FUN_0044b4e0(&targetTransform, &localTransform); // from this local

            // Compute blend with different indices
            if (this[0x3ff] == 0) {
                iVar3 = 0;
            } else {
                iVar3 = this[0x3ff] - 0x48;
            }
            FUN_007fcf30(&blendResult, iVar3, &sourceTransform, &tempTransform1, this + 0x401, this, &targetTransform, &tempTransform2, this + 0x402);
            // parameters: blendResult, otherBase, source, temp1, index1, this, target, temp2, index2

            FUN_00449da0(&blendResult, &blendResult);
            (**(code **)(*this + 0x2c))(&blendResult);
        }
    }
    return;
}