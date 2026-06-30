// FUNC_NAME: Sentient::processImpactForce
void __thiscall Sentient::processImpactForce(ImpactHitData* hitData, Sentient* this) {
    if (this->stateFlag != 1) { // offset [8] - some state/flag
        Node* headA = this->linkedListA; // *param_2 (offset [0])
        Node* lastA = headA;
        for (Node* node = *(Node**)(headA + 0xc); node != nullptr; node = *(Node**)(node + 0xc)) {
            lastA = node; // traverse to last
        }

        Node* headB = this->linkedListB; // param_2[1]
        Node* lastB = headB;
        for (Node* node = *(Node**)(headB + 0xc); node != nullptr; node = *(Node**)(node + 0xc)) {
            lastB = node;
        }

        // Check some flags via double indirection (index into table at +0x80)
        if ((*(byte*)(lastA + 0x10) + 0x80 + lastA) != 1) return; // condition guard
        if ((*(byte*)(lastB + 0x10) + 0x80 + lastB) != 1) return;

        // Determine which list to use for last node
        Node* lastNode;
        if (*(byte*)(lastA + 0x10) + lastA == this->somePtr) { // param_2[3]
            lastNode = lastB;
        } else {
            lastNode = lastA;
        }

        char activeState = *(char*)(*(byte*)(lastNode + 0x10) + 0xd8 + lastNode); // byte at some table

        float clampMinX = hitData->minBoundX;    // +0x10
        float clampMaxX = hitData->maxBoundX;    // +0x14
        float clampMinY = hitData->minBoundY;    // +0x18 (used for Z in code but naming)
        // Actually local_18 is used as a min for Z, but offset +0x18 is used for clamp as well
        // Let's keep original param names

        if (activeState == 7 || activeState == 6) {
            PhysicsComponent* phy = *(PhysicsComponent**)(hitData + 0x34); // +0x34
            float velX = phy->velocity[0];   // +0x1a0
            float velY = phy->velocity[1];   // +0x1a4
            float velZ = phy->velocity[2];   // +0x1a8
            float extra = *(undefined4*)(phy + 0x1ac); // w or something

            if (hitData->useMinClamp && velY < hitData->maxClampY) { // +0x28 and +0x14
                if (velX < hitData->minClampX) velX = hitData->minClampX; // +0x10
                if (velX < hitData->minClampZ) velZ = hitData->minClampZ; // +0x18
                FUN_004b5cf0(&velX); // normalize/clamp
                velY = hitData->maxClampY;
            }

            if (hitData->flagTwo || hitData->flagThree) { // +0x2c, +0x30
                Vector3* vec = this->someVector; // param_2[4]
                float dotVal = (float)((uint)(vec->x * 0.0 + vec->y * 0.0 + vec->z * 0.0) & DAT_00e44680);
                float speed;
                if (hitData->flagTwo && dotVal > DAT_00e2cd54) {
                    speed = hitData->speedOne; // +0x1c
                } else if (hitData->flagThree && dotVal > DAT_00e2cd54) {
                    speed = hitData->speedTwo; // +0x20
                } else {
                    return; // neither condition met
                }

                float div = speed / *(float*)(this->somePtr + 0x84); // param_2[3] + 0x84
                float sqrtResult = (float)FUN_00414a80(div); // perhaps sqrt(div)?
                byte index = *(byte*)(this->indexPtr + 0xc); // param_2[6] + 0xc
                float multiplier = *(float*)(&DAT_00d999b8 + index * 4);
                float finalValue = sqrtResult * multiplier;
                FUN_00aaa340(&finalValue); // apply effect
            }
        } else {
            // Other active states (not 7 or 6)
            void* effectData = *(void**)(hitData + 0x24); // +0x24
            if (effectData != nullptr) {
                int type = FUN_00541470(*(undefined4*)(lastNode + 0x1c));
                if (type == 8) {
                    FUN_009f66e0(this->effectParam1,          // param_2[9]
                                 *(undefined4*)(hitData + 0x34), // +0x34 (physics)
                                 0,                              // shift
                                 *(undefined4*)(this->effectParam2 + 4), // param_2[0xb] + 4
                                 DAT_00e2b1a4 / *(float*)(hitData + 0x8), // division
                                 1.0f);                          // constant
                } else if (type == 5) {
                    FUN_009f66e0(this->effectParam1,
                                 *(undefined4*)(hitData + 0x34),
                                 0,
                                 *(undefined4*)(this->effectParam2 + 4),
                                 DAT_00e2b1a4 / *(float*)(hitData + 0xc),
                                 1.0f);
                }
            }
        }
    }
    return;
}