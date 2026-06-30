// FUNC_NAME: IntrusiveList::swapNodeWithNext
void __thiscall IntrusiveList::swapNodeWithNext(void* thisList, Node* node) {
    Node* nextNode = node->next; // +0x08
    node->next = nextNode->next; // +0x08, skip next
    if (*(char*)(nextNode + 0x25) == '\0') {
        nextNode->prev = node; // +0x04
    }
    nextNode->prev = node->prev; // +0x04
    if (node == ((Node*)*(int*)(thisList + 4))->next) { // +0x04 of list -> sentinel node +0x04 (tail)
        ((Node*)*(int*)(thisList + 4))->next = nextNode;
        nextNode->next = node;
        node->prev = nextNode;
        return;
    }
    Node* prevNode = node->prev; // +0x04
    if (node == prevNode->next) { // +0x00 of prev
        prevNode->next = nextNode;
        nextNode->next = node;
        node->prev = nextNode;
        return;
    }
    // Otherwise, prevNode is not the head
    prevNode->next->next = nextNode? // Actually prevNode[2] is likely prevNode->next->next? Wait careful: piVar2 is prevNode, then piVar2[2] is *(int*)(prevNode+8) = prevNode->next? No consistent. Let's check original lines.
    // Original: piVar2 = *(int **)(param_2 + 4);  // node->prev
    // if (param_2 == *piVar2) { ... head case }
    // else { piVar2[2] = (int)piVar1; ... }
    // So piVar2[2] is *(int*)(prevNode + 8) = prevNode->next?
    // So we set prevNode->next = nextNode? Actually piVar2[2] = piVar1 -> set prevNode->next = nextNode.
    prevNode->next = nextNode;
    nextNode->next = node;
    node->prev = nextNode;
}