// FUNC_NAME: SomeClass::setLinkedNode (linked list node setter at 0x73e120)

void __thiscall SomeClass::setLinkedNode(SomeClass* this, int param_2)
{
    int** ppNode = (int**)(this + 0x54); // pointer to the linked node (this->m_pNode)
    int targetNode;

    if (param_2 == 0) {
        targetNode = 0;
    } else {
        targetNode = param_2 + 0x48; // param_2 is a container with embedded node at +0x48
    }

    if (*ppNode != targetNode) {
        if (*ppNode != 0) {
            FUN_004daf90(ppNode); // unlink the old node
        }
        *ppNode = targetNode; // set new node pointer
        if (targetNode != 0) {
            // Store the previous back-link from the new node's +4 field into this+0x58
            *(int*)(this + 0x58) = *(int*)(targetNode + 4);
            // Make the new node's +4 point back to this's node pointer location
            *(int**)(targetNode + 4) = ppNode;
        }
    }
    return;
}