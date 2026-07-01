// FUNC_NAME: LinkedListIterator::advance
int* __fastcall LinkedListIterator::advance(int* iterator) {
    // iterator points to a structure: +0x00 = head (list base), +0x04 = current node pointer
    // Each node has a next pointer at +0x04
    // The list base has a sentinel/tail pointer at +0x18
    if (*iterator == 0) {
        // head is null, fatal error
        FUN_00b97aea();
    }
    int* currentNode = (int*)iterator[1];
    // currentNode is the current node, get its next pointer (at offset +0x04)
    int nextNode = *(int*)(currentNode + 1);
    iterator[1] = nextNode;
    if (nextNode == *(int*)(*iterator + 6)) { // +0x18 = offset 24 = 6 ints from head pointer
        // reached tail sentinel, fatal error (should not call next at end)
        FUN_00b97aea();
    }
    return iterator;
}