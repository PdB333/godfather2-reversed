// FUNC_NAME: EntityList::ensureActiveNode
void EntityList::ensureActiveNode(void)
{
    // this+0x8 points to the head of a linked list of nodes
    // Each node has:
    //   +0x8: next pointer
    //   +0x25: active flag (char)
    // Traverse until we find a node with active flag set (non-zero)
    // If none found, this would loop indefinitely (assumes at least one active node)
    EntityNode* node = *(EntityNode**)(this + 8);
    char activeFlag = *(char*)(node + 0x25);
    while (activeFlag == '\0') {
        node = *(EntityNode**)(node + 8);
        activeFlag = *(char*)(node + 0x25);
    }
    // No return value; function exists to ensure at least one active node exists
}