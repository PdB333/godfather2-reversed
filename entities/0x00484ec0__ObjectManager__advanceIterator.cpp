// FUNC_NAME: ObjectManager::advanceIterator
// Function address: 0x00484ec0
// Role: Advances internal iterator to the next object node that is marked as active (isActive flag at +0x15 non-zero).
// The iterator stores a pointer to the current node at offset +0x04 from 'this'.
// It expects that *this (offset +0x00) is non-null (probably head or count). If null, it asserts.
// The node structure is assumed to have:
//   +0x00: ObjectNode* prev
//   +0x04: ObjectNode* something (e.g., list head or parent)
//   +0x08: ObjectNode* next
//   +0x15: char isActive

void __thiscall ObjectManager::advanceIterator(void) {
    ObjectNode* pCurrent;
    ObjectNode* pCandidate;
    ObjectNode* pNext;
    char flag;

    // Assert that the list is initialized (e.g., head pointer at this+0x00 not null)
    if (*reinterpret_cast<ObjectNode**>(this) == nullptr) {
        assertionFailure(); // FUN_00b97aea
    }

    pCurrent = *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4); // this->m_current

    // If current node is not active, traverse to find the next active node
    if (pCurrent->isActive == 0) {
        // Use the current node's prev field (offset +0x00) as a starting point
        pCandidate = reinterpret_cast<ObjectNode*>(pCurrent->prev); // *pCurrent (first field)

        if (pCandidate->isActive == 0) {
            // Walk forward via next pointers until we find an active node
            pNext = reinterpret_cast<ObjectNode*>(pCandidate->next); // pCandidate + 0x08
            flag = pNext->isActive;
            while (flag == 0) {
                pCandidate = pNext;
                pNext = reinterpret_cast<ObjectNode*>(pNext->next);
                flag = pNext->isActive;
            }
            // Set current to the node just before the active one (so that next getNext returns the active node)
            *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4) = pCandidate;
            return;
        }

        // If pCandidate (prev of current) is active, enter another traversal path
        pCurrent = reinterpret_cast<ObjectNode*>(pCurrent->field_0x04); // pCurrent->something (offset +0x04)
        flag = pCurrent->isActive;
        while (flag == 0 && *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4) == pCandidate->prev) {
            *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4) = pCurrent;
            pCurrent = reinterpret_cast<ObjectNode*>(pCurrent->field_0x04);
            flag = pCurrent->isActive;
        }

        // After loop, check if the updated current node is active; if so, assert
        if ((*reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4))->isActive != 0) {
            assertionFailure();
            return;
        }
        // Otherwise set current to the last pCurrent from loop
        *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4) = pCurrent;
    } else {
        // Current node is active; move to its next node
        pNext = reinterpret_cast<ObjectNode*>(pCurrent->next); // pCurrent + 0x08
        *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 4) = pNext;
        // Assert that the next node is NOT active (should be free slot)
        if (pNext->isActive != 0) {
            assertionFailure();
            return;
        }
    }
}