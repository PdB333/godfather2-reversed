// FUNC_NAME: PriorityQueue::updatePriority
// Address: 0x004d0ba0
// This function updates the priority (float value) of a node identified by its ID in a thread-safe doubly linked list sorted in descending priority order.
// If the new priority is different and the node's count (active? processing?) is zero, it reinserts the node into the correct sorted position.
// Critical section at this+0x68 protects list modifications.

void __thiscall PriorityQueue::updatePriority(int id, float newPriority) {
    Node** listHead = reinterpret_cast<Node**>(this + 0x4c);  // +0x4c: pointer to head of list
    Node* node = *listHead;
    if (node == nullptr) {
        return;
    }

    // Find the node with the given ID
    while (node->id != id) {
        node = node->next;
        if (node == nullptr) {
            return;
        }
    }

    // If count > 0, don't reschedule (node is in use?)
    if (node->count > 0) {
        return;
    }

    // No change in priority
    if (node->value == newPriority) {
        return;
    }

    // Determine insertion path: if new priority is less or equal, find forward insertion point; else backward.
    if (newPriority <= node->value) {
        // Search forward for the first node with value <= newPriority
        Node* target = node->next;
        Node* start = target;
        if (target == nullptr) {
            goto done; // cannot move further, just update value
        }
        while (target != nullptr) {
            if (target->value <= newPriority) {
                break;
            }
            target = target->next;
        }
        if (target == start) {
            goto done; // same spot
        }

        EnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this + 0x68)); // +0x68
        removeNodeFromList();  // FUN_004d1ea0: generic unlink
        if (target == nullptr) {
            insertNodeAtEnd(); // FUN_004d1e40: insert at end
        } else {
            insertNodeBeforeTarget(listHead); // FUN_004d1e60: insert before 'target'
        }
        LeaveCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this + 0x68));
    } else {
        // Search backward for the first node with count>0 or value <= newPriority
        Node* target = reinterpret_cast<Node*>(node->prev);
        if (target == nullptr) {
            goto done;
        }
        while (target != nullptr) {
            if ((target->count > 0) || (target->value <= newPriority)) {
                break;
            }
            target = reinterpret_cast<Node*>(target->prev); // actually target->prev is at offset +4, stored as int
        }
        if (target == reinterpret_cast<Node*>(node->prev)) {
            goto done;
        }

        EnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this + 0x68));
        removeNodeFromList();  // FUN_004d1ea0
        if (target == nullptr) {
            insertNodeAtFront(); // FUN_004d1e20: insert at front
        } else {
            insertNodeAfterTarget(listHead); // FUN_004d1e80: insert after 'target'
        }
        LeaveCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(this + 0x68));
    }

done:
    // Store the new priority as integer (float bits)
    node->value = *reinterpret_cast<int*>(&newPriority);
}