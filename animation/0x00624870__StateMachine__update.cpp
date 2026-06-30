// FUNC_NAME: StateMachine::update
int* __thiscall StateMachine::update(int* thisPtr, int param2, float deltaTime, int* param4, undefined4* param5, undefined4 param6)
{
    ushort nodeFlags;
    undefined4* callbackList;
    int* result;
    int* nodeGroupPtr;
    char conditionResult;
    ushort* currentNode;
    undefined4* callbackEntry;
    undefined4* nodeArray;
    int nodeIndex;
    char conditionPassed;

    // Set flag bit 0 (maybe "active" or "running")
    thisPtr[5] |= 1;

    // Get current node group from array
    nodeGroupPtr = *(int**)(thisPtr[4] + thisPtr[3] * 4);
    if (nodeGroupPtr != 0) {
        // If flag bit 3 is not set, call exit callbacks for previous group?
        if ((thisPtr[5] & 8) == 0) {
            callbackList = (undefined4*)nodeGroupPtr[3];
            for (callbackEntry = (undefined4*)*callbackList; callbackEntry != 0;
                 callbackEntry = (undefined4*)*callbackEntry) {
                (**(code**)(*thisPtr + 8))(param2, deltaTime, param4, *callbackEntry, callbackEntry[1]);
                callbackEntry = callbackList + 1;
                callbackList = callbackList + 1;
            }
        }

        // Get the array of node pointers for this group
        nodeArray = (undefined4*)*nodeGroupPtr;
        currentNode = (ushort*)*nodeArray;
        nodeIndex = 0;
        if (currentNode != 0) {
            while (((*(byte*)(thisPtr + 5) & 2) == 0 && (conditionResult = FUN_00624720(), conditionResult != '\0'))) {
                // Check if node is a condition node (bit 0 set) or action node
                if ((currentNode[1] & 1) == 0) {
                    // Action node: check if condition matches (data1 == data1 & param4)
                    conditionPassed = *(uint*)(currentNode + 2) == (*(uint*)(currentNode + 2) & (uint)param4);
LAB_00624999:
                    if (conditionPassed == '\0') goto LAB_00624a70;
                    // Condition passed: call action callbacks
                    callbackList = (undefined4*)nodeGroupPtr[4];
                    for (callbackEntry = (undefined4*)*callbackList; callbackEntry != 0;
                         callbackEntry = (undefined4*)*callbackEntry) {
                        (**(code**)(*thisPtr + 8))(param2, deltaTime, param4, *callbackEntry, callbackEntry[1]);
                        callbackEntry = callbackList + 1;
                        callbackList = callbackList + 1;
                    }
                    FUN_00624d20();
                    *param5 = param6;
                    // Transition to new node group
                    thisPtr[3] = (uint)*currentNode;
                    thisPtr[0xc] = 0;
                    nodeGroupPtr = *(int**)(thisPtr[4] + (uint)*currentNode * 4);
                    // Call enter callbacks for new group
                    callbackList = (undefined4*)nodeGroupPtr[2];
                    for (callbackEntry = (undefined4*)*callbackList; callbackEntry != 0;
                         callbackEntry = (undefined4*)*callbackEntry) {
                        (**(code**)(*thisPtr + 8))(param2, deltaTime, param4, *callbackEntry, callbackEntry[1]);
                        if ((*(byte*)(thisPtr + 5) & 2) != 0) goto LAB_00624a8a;
                        callbackEntry = callbackList + 1;
                        callbackList = callbackList + 1;
                    }
                    // Reset node array for new group
                    nodeArray = (undefined4*)*nodeGroupPtr;
                    nodeIndex = nodeIndex + 1;
                    currentNode = (ushort*)*nodeArray;
                    if (0x19 < nodeIndex) break;
                }
                else {
                    // Condition node: evaluate condition
                    int context = thisPtr[1];
                    if (((context == 0) || (*(char*)(context + 0x1a5) == '\0')) ||
                       (*(char*)(context + 0x1a4) != '\0')) {
                        conditionPassed = (**(code**)(*thisPtr + 0xc))
                                                     (param2, deltaTime, *(undefined4*)(currentNode + 2),
                                                      *(undefined4*)(currentNode + 4));
                    }
                    else {
                        conditionPassed = FUN_00625390(thisPtr[2], *(undefined4*)(currentNode + 2));
                    }
                    if (conditionPassed != '\0') {
                        int context2 = thisPtr[1];
                        if (((context2 != 0) && (*(char*)(context2 + 0x1a5) != '\0')) &&
                           (*(char*)(context2 + 0x1a4) != '\0')) {
                            FUN_00625340(thisPtr[2], *(undefined4*)(currentNode + 2), param6);
                        }
                        goto LAB_00624999;
                    }
LAB_00624a70:
                    // Move to next node in array
                    currentNode = (ushort*)nodeArray[1];
                    nodeArray = nodeArray + 1;
                }
                if (currentNode == 0) break;
            }
        }
    }

LAB_00624a8a:
    // Clear flags bits 1 and 2
    thisPtr[5] &= 0xfffffff6;
    // Accumulate time
    thisPtr[0xc] = (int)((float)thisPtr[0xc] + deltaTime);

    if ((thisPtr[5] & 2) == 0) {
        return thisPtr;
    }

    // If stop flag set, call stop and return null
    result = (int*)thisPtr[7];
    (**(code**)(*thisPtr + 4))(1);
    if (result != 0) {
        result[5] |= 8;
        *param4 = (int)param5;
        (**(code**)(*result + 0x14))(/* unaff_retaddr */, param2, param4, param4, (int)param5 + 1);
    }
    return 0;
}