// FUNC_NAME: Presentation::updateAnimationList
uint __thiscall Presentation::updateAnimationList(float deltaTime) {
    uint uVar1;
    AnimationNode* pNode; // esi - current node, starts with this
    int iVar2;
    float fVar3;
    float fVar4;

    pNode = this;
    do {
        /* Set direction flag based on deltaTime sign */
        if (0.0 <= deltaTime) {
            pNode->flags = pNode->flags & 0xfffbffff; // clear bit 18 (forward)
        } else {
            pNode->flags = pNode->flags | 0x40000;      // set bit 18 (backward)
        }

        fVar3 = pNode->speedScale * g_fTimeScale;       // global time scale
        fVar4 = deltaTime;

        /* Check if this is a child node (not root) and conditions for callback trigger */
        if (((pNode != this) && (*(char*)(&pNode->flags + 0x20) == '\0')) && // +0x30 char == 0
            ((pNode->flags & 3) != 0) &&                                     // bits 0-1 non-zero
            ((pNode->flags >> 0x1c & 1) != 0)) {                              // bit 28 set (callback pending)
            pNode->flags = pNode->flags & 0xefffffff;                        // clear bit 28
            FUN_00572580();                                                   // trigger animation callback
        }

        uVar1 = FUN_00578990(fVar3 * fVar4);                                 // advance animation time

        if (*(int*)(pNode + 0x110) != 0) {                                   // +0x110: pointer to secondary animation?
            *(float*)(pNode + 0x114) = *(float*)(pNode + 0x114) + deltaTime; // +0x114: secondary time accumulator
        }

        *(float*)(pNode + 0x78) = *(float*)(pNode + 0x78) + deltaTime;       // +0x78: primary time accumulator

        iVar2 = *(int*)(pNode + 0x124);                                       // +0x124: next node pointer
        pNode = iVar2;
    } while (pNode != 0);

    return uVar1 & 0xffffff00; // return status (mask out low byte)
}