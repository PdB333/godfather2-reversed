// FUNC_NAME: BehaviorManager::findMatchingNode
int BehaviorManager::findMatchingNode(BehaviorManager* this)
{
    float fVar1;
    int iVar2;
    char cVar3;
    int* node;
    int iVar5;
    char* commandString;
    uint uVar7;
    float minValue;
    float maxValue;
    float fVar10;
    float fVar9;
    int local_20;
    int local_1c;
    byte local_18;
    int local_14;
    undefined4 unused1;
    undefined4 unused2;
    undefined4 unused3;
    int local_4;

    // Dereference this pointer to get some manager object, then get a node list pointer
    iVar5 = *(int*)(*(int*)(*this + 0x70) + 0x2c);  // this->field_0x00->someManager->nodeList
    if (iVar5 != 0) {
        // If a flag is set, reset/initialize something
        if (*(char*)(iVar5 + 0x10) != '\0') {
            FUN_005878e0();  // resetNodeState
        }
        // Extract a float value from the context (field at +0x14)
        unused1 = *(undefined4*)(this[1] + 0x14);  // this->context->someFloat
        iVar2 = *(int*)(iVar5 + 4);     // nodeList->baseValue
        iVar5 = *(int*)(iVar5 + 0xc);   // nodeList->count
        unused2 = 0;
        unused3 = FUN_00587c60(iVar2, unused1);  // convertBaseValueToFloat?
        local_4 = iVar2 + iVar5 * 4;   // end pointer computation (maybe used elsewhere)

        // Begin iterating over nodes using an iterator function
        node = (int*)FUN_00587bb0();   // getFirstNode
        while (node != (int*)0x0) {
            uVar7 = node[0xb] & 0x20;  // Check flag bit 5 (isDynamic?)
            if ((uVar7 == 0) || (*node < 2)) {
                iVar5 = node[5];        // Action result or next node ID
            }
            else {
                iVar5 = node[7];        // Alternative result if dynamic and type >= 2
            }
            if (iVar5 != -1) {
                // Get command string pointer based on same condition
                if ((uVar7 == 0) || (*node < 2)) {
                    commandString = (char*)node[4];
                }
                else {
                    commandString = (char*)node[6];
                }
                if (commandString != (char*)0x0) {
                    fVar1 = *(float*)(this[1] + 0x1c);  // context->currentValue
                    // Get min/max values based on flag
                    if ((uVar7 == 0) || (*node < 2)) {
                        minValue = (float)node[1];
                        maxValue = (float)node[2];
                    }
                    else {
                        minValue = (float)node[3];
                        maxValue = (float)node[4];
                    }
                    // If node has scale flag (bit 3), scale min/max by a global factor
                    if (((uint)node[0xb] >> 3 & 1) != 0) {
                        float scale = *(float*)(this[1] + 0x24) - DAT_00e2b1a4;  // context->someValue - globalConstant
                        minValue = scale * minValue;
                        maxValue = scale * maxValue;
                    }
                    // Check if current value is within [min, max]
                    if ((minValue <= fVar1) && (fVar1 <= maxValue)) {
                        // Build a callback context structure
                        local_1c = this[2];
                        local_20 = *this;
                        local_18 = 0;
                        local_14 = 0;
                        // Dispatch via function table based on first character of command string
                        if ((*commandString < '\n') &&
                            (cVar3 = ((code*)PTR_FUN_0103af90[*commandString])(&local_20), cVar3 != '\0')) {
                            // Node matched and callback succeeded -> store result
                            this[3] = (int)node;
                            *(byte*)(this + 4) = local_18;
                            this[5] = local_14;
                            // If dynamic node with type > 3, return a specific result
                            if (((*(byte*)(node + 0xb) & 0x20) != 0) && (3 < *node)) {
                                return node[5];
                            }
                            return 0;
                        }
                    }
                }
            }
            node = (int*)FUN_00587bb0();  // getNextNode
        }
    }
    return -1;
}