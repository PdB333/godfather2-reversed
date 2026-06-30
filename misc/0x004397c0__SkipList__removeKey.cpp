// FUNC_NAME: SkipList::removeKey
// 0x004397c0 - SkipList removal function: searches by key, removes node if found, updates links at all levels, calls custom deleter, frees memory.
// Assumed class: SkipList (skip list implementation). Node structure: +0x00 key, +0x04 userData, +0x10 deleter function pointer, +0x14 forward array pointer.
// Class fields: +0x00 head (dummy node), +0x04 maxLevel, +0x10 size, +0x14 updatePath (array of Node* for search path, allocated externally).

void SkipList::removeKey(uint *keyPtr) {
    Node *current = m_head;
    int level = m_maxLevel;

    // Search from top level down, record update nodes
    do {
        Node *next = current->forward[level];
        while (next && next->key < *keyPtr) {
            current = next;
            next = current->forward[level];
        }
        m_updatePath[level] = current;   // +0x14 + 4 + level*4 in original
        --level;
    } while (level >= 0);

    // Node to remove (if key matches)
    Node *toRemove = current->forward[0]; // from last search iteration
    if (toRemove && toRemove->key == *keyPtr) {
        // Bypass toRemove at all levels where it was the immediate next
        for (int i = 0; i <= m_maxLevel; ++i) {
            Node **parentForward = m_updatePath[i]->forward; // +0x14
            if (parentForward[i] != toRemove)
                break;
            // Replace with toRemove's forward pointer at same level
            parentForward[i] = toRemove->forward[i];
        }

        // Free forward array of the removed node
        _freeArray(toRemove->forward);   // FUN_009c8f10

        // Call custom deleter if provided
        if (toRemove->userData) {
            toRemove->deleter(toRemove->userData); // +0x10 function, +0x04 context
        }

        // Free node itself
        _freeNode(toRemove);              // FUN_009c8eb0

        // Decrement size
        --m_size;                        // +0x10
    }
}