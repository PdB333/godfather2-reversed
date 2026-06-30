// FUNC_NAME: LinkedList::moveNodeToEnd
void __thiscall LinkedList::moveNodeToEnd(LinkedList *thisList, void *container /* param_2 */)
{
    Node *node;
    Node *nextNode;
    Node *tail;
    bool flag;

    node = thisList->head; // *param_1
    thisList->head = node->next; // *param_1 = node->next (dereference node+8)
    // if node->next exists and its flag byte at offset 0x15 is zero?
    // Possibly indicates that node is not the only node?
    nextNode = node->next;
    if (nextNode != nullptr && *(char *)((int)nextNode + 0x15) == '\0') {
        // Update previous link of nextNode to point to the list handle? That's unusual.
        // Might be for a special marker: nextNode->prev = thisList?
        // Actually: *(int **)(*(int *)(iVar1 + 8) + 4) = param_1; => nextNode->prev = thisList
        nextNode->prev = thisList; // reinterpret cast
    }
    // Set node's prev to the current tail (thisList->tail)
    node->prev = thisList->tail; // param_1[1]
    // Special case: if thisList equals some specific list stored in container
    if (thisList == *(LinkedList **)(*(int *)(container + 0x1c) + 4)) {
        // Update that specific list's tail to this node?
        *(Node **)(*(int *)(container + 0x1c) + 4) = node;
        node->next = thisList; // node->next = thisList (pointer to list handle)
        thisList->tail = node;
        return;
    }
    tail = thisList->tail; // param_1[1]
    // Another condition: if thisList equals tail->next? (tail+8)
    if (thisList == (LinkedList *)tail->next) {
        tail->next = node;
        node->next = thisList;
        thisList->tail = node;
        return;
    }
    // Normal insertion at end: update tail's prev? Actually *piVar2 = iVar1 => tail->prev = node?
    tail->prev = node; // *piVar2 = iVar1
    node->next = thisList; // node->next = thisList
    thisList->tail = node;
}