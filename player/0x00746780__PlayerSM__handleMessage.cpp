// FUNC_NAME: PlayerSM::handleMessage
int __thiscall PlayerSM::handleMessage(int arg1, int arg2, int arg3, int msgType, int arg4) {
    int tempNode;
    char exitResult;
    int result;
    int* linkHead;
    
    if (msgType == 10) {
        // Enter state 10: set up new node and attach to owner's list
        (*(code *)(*(int*)this->m_pOwner + 0x260))(); // onEnterState10?
        if (this->m_pActiveNode == 0) {
            tempNode = 0;
        } else {
            tempNode = this->m_pActiveNode - 0x48; // previous node in list
        }
        (*(code *)(*(int*)this->m_pOwner + 0x248))(tempNode); // onExitState? or transition?
        if (this->m_pActiveNode == 0) {
            tempNode = 0;
        } else {
            tempNode = this->m_pActiveNode - 0x48;
        }
        int* owner = (int*)this->m_pOwner;
        linkHead = (int*)(owner + 0x74c); // offset 0x74c: head of node list
        if (tempNode == 0) {
            tempNode = 0;
        } else {
            tempNode = tempNode + 0x48; // convert back to original
        }
        if (*linkHead != tempNode) {
            if (*linkHead != 0) {
                FUN_004daf90(linkHead); // delete old head node
            }
            *linkHead = tempNode;
            if (tempNode != 0) {
                *(int*)(owner + 0x750) = *(int*)(tempNode + 4); // save next pointer?
                *(int**)(tempNode + 4) = linkHead; // link node to head
            }
        }
        *(uint*)(owner + 0x1f58) &= 0xfffff7ff; // clear some flag (bit 11)
        (*(code *)(*(int*)this + 0x2c))(0x44af52ec, 1, 1, 0, 0x3f800000, 0x3f800000); // play animation?
        *(byte*)(&this->m_stateFlag) = 1; // mark state as active
    } else if (msgType == 11) {
        // Exit state 11: remove node if valid
        linkHead = &this->m_pActiveNode;
        if ((this->m_pActiveNode != 0) && (this->m_pActiveNode != 0x48)) {
            if (*linkHead == 0) {
                tempNode = 0;
            } else {
                tempNode = *linkHead - 0x48;
            }
            exitResult = (*(code *)(*(int*)this->m_pOwner + 0x248))(tempNode); // check exit condition
            if (exitResult != 0) {
                if (*linkHead != 0) {
                    FUN_004daf90(linkHead); // free node
                    *linkHead = 0;
                }
                *(uint*)(this->m_pOwner + 0x1f58) &= 0xfffff7ff; // clear flag again
                return 1;
            }
        }
    } else {
        // Default handler for other message types
        result = FUN_004ac700(arg1, arg2, arg3, msgType, arg4);
        return result;
    }
    return 1;
}