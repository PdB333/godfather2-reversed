// FUNC_NAME: NodeList::findNextActive

void NodeList::findNextActive(void)
{
    // this->+0x8 is pointer to head of linked list (or current node)
    Node* currentNode = *(Node**)((int)this + 0x8);
    char activeFlag = *(char*)((int)currentNode + 0x25);

    // Traverse linked list using 'next' pointer at offset +0x8 within node
    // until we find a node with non-zero active flag at +0x25
    while (activeFlag == '\0')
    {
        currentNode = *(Node**)((int)currentNode + 0x8);
        activeFlag = *(char*)((int)currentNode + 0x25);
    }

    // Function returns void; likely the caller uses the found currentNode
    // via a member variable or internal state
    return;
}