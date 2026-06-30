// FUNC_NAME: ActionDelayManager::cancelAction

void __thiscall ActionDelayManager::cancelAction(int *actionId)
{
    float duration;
    uint slotMask;
    undefined4 *node;
    int index;
    int *slotValue;
    undefined **tempStack;
    int tempInt;
    int local_10;
    undefined4 local_c;
    undefined ***local_8;
    undefined1 local_4;

    // Call base cleanup (likely releases a resource)
    FUN_0046c6a0(actionId);

    if (this->remainingTime <= DAT_01205224) {
        index = 0;
        do {
            slotMask = 1 << (index & 0x1f);
            slotValue = (int *)0x0;
            switch(slotMask) {
            case 1:
                slotValue = &this->slotIds[0]; // +0x14
                break;
            case 2:
                slotValue = &this->slotIds[1]; // +0x1c
                break;
            case 4:
                slotValue = &this->slotIds[2]; // +0x24
                break;
            case 8:
                slotValue = &this->slotIds[3]; // +0x2c
            }
            if (*actionId == *slotValue) goto LAB_00479e9a;
            index = index + 1;
        } while (index < 4);
        slotMask = 0;
LAB_00479e9a:
        if ((this->activeSlots & slotMask) != 0) {
            duration = this->delayDuration; // +0x3c
            if (0.0 < duration) {
                // Allocate a timer event (size 0xC)
                node = (undefined4 *)FUN_009c8e50(0xc);
                if (node == (undefined4 *)0x0) {
                    node = (undefined4 *)0x0;
                }
                else {
                    *node = &PTR_FUN_00e31e2c; // vtable for timer event
                    if (this == (ActionDelayManager*)0x3c) { // likely NULL check
                        index = 0;
                    }
                    else {
                        index = (int)this + 0xc; // offset to a linked list head?
                    }
                    node[1] = index;
                    node[2] = 0;
                    if (index != 0) {
                        node[2] = *(undefined4 *)(index + 4);
                        *(undefined4 **)(index + 4) = node + 1;
                    }
                }
                // Queue the action with the duration
                FUN_00440590(this->timerQueue, 0, duration, node, 0); // +0x40
            }
            else {
                // Immediate cancellation: clear the timer queue
                if (this == (ActionDelayManager*)0x3c) {
                    tempInt = 0;
                }
                else {
                    tempInt = (int)this + 0xc;
                }
                tempStack = &PTR_FUN_00e31e2c;
                local_10 = 0;
                if (tempInt != 0) {
                    local_10 = *(int *)(tempInt + 4);
                    *(int **)(tempInt + 4) = &tempInt;
                }
                local_c = *(undefined4 *)(this->timerQueue); // +0x40
                local_8 = &tempStack;
                local_4 = 0;
                FUN_00408a00(&local_c, 0);
                // Restore linked list pointer
                if (tempInt != 0) {
                    int **listPtr = *(int ***)(tempInt + 4);
                    if (listPtr == (int **)&tempInt) {
                        *(int *)(tempInt + 4) = local_10;
                    }
                    else {
                        if ((int *)listPtr[1] != (int *)&tempInt) {
                            do {
                                listPtr = (int **)listPtr[1];
                            } while ((int *)listPtr[1] != (int *)&tempInt);
                        }
                        listPtr[1] = (int *)local_10;
                    }
                }
            }
            // Update remaining time with speed factor
            tempStack = (undefined **)(longlong)ROUND(this->durationMultiplier * _DAT_00e2e220); // +0x50
            this->remainingTime = DAT_01205224 - (int)tempStack; // +0x54
        }
    }
    // If the actionId matches the null ID, reset remaining time
    if (*actionId == this->nullActionId) { // +0x48
        this->remainingTime = 0;
    }
}