//FUNC_NAME: ConstraintSolver::evaluateChain
void __thiscall ConstraintSolver::evaluateChain(int *this, ConstraintNode *inputNodes, uint initialValue, uint maxRemaining)
{
    int *outputBase = (int *)*this; // this->outputArray
    int count = inputNodes->count; // inputNodes[0].count? Actually inputNodes is a pointer to an array of nodes, but the first element seems to be a header with count at offset 4? Let's reinterpret.
    // Actually param_2 is a pointer to a structure that has at offset 0 a pointer to the array? No, the code uses *piVar3 = *param_2, and piVar3[1] = param_2[1]. So param_2 points to an array of two ints: first is a pointer to the node array, second is the count.
    // Let's rename accordingly.
    int *nodeArray = (int *)inputNodes[0]; // pointer to array of ConstraintNode (each 12 bytes)
    int nodeCount = inputNodes[1]; // number of nodes
    int outputOffset = *(int *)(*this + 4) - nodeCount; // this->someOffset - nodeCount? Actually iVar8 = *(int *)(*this + 4) - nodeCount. So this->baseOffset - nodeCount.
    uint prevResult = 0;
    ConstraintResult *prevOutput = nullptr;
    uint processedCount = 0;

    if (nodeCount != 0) {
        int outputIndex = outputOffset * 6; // 0x18 = 24 bytes per output, so outputIndex = outputOffset * 6 (since 24/4 = 6 ints)
        int nodeOffset = 0;
        ConstraintNode *prevNode = nullptr;
        do {
            ConstraintNode *currentNode = (ConstraintNode *)((char *)nodeArray + nodeOffset);
            char type = currentNode->type;
            ConstraintResult *currentOutput = (ConstraintResult *)((char *)outputBase + outputIndex);
            uint result = 0;

            if (type == '\0' || type == '+') {
                if (initialValue < (uint)(-currentNode->value - 1)) {
                    result = currentNode->value + initialValue;
                } else {
                    result = 0xFFFFFFFF;
                }
            } else if (type == '-') {
                if ((uint)currentNode->value < initialValue) {
                    result = initialValue - (uint)currentNode->value;
                } else {
                    result = 0;
                }
                if (result < prevResult) {
                    result = prevResult + 1;
                }
            }
            currentOutput->result = result;

            if (prevOutput != nullptr) {
                uint diff;
                if (prevOutput->result < result) {
                    diff = result - prevOutput->result;
                } else {
                    diff = 0;
                }
                char prevType = prevNode->type;
                uint newPrev;
                if (prevType == '\0') {
                    newPrev = prevNode->extra;
                    if (diff < newPrev) {
                        newPrev = diff;
                    }
                } else if (prevType == '+') {
                    if (diff < (uint)(-prevNode->extra - 1)) {
                        newPrev = prevNode->extra + diff;
                    } else {
                        newPrev = 0xFFFFFFFF;
                    }
                } else {
                    newPrev = 0;
                    if (prevType == '-') {
                        if ((uint)prevNode->extra < diff) {
                            newPrev = diff - (uint)prevNode->extra;
                        } else {
                            newPrev = 0;
                        }
                    }
                }
                prevOutput->extra = newPrev;
                if (newPrev < maxRemaining) {
                    maxRemaining -= newPrev;
                } else {
                    maxRemaining = 0;
                }
            }

            outputIndex += 6; // 0x18 bytes
            nodeOffset += 3; // 0xc bytes (3 ints)
            prevResult = currentOutput->result;
            processedCount++;
            prevNode = currentNode;
            prevOutput = currentOutput;
        } while (processedCount < (uint)nodeCount);
    }

    // Handle the last node specially
    ConstraintNode *lastNode = (ConstraintNode *)((char *)nodeArray + (nodeCount - 1) * 12);
    ConstraintResult *lastOutput = (ConstraintResult *)((char *)outputBase + (outputOffset + nodeCount - 1) * 24);
    char lastType = lastNode->type;
    int finalValue;

    if (lastType == '\0') {
        finalValue = lastNode->extra;
    } else if (lastType == '+') {
        if ((uint)(-lastNode->extra - 1) <= maxRemaining) {
            lastOutput->extra = 0xFFFFFFFF;
            return;
        }
        finalValue = lastNode->extra + (int)maxRemaining;
    } else {
        if (lastType != '-') {
            lastOutput->extra = 0;
            return;
        }
        if (maxRemaining <= (uint)lastNode->extra) {
            lastOutput->extra = 0;
            return;
        }
        finalValue = (int)maxRemaining - (uint)lastNode->extra;
    }
    lastOutput->extra = finalValue;
}