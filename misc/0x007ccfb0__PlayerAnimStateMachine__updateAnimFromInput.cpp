// FUNC_NAME: PlayerAnimStateMachine::updateAnimFromInput

void __thiscall PlayerAnimStateMachine::updateAnimFromInput(PlayerAnimStateMachine *this, AnimStateInput *input, AnimStateInfo *info, bool isAlternate)
{
    int secondaryAnimPtr;
    int secondaryBase;
    int animData;
    int local_8;
    int local_4;
    int mainAnimObj;

    mainAnimObj = 0;
    // m_pLinkedAnimObject (offset 0x1b4) may be null
    if (this->m_pLinkedAnimObject == 0) {
        secondaryBase = 0;
    } else {
        // The linked animation object is embedded at offset 0x48 in its container
        secondaryBase = this->m_pLinkedAnimObject - 0x48;
    }
    // m_pAnimDataTable (offset 0x1bc) from secondaryBase's field at +0x1f3c
    animData = *(int *)(secondaryBase + 0x1f3c);
    this->m_pCurrentAnimData = animData;
    if (animData == 0) {
        return;
    }
    local_4 = 0;
    local_8 = 0;

    if (!isAlternate) {
        // Normal path: set direct flag on primary animation object
        *(char *)(this->m_pPrimaryAnimObj + 0xa20) = 1;
        // Lookup animation data using input->field_1c and a key at this+0x1d6
        int *ptr = (int *)FUN_007cae10(*(int *)(input + 0x1c), (short *)(this + 0x1d6));
        if (ptr != (int *)0) {
            if (*ptr == -1) {
                mainAnimObj = **(int **)(*(int *)(this->m_pCurrentAnimData + 0x30));
            } else {
                mainAnimObj = *(int *)(*(int *)(*(int *)(this->m_pCurrentAnimData + 0x30) + *ptr * 4);
            }
            mainAnimObj = mainAnimObj + 0x10;
            // Another lookup for blend data using input->field_14
            int blendPtr = FUN_007cae60(*(int *)(input + 0x14), (short *)(this + 0x1d6));
            if (blendPtr != 0) {
                local_4 = *(int *)(blendPtr + 4);
                local_8 = *(int *)(blendPtr + 8);
            }
            goto LAB_007cd0e1;
        }
        // Fallback: use input->field_14 as key
        code key = *(int *)(input + 0x14);
    } else {
        // Alternate path: clear the direct flag
        *(char *)(this->m_pPrimaryAnimObj + 0xa20) = 0;
        // Call some function that returns a byte (maybe an override)
        char result = FUN_007cab20(*(int *)(input + 0xc), this->m_pPrimaryAnimObj, secondaryBase);
        *(char *)(this + 0x20c) = result;
        // Lookup using input->field_14 and key at this+0x1d6
        int *ptr = (int *)FUN_007cae10(*(int *)(input + 0x14), this + 0x1d6);
        if (ptr != (int *)0) {
            if (*ptr == -1) {
                mainAnimObj = **(int **)(*(int *)(this->m_pCurrentAnimData + 0x30));
            } else {
                mainAnimObj = *(int *)(*(int *)(*(int *)(this->m_pCurrentAnimData + 0x30) + *ptr * 4);
            }
            local_4 = ptr[1];
            local_8 = ptr[2];
            mainAnimObj = mainAnimObj + 0x10;
            goto LAB_007cd0e1;
        }
        // Fallback: use input->field_1c as key
        code key = *(int *)(input + 0x1c);
    }
    // Try one more lookup if the first attempt failed
    FUN_007cae10(key, this + 0x1d6);

LAB_007cd0e1:
    // Set the main animation
    FUN_007cbf50(mainAnimObj);
    // Set blend parameters
    FUN_007cbfa0(local_4, local_8);
    // Set some animation flag based on input->field_24 >> 7, masked with 0xffffff01
    FUN_007cb110((*(uint *)(input + 0x24) >> 7) & 0xffffff01);

    // Determine a boolean for the second animation call
    bool secondFlag;
    if ((!isAlternate) || ((*(uint *)(info + 8) >> 7 & 1) == 0)) {
        secondFlag = 0;
    } else {
        secondFlag = 1;
    }
    // Apply animation state to primary animation object
    FUN_007cc030(this->m_pPrimaryAnimObj, *(uint *)(info + 8) & 7,
                 *(uint *)(info + 8) & 0x78, secondFlag);

    // Determine boolean for the third animation call (note inversion of isAlternate)
    bool thirdFlag;
    if ((isAlternate) && ((*(uint *)(info + 8) >> 7 & 1) != 0)) {
        thirdFlag = 1;
    } else {
        thirdFlag = 0;
    }
    // Apply animation state to the secondary base (if valid)
    if (this->m_pLinkedAnimObject == 0) {
        secondaryBase = 0;
    } else {
        secondaryBase = this->m_pLinkedAnimObject - 0x48;
    }
    FUN_007cc030(secondaryBase, *(uint *)(info + 0xc) & 7,
                 *(uint *)(info + 0xc) & 0x78, thirdFlag);

    return;
}