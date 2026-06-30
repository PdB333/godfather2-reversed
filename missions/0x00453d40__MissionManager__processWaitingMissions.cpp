// FUNC_NAME: MissionManager::processWaitingMissions
void __thiscall MissionManager::processWaitingMissions(int this, int actionList)
{
    int originalGuard = s_recursionGuard;
    int thisId = *(int *)(this + 0x104); // +0x104: this manager's identifier
    int currentNode = *(int *)(actionList + 0x20); // +0x20: head of node list
    s_recursionGuard++; // increment reentrancy guard

    if (currentNode == 0) {
        s_recursionGuard = originalGuard;
        return;
    }

    do {
        int targetObject = *(int *)(currentNode + 0x2c); // +0x2c: associated object
        int* vtablePtr = *(int**)(currentNode + 0x40); // +0x40: vtable pointer (interface)

        // Check if target object is free (all state fields zero)
        bool targetFree = true;
        if (targetObject != 0) {
            if (*(short*)(targetObject + 0x100) != 0 || *(short*)(targetObject + 0x102) != 0 ||
                *(int*)(targetObject + 0x104) != thisId ||
                *(int*)(targetObject + 0x108) != 0 ||
                *(int*)(targetObject + 0x10c) != 0 ||
                *(int*)(targetObject + 0x110) != 0) {
                targetFree = false;
            }
        } else {
            targetFree = false;
        }

        if (targetFree) {
            if (vtablePtr != (int*)0x0) {
                char shouldActivate = (**(code**)(*vtablePtr + 0x3c))(); // virtual check
                if (shouldActivate != 0) {
                    // Activate the node's action
                    (**(code**)(*vtablePtr + 0x34))(); // virtual call
                } else {
                    goto LAB_checkEnable;
                }
            }
        } else {
LAB_checkEnable:
            // Check if node has pairing info and should trigger
            if (vtablePtr != (int*)0x0) {
                uint flags = *(uint*)(currentNode + 0x30); // +0x30: flags
                byte byteFlag = *(byte*)(currentNode + 0x3c); // +0x3c: enable flag
                if ((flags >> 1 & 1) == 0 && (byteFlag & 1) != 0) {
                    // Search pairing array for an eligible partner
                    uint pairCount = *(uint*)(actionList + 0x50); // +0x50: number of pairs
                    int* pairArray = *(int**)(actionList + 0x4c); // +0x4c: array of pairs
                    uint i = 0;
                    if (pairCount != 0) {
                        do {
                            if (*pairArray == currentNode) {
                                int partnerObject = pairArray[1];
                                bool partnerFree = true;
                                if (partnerObject != 0) {
                                    if (*(short*)(partnerObject + 0x100) != 0 ||
                                        *(short*)(partnerObject + 0x102) != 0 ||
                                        *(int*)(partnerObject + 0x104) != thisId ||
                                        *(int*)(partnerObject + 0x108) != 0 ||
                                        *(int*)(partnerObject + 0x10c) != 0 ||
                                        *(int*)(partnerObject + 0x110) != 0) {
                                        partnerFree = false;
                                    }
                                } else {
                                    partnerFree = false;
                                }
                                if (partnerFree) {
                                    // Both node and partner are free – activate
                                    (**(code**)(*vtablePtr + 0x34))();
                                    FUN_00454030(); // reschedule/cleanup function
                                }
                                break;
                            }
                            i++;
                            pairArray += 2;
                        } while (i < pairCount);
                    }
                }
            }
        }

        currentNode = *(int*)(currentNode + 0x34); // +0x34: next node in list
        if (currentNode == 0) {
            s_recursionGuard--;
            return;
        }
    } while (true);
}