// FUNC_NAME: PhysicsConstraint::updateConstraint
void __thiscall PhysicsConstraint::updateConstraint(PhysicsConstraint *this, float *targetNode, float *targetPosition, float *targetRotation, bool isSecondary, int *extraData) {
    float *linkedNode;
    float fVar1;
    double dVar2;
    float fVar3, fVar4, fVar5, fVar6, fVar7;
    float *local_40;
    float local_38, local_34, local_30, local_2c, local_28, local_24, local_20, fStack_1c, fStack_18, fStack_14;
    
    // Clear the previous linked node pointer at offset +0x10 (byte) and remove from list if needed
    linkedNode = (float *)(this + 0x11); // offset +0x11 (float)
    this->m_previousLinkedNode = 0; // offset +0x10 (byte)
    
    if (*linkedNode != 0.0f) {
        // Remove this node from linked list
        removeFromLinkedList((float *)linkedNode);
        *linkedNode = 0.0f;
    }
    
    // Similar for another node at offset +0x46
    if (this->m_secondaryNode != 0.0f) {
        removeFromLinkedList((float *)(this + 0x46));
        this->m_secondaryNode = 0.0f;
    }
    
    // Save the primary linked node and its next pointer
    local_2c = this->m_primaryNode; // offset +0x1f
    local_28 = 0.0f;
    if (local_2c != 0.0f) {
        local_28 = *(float *)((int)local_2c + 4);
        *(float **)((int)local_2c + 4) = &local_2c; // point back to itself? this is tricky
    }
    
    // Save tertiary linked node and its next pointer
    local_24 = this->m_tertiaryNode; // offset +0x21
    linkedNode = (float *)(this + 0x22); // offset +0x22
    local_38 = *linkedNode;
    local_34 = 0.0f;
    if (local_38 != 0.0f) {
        local_34 = *(float *)((int)local_38 + 4);
        *(float **)((int)local_38 + 4) = &local_38;
    }
    
    local_30 = this->m_quaternaryNode; // offset +0x24
    
    fVar7 = *targetNode;
    if (fVar7 == 0.0f) {
        local_40 = 0;
    } else {
        local_40 = (float *)targetNode[2]; // offset +2 from targetNode
    }
    
    if (!isSecondary) {
        // Primary branch: update position and orientation constraints from target
        enterCriticalSection(); // FUN_005f5ce0
        if ((extraData != 0) && (extraData[0] != 0) && (extraData[2] != 0)) {
            processExtraData(extraData); // FUN_005f7ba0
        }
        leaveCriticalSection();
        
        if ((float *)(this + 0x22) != targetNode) {
            fVar7 = *targetNode;
            if (*(float *)(this + 0x22) != fVar7) {
                if (*(float *)(this + 0x22) != 0.0f) {
                    removeFromLinkedList((float *)(this + 0x22));
                }
                *(float *)(this + 0x22) = fVar7;
                if (fVar7 != 0.0f) {
                    this->m_tertiaryNodeNext = *(float *)((int)fVar7 + 4); // offset +0x23
                    *(float **)((int)fVar7 + 4) = (float *)(this + 0x22);
                }
            }
        }
        this->m_quaternaryNode = targetNode[2]; // offset +0x24
        this->m_position[0] = targetPosition[0]; // offset +0x18
        this->m_position[1] = targetPosition[1]; // offset +0x19
        this->m_position[2] = targetPosition[2]; // offset +0x1a
    } else {
        // Secondary branch: use targetNode as new linked node for offset +0x1c
        linkedNode = (float *)(this + 0x1c);
        if ((linkedNode != targetNode) && (*linkedNode != fVar7)) {
            if (*linkedNode != 0.0f) {
                removeFromLinkedList(linkedNode);
            }
            *linkedNode = fVar7;
            if (fVar7 != 0.0f) {
                this->m_secondaryNext = *(float *)((int)fVar7 + 4); // offset +0x1d
                *(float **)((int)fVar7 + 4) = linkedNode;
            }
        }
        this->m_secondaryNode = targetNode[2]; // offset +0x1e
        if ((float *)(this + 0x1f) != linkedNode) {
            fVar7 = *linkedNode;
            if (this->m_primaryNode != fVar7) {
                if (this->m_primaryNode != 0.0f) {
                    removeFromLinkedList((float *)(this + 0x1f));
                }
                this->m_primaryNode = fVar7;
                if (fVar7 != 0.0f) {
                    this->m_primaryNext = *(float *)((int)fVar7 + 4); // offset +0x20
                    *(float **)((int)fVar7 + 4) = (float *)(this + 0x1f);
                }
            }
        }
        this->m_tertiaryNode = this->m_secondaryNode; // offset +0x21 = offset +0x1e
        this->m_position[0] = local_40[0];
        this->m_position[1] = local_40[1];
        this->m_position[2] = local_40[2];
        targetPosition[0] = this->m_position[0];
        targetPosition[1] = this->m_position[1];
        targetPosition[2] = this->m_position[2];
        updateDerived(this, targetNode, (float *)(this + 0x22), 0);
    }
    
    updateInternalState(); // FUN_00414aa0
    this->m_someFloat0 = 0.0f; // offset +0x38
    this->m_someFloat1 = 0.0f; // offset +0x30
    this->m_someFloat2 = 0.0f; // offset +0x44
    this->m_someFloat3 = 0.0f; // offset +0x43
    
    if ((*(float *)(this + 0x22) == 0.0f) || ((float *)this->m_quaternaryNode == 0)) {
        this->m_flags |= 1; // offset +0x2d, bit0 set
        this->m_angleX = 0.0f; // offset +0x3f
        this->m_angleY = 0.0f; // offset +0x3e
        this->m_angleZ = 0.0f; // offset +0x3d
        this->m_angleTargetX = 0.0f; // offset +0x42
        this->m_angleTargetY = 0.0f; // offset +0x41
        this->m_angleTargetZ = 0.0f; // offset +0x40
        goto LABEL_CLEANUP;
    }
    
    // Compute direction vector from this position to target
    float *targetPosPtr;
    if (!isSecondary) {
        targetPosPtr = local_40;
    } else {
        targetPosPtr = (float *)this->m_quaternaryNode;
    }
    float dx = targetPosPtr[0] - this->m_position[0];
    float dy = targetPosPtr[1] - this->m_position[1];
    float dz = targetPosPtr[2] - this->m_position[2];
    float dw = fStack_14 - this->m_position[3]; // note: m_position[3] (w component) exists? maybe quaternion
    float distSq = dx*dx + dy*dy + dz*dz;
    float distance = 0.0f;
    float invDist = 0.0f;
    if (DAT_00e2cbe0 < distSq) { // small threshold
        distance = sqrtf(distSq);
        invDist = DAT_00e2b1a4 / distance; // probably 1.0f / distance if DAT is 1.0
    }
    dx *= invDist;
    dy *= invDist;
    dz *= invDist;
    
    dVar2 = (double)dx;
    performMath(); // FUN_00b9a9fa? maybe sin/cos
    float angleX = (float)dVar2;
    this->m_angleX = angleX;
    
    dVar2 = (double)dy;
    performMath();
    float angleTargetX = DAT_00e44564 - (float)dVar2; // angle offset
    this->m_angleTargetX = angleTargetX;
    
    if ((targetRotation == 0) || (isSecondary)) {
        this->m_angleY = angleX;
        this->m_angleZ = angleX;
        this->m_angleTargetY = angleTargetX;
        this->m_angleTargetZ = angleTargetX;
        if (targetRotation != 0) {
            targetRotation[0] = dx;
            targetRotation[1] = dy;
            targetRotation[2] = dz;
        }
        goto LABEL_CLEANUP;
    }
    
    // Apply angle wrapping from previous target orientation
    dVar2 = (double)*targetRotation;
    performMath();
    float prevAngleY = (float)dVar2;
    float diffAngleY = angleX - prevAngleY;
    this->m_angleY = prevAngleY;
    
    // Normalize diffAngleY to [-PI, PI]
    if (diffAngleY > DAT_00e2afac) {
        diffAngleY -= DAT_00e2a848;
    } else if (diffAngleY < DAT_00e44588) {
        diffAngleY += DAT_00e2a848;
    }
    
    float newAngleZ = prevAngleY - diffAngleY;
    this->m_angleZ = newAngleZ;
    if (newAngleZ > DAT_00e2afac) {
        newAngleZ -= DAT_00e2a848;
        this->m_angleZ = newAngleZ;
    } else if (newAngleZ < DAT_00e44588) {
        newAngleZ += DAT_00e2a848;
        this->m_angleZ = newAngleZ;
    }
    
    dVar2 = (double)targetRotation[1];
    performMath();
    float prevAngleTargetY = DAT_00e44564 - (float)dVar2;
    float diffAngleTargetY = this->m_angleTargetX - prevAngleTargetY;
    this->m_angleTargetY = prevAngleTargetY;
    
    if (diffAngleTargetY > DAT_00e2afac) {
        diffAngleTargetY -= DAT_00e2a848;
    } else if (diffAngleTargetY < DAT_00e44588) {
        diffAngleTargetY += DAT_00e2a848;
    }
    
    float newAngleTargetZ = prevAngleTargetY - diffAngleTargetY;
    this->m_angleTargetZ = newAngleTargetZ;
    if (newAngleTargetZ > DAT_00e2afac) {
        newAngleTargetZ -= DAT_00e2a848;
        this->m_angleTargetZ = newAngleTargetZ;
    } else if (newAngleTargetZ < DAT_00e44588) {
        newAngleTargetZ += DAT_00e2a848;
        this->m_angleTargetZ = newAngleTargetZ;
    }
    
    // Compute inertia factor
    float inertia = distance * DAT_00e2cd54; // some coefficient
    this->m_inertia = inertia; // offset +0x3b
    float invInertia = DAT_00e44968;
    if (inertia > 0.0f) {
        invInertia = DAT_00e2b1a4 / inertia;
    }
    this->m_invInertia = invInertia; // offset +0x3c
    
    // Clear torque
    this->m_torque[0] = 0.0f; // offset +0x34
    this->m_torque[1] = 0.0f; // offset +0x35
    this->m_torque[2] = 0.0f; // offset +0x36
    this->m_someFloat0 = 2.8026e-45f; // tiny number
    
LABEL_CLEANUP:
    enterCriticalSection();
    if (this->m_callback != 0) { // offset +0x29
        ((void (*)(PhysicsConstraint*, float*, float*, float*, float*))this->m_callback)(this, &local_2c, &local_38, (float *)(this + 0x1f), (float *)(this + 0x22));
    }
    
    // Restore linked list pointers from saved nodes
    if (local_38 != 0.0f) {
        float *pfVar1 = *(float **)((int)local_38 + 4);
        if (pfVar1 == &local_38) {
            *(float *)((int)local_38 + 4) = local_34;
        } else {
            while (*(float *)(pfVar1 + 1) != &local_38) {
                pfVar1 = (float *)pfVar1[1];
            }
            pfVar1[1] = local_34;
        }
    }
    if (local_2c != 0.0f) {
        float *pfVar1 = *(float **)((int)local_2c + 4);
        if (pfVar1 == &local_2c) {
            *(float *)((int)local_2c + 4) = local_28;
        } else {
            while (*(float *)(pfVar1 + 1) != &local_2c) {
                pfVar1 = (float *)pfVar1[1];
            }
            pfVar1[1] = local_28;
        }
    }
}