// FUNC_NAME: TList::extractSubList
void __thiscall TList::extractSubList(TList** outHead, TList** outTail, TList* startNode, TList* endNode, TList* listSentinel, TList* endSentinel)
{
    // sentinel points to list head via next->? We'll guess structure:
    // this is a sentinel node with:
    // +0x00: prev (points to last node)
    // +0x04: next (points to first node)
    // +0x08: size or flags

    // First check: startNode must be null or equal to this (sentinel)
    if ((startNode != 0) && (startNode != this)) {
        FUN_00b97aea(); // assertion failed
    }
    // Get value from sentinel->next->prev? Assuming list is circular.
    int checkVal = *(int**)(this + 4); // sentinel->next
    checkVal = *(int*)checkVal;        // sentinel->next->prev (should be sentinel itself)

    // If endNode matches sentinel->next->prev (i.e., sentinel itself) and
    // endSentinel matches sentinel->next, extract the entire list?
    if (endNode == (TList*)checkVal) {
        TList* temp = *(TList**)(this + 4); // sentinel->next
        if ((listSentinel != 0) && (listSentinel != this)) {
            FUN_00b97aea();
        }
        if (endSentinel == temp) {
            // Special case: list has exactly one node? Extract and reset list to empty.
            // Remove node from its current position (FUN_00695700 likely unlinks)
            FUN_00695700(*(int*)(temp + 4)); // temp->next
            // Rewire temp to point to itself (circular single node)
            temp->next = temp;
            temp->prev = temp;
            this->next = 0; // sentinel next becomes null (empty)
            this->prev = this; // sentinel prev points to itself (circular empty list)
            // Output: outHead = this (sentinel?) and outTail = temp
            *outHead = this;
            *outTail = temp;
            return;
        }
    }
    // General case: iterate from (startNode, endNode) to (listSentinel, endSentinel)
    while (true) {
        if ((startNode != 0) && (startNode != listSentinel)) {
            FUN_00b97aea(); // assertion
        }
        if (endNode == endSentinel) break;
        // Advance and copy? (FUN_006941f0 and FUN_00695ac0 likely traverse and accumulate)
        FUN_006941f0();
        FUN_00695ac0((byte*)outHead, startNode, endNode);
    }
    // Output the extracted sublist's start and end nodes
    *outHead = startNode;
    *outTail = endNode;
    return;
}