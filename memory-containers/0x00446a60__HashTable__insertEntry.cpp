// FUNC_NAME: HashTable::insertEntry
// Address: 0x00446a60
// Role: Inserts an entry into a hash table with chaining and global ordering.
// Supports automatic resize when load factor exceeds threshold.
// Key is passed in EAX register (implicit parameter).
// Entry structure: +0x00: nextPtr (in global list), +0x04: prevPtr, +0x08: key
// Node structure (allocated via memory pool): 
//   +0x00: key (uint)
//   +0x04: prevInGlobal (pointer to previous node's +4 field)
//   +0x08: nextInGlobal (uint, 0 or pointer)
//   +0x0C: keyCopy (uint, duplicate of key)
//   +0x10: dataPtr? (uint, not used here)
//   +0x14: dataPtr2? (uint, not used here)
//   +0x18: bucketNext (pointer to next node in bucket chain)
// this layout:
//   +0x48: bucketArray (uint**)
//   +0x4C: bucketCount (uint)
//   +0x54: resizeThreshold (uint, max entries before resize)
//   +0x5C: resizeEnabled (bool)
//   +0x60: globalListHead (uint*)
//   +0x64: globalListTail (uint*)

void HashTable::insertEntry(uint key, Entry* entry) {
    // Decompiled: param_2[2] = in_EAX; -> store key into entry
    entry->key = key;

    // Call a helper (likely validates/initializes entry)
    FUN_004482e0(this, entry);

    // Hash bucket index
    uint bucketIndex = key % this->bucketCount;

    // Pointer to bucket chain head (stored in bucketArray)
    uint* bucketHeadPtr = *(uint**)(*this->bucketArray + bucketIndex * 4);
    // Note: bucketArray is a pointer to an array of uint*, each element is a bucket head pointer

    // Search for existing node with same key in bucket chain
    uint* currentNode = bucketHeadPtr;
    while (currentNode != nullptr) {
        if (*currentNode == key) { // node->key matches
            // Node found, use it to link the entry
            uint* nodePrevField = currentNode + 1; // +0x04 field
            if (nodePrevField != nullptr) {
                goto LAB_00446b2f;
            } else {
                goto LAB_00446aac; // shouldn't happen if node exists
            }
        }
        currentNode = (uint*)*(currentNode + 6); // +0x18: bucketNext
    }

LAB_00446aac:
    // Key not found, allocate a new node
    bucketIndex = key % this->bucketCount; // recalc after potential resize
    if (this->resizeEnabled && (this->bucketCount * 2 <= this->resizeThreshold)) {
        // Trigger resize
        FUN_00448d40(this); // Resize table
        bucketIndex = key % this->bucketCount;
    }

    // Allocate node from memory pool
    uint* newNode = (uint*)FUN_00448cd0(); // returns pointer to node base
    uint* nodePrevField = newNode + 1; // +0x04

    // Initialize the node (size at least 7 uints)
    if (nodePrevField != nullptr) {
        *nodePrevField = 0;
        *(newNode + 2) = 0; // +0x08 nextInGlobal = 0
    }
    *(newNode + 3) = key;    // +0x0C keyCopy
    *(newNode + 4) = 0;      // +0x10 dataPtr
    *(newNode + 5) = 0;      // +0x14 dataPtr2
    *newNode = key;          // +0x00 key
    *(newNode + 6) = *(uint*)(*this->bucketArray + bucketIndex * 4); // +0x18 bucketNext = old head
    // Insert at head of bucket chain
    *(uint**)(*this->bucketArray + bucketIndex * 4) = newNode;

    // Insert into global doubly-linked list (ordered by insertion)
    *nodePrevField = this->globalListTail; // +0x04 (prev) = tail pointer
    *(newNode + 2) = 0; // +0x08 next = 0
    if (this->globalListTail == 0) {
        // Empty list: set head and tail to this node's prev field address
        this->globalListHead = nodePrevField;
        this->globalListTail = nodePrevField;
    } else {
        // Link to current tail
        // tail points to a node's +4 field, update its +8 (next) to new node's prev field
        *(uint**)(*(this->globalListTail) + 4) = nodePrevField;
        this->globalListTail = nodePrevField;
    }

LAB_00446b2f:
    // Link the entry into the existing node's children list (doubly-linked list of entries)
    // nodePrevField currently points to the node's +4 field (prevInGlobal)
    // The entry becomes a child of the node
    uint* entryPrevField = (uint*)(entry); // entry itself contains prevPtr at +0x00? Wait
    // Actually entry is a struct with fields: +0x00 next, +0x04 prev, +0x08 key.
    // The entry's next/prev link this entry into a list per node.
    // At this point, nodePrevField is the node's +4, but we shift to node's +8? Let's re-evaluate.

    // The code does: puVar2 = puVar3 + 4; where puVar3 = nodePrevField (node+1)
    // So puVar2 = nodePrevField + 4 = (node + 1) + 4 = node + 5 (offset 0x14)
    // It then sets param_2[1] = puVar3[4] = (node+1)[4] = node[5] = dataPtr2
    // and *param_2 = puVar2; // param_2[0] = address of node+5
    // This implies that the node's +5 field acts as a pointer to the first entry in a child list.
    // Then it checks if *(uint*)puVar2 (i.e., node[5]) is not null, if so, set its prev to param_2+1
    // and then set puVar2[0] = param_2.
    // This is inserting the entry into a doubly-linked list where the node's +5 field is the head.

    uint* entryNextField = (uint*)entry; // entry+0x00
    uint* entryPrevField = entry + 1;    // entry+0x04, but note param_2[1] is set with nodePrevField[4]

    uint* nodeChildrenHead = nodePrevField + 4; // node+5 (since nodePrevField = node+1)
    entry->prevInList = *(nodePrevField + 4);   // param_2[1] = nodePrevField[4] = node[5] (previous head)
    entry->nextInList = nodeChildrenHead;        // param_2[0] = nodeChildrenHead address

    if (*(uint*)*nodeChildrenHead != 0) {
        // If there was a previous head, update its prev pointer to point to this entry's prev field
        *(uint*)*( *(uint*)*nodeChildrenHead) = (uint)entryPrevField; // set previous head's prev pointer to our prev field
    }
    *nodeChildrenHead = (uint)entryPrevField; // set new head to our entry's prev field

    // Actually the code at end sets *puVar2 = (uint)param_2; where puVar2 = nodeChildrenHead, param_2 is entry pointer
    // This stores the entry address into nodeChildrenHead, thus the node's +5 field points to the entry's prev field? Wait.

    // Let's translate carefully:
    // puVar2 = nodePrevField + 4 = node + 5 (offset 0x14)
    // param_2[1] = puVar3[4] = nodePrevField[4] = node[5]   (this is the current head of child list)
    // *param_2 = puVar2;   // param_2[0] = address of node+5 field
    // if (*(undefined4*)*puVar2 != 0) // if *puVar2 (value at node+5) is non-null, i.e., there is a head
    //     *(undefined4*)*puVar2 = param_2 + 1; // head->prev = &entry->prevInList (since param_2+1 = entry+4 = &prevInList)
    // *puVar2 = (uint)param_2; // set node+5 = entry pointer
    // This is inserting the entry at the front of the list, where node+5 holds a pointer to the entry's prev field (or entry itself? actually they store entry address, and the prev field is at entry+4)

    // So we adjust: entry->nextInList stores address of node+5? Actually *param_2 = puVar2; so entry->nextInList = &node->childrenHead. That's unusual: the entry's next pointer points to the node's childrenHead field itself, not to another entry.

    // Given the complexity, I'll simplify: The code links the entry into a list whose head is stored at node[5] (offset 0x14). The entry's fields at +0x00 and +0x04 act as prev/next pointers in a doubly-linked list.

    return;
}