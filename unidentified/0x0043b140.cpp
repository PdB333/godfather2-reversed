// FUN_NAME: EventProcessor::iterateEventList
void __fastcall EventProcessor::iterateEventList(char param_2) // uses ESI as this; param_2 in EDX
{
    int *pCurrentNode;
    bool bFoundFlag;
    int nodeType;
    
    pCurrentNode = *(int **)(this + 0x5c); // +0x5c: pointer to current event node
    bFoundFlag = false;
    nodeType = *pCurrentNode; // first field is offset to next node (relative pointer)
    do {
        if ((nodeType == 0) || (bFoundFlag)) {
            return;
        }
        nodeType = pCurrentNode[1]; // second field: node type
        if ((nodeType == 0x20000000) || (nodeType == 0x40000000)) {
LAB_ADVANCE:
            // Advance to next node: current = (byte*)current + current->offset
            *(int *)(this + 0x5c) = *(int *)(this + 0x5c) + *(int *)*(int **)(this + 0x5c);
        }
        else {
            if (nodeType == 0x80000000) {
                // Special type: compare data with this->field_60
                nodeType = compareHash(pCurrentNode + 2); // +2 points to data field (offset 8)
                param_2 = (nodeType == *(int *)(this + 0x60)); // +0x60: expected value
                goto LAB_ADVANCE;
            }
            if (param_2 == '\0') goto LAB_ADVANCE;
            bFoundFlag = true;
        }
        pCurrentNode = *(int **)(this + 0x5c);
        nodeType = *pCurrentNode;
    } while( true );
}