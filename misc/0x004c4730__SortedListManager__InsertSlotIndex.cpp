// FUNC_NAME: SortedListManager::InsertSlotIndex

class SortedListManager {
public:
    // +0x00: unknown
    // +0x10: base address of element array (each 0x20 bytes)
    char* baseArray; // at offset 0x10
    // +0x14: probably size count or something
};

struct ListNode {
    ListNode* next;   // +0x4 (right child / next node in sorted order)
    ListNode* prev;   // +0x8 (left child / previous node)
    int slotIndex;    // +0xC (index into baseArray, i.e., (elementAddress - baseArray) / 32)
    // Total size likely 0x10 or 0x20
};

struct Element {
    // Fields used for ordering: appear at offsets 0x8, 0xC, 0x10, 0x14, 0x18
    // We'll define as a set of keys for sorting (e.g., 5 uint32 values)
    uint32_t key[5]; // +0x8 to +0x1C? Actually keys start at +8
    // Total 0x20 bytes
};

// Insert a new element (pointed to by elementAddr) into a sorted linked list
// managed by this object. The list's head is stored at *rootPtr.
// The element is identified by its address (EAX) and inserted based on its key fields.
void SortedListManager::InsertSlotIndex(ListNode** rootPtr, Element* elementAddr) {
    if (*rootPtr == nullptr) {
        *rootPtr = this->allocateNode();
        (*rootPtr)->slotIndex = (elementAddr - this->baseArray) >> 5; // slot number = offset/32
        return;
    }

    ListNode* currentNode = *rootPtr;
    ListNode* parentNode = nullptr;

    while (true) {
        // Compute the element this node points to
        Element* nodeElement = reinterpret_cast<Element*>(
            this->baseArray + currentNode->slotIndex * 32);

        // Compare node's element with the new element (lexicographically on keys)
        bool isLess = false;
        int cmp = 0;
        // Compare keys in order: key[0], key[1], key[2], key[3], key[4]
        if (nodeElement->key[0] < elementAddr->key[0]) {
            isLess = true;
        } else if (nodeElement->key[0] == elementAddr->key[0]) {
            if (nodeElement->key[1] < elementAddr->key[1]) {
                isLess = true;
            } else if (nodeElement->key[1] == elementAddr->key[1]) {
                if (nodeElement->key[2] < elementAddr->key[2]) {
                    isLess = true;
                } else if (nodeElement->key[2] == elementAddr->key[2]) {
                    if (nodeElement->key[3] < elementAddr->key[3]) {
                        isLess = true;
                    } else if (nodeElement->key[3] == elementAddr->key[3]) {
                        if (nodeElement->key[4] < elementAddr->key[4]) {
                            isLess = true;
                        } else if (nodeElement->key[4] == elementAddr->key[4]) {
                            // All keys equal -> duplicate element found
                            // Update the node's slot index to the new element (essentially no-op)
                            currentNode->slotIndex = (elementAddr - this->baseArray) >> 5;
                            return;
                        }
                    }
                }
            }
        }

        if (!isLess) {
            // The new element is not less than the current node's element.
            // Break to handle insertion to the left (or duplicate case already handled).
            break;
        }

        // Move to the next node (right child / successor)
        parentNode = currentNode;
        currentNode = currentNode->next;
        if (currentNode == nullptr) {
            // Reached end of list: insert at tail
            ListNode* newNode = this->allocateNode();
            newNode->prev = parentNode;
            parentNode->next = newNode;
            newNode->slotIndex = (elementAddr - this->baseArray) >> 5;
            return;
        }
    }

    // The new element is >= current node's element (or equal case already handled above).
    // Check if the new element is exactly equal (should have been caught in loop, but just in case)
    Element* currentElement = reinterpret_cast<Element*>(
        this->baseArray + currentNode->slotIndex * 32);
    if (currentElement == elementAddr) {
        // Same element address? Then update index (though it's the same)
        currentNode->slotIndex = (elementAddr - this->baseArray) >> 5;
        return;
    }

    // Insert new node before currentNode (to its left)
    ListNode* newNode = this->allocateNode();
    newNode->next = currentNode;
    newNode->prev = parentNode;

    if (parentNode == nullptr) {
        // New node becomes the new head
        *rootPtr = newNode;
    } else {
        parentNode->next = newNode;
    }
    currentNode->prev = newNode;

    newNode->slotIndex = (elementAddr - this->baseArray) >> 5;
}

private:
    // Allocate a new ListNode (likely memory pool)
    ListNode* allocateNode() {
        // Actual implementation at 0x004c4560
        // For reconstruction we assume it returns a new ListNode
        return new ListNode;
    }
};