// FUNC_NAME: DoublyLinkedList::removeByKey
bool __thiscall DoublyLinkedList::removeByKey(int key)
{
    Node* current = head;
    bool becameEmpty = false;

    if (current == nullptr) {
        // List empty already
        goto cleanup;
    }

    // Find the node with matching key
    while (current->key != key) {
        current = current->next;
        if (current == nullptr) {
            // Key not found
            someField = -1; // +0xC: possibly "last removed result" or "size marker"
            return false;
        }
    }

    // Remove node from doubly linked list
    if (current->prev == nullptr) {
        // Removing head
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            // List becomes empty, update tail
            tail = current->prev; // which is null
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        }
    } else {
        // Has previous node
        current->prev->next = current->next;
        if (current->next == nullptr) {
            // Removing tail
            tail = current->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        } else {
            current->next->prev = current->prev;
        }
    }

    // Detach the node
    current->prev = nullptr;
    current->next = nullptr;

    becameEmpty = (head == nullptr);

    // Deallocate the node memory
    Node::deallocate(current); // FUN_009c8eb0

cleanup:
    someField = -1; // +0xC: reset some flag
    return becameEmpty;
}