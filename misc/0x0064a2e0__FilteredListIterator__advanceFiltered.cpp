// FUNC_NAME: FilteredListIterator::advanceFiltered
typedef unsigned int uint;

struct ListNode {
    uint field_0;      // +0x00
    uint flags;        // +0x04
    uint field_8;      // +0x08
    uint field_0C;     // +0x0C
    void* next;        // +0x10
};

class FilteredListIterator {
public:
    uint filterMask;        // +0x00
    ListNode* pCurrent;     // +0x04
    ListNode* pBest;        // +0x08
    uint result[6];         // +0x0C .. +0x20 (indices 3..8)

    // Returns pointer to result array if a matching node is found, otherwise nullptr.
    uint* __thiscall advanceFiltered(uint filter, ListNode* pEnd);
};

uint* __thiscall FilteredListIterator::advanceFiltered(uint filter, ListNode* pEnd) {
    if (this == nullptr) return nullptr;

    filter = filter & this->filterMask;
    ListNode* endSentinel = (ListNode*)((char*)pEnd + 4);  // sentinel node (end+4)
    ListNode* curNode = this->pCurrent;

    while (curNode != endSentinel) {
        // If node is "inactive" (all flags except bit0 are zero), skip it.
        if ((curNode->flags & 0xFFFFFFFE) == 0) {
            // Skip consecutive inactive nodes.
            do {
                curNode = (ListNode*)this->pCurrent->next;
                this->pCurrent = curNode;
                if (curNode == endSentinel) break;
            } while ((curNode->flags & 0xFFFFFFFE) == 0);
            this->pBest = nullptr;
        } else {
            // Node is active: traverse its associated chain (beginning from next)
            ListNode* candidate;
            if (this->pBest == nullptr) {
                candidate = (ListNode*)curNode->next;
            } else {
                candidate = (ListNode*)this->pBest->next;
            }
            this->pBest = candidate;

            // Filter candidates until we return to the current node.
            while (candidate != curNode) {
                // If both filter bits 1 and 2 are set, stop filtering.
                if ((filter & 6) == 6) break;

                uint hasBit0 = (this->pBest->flags & 1);

                // Apply filter logic based on bits 1 and 2 of 'filter'.
                if ((filter & 2) == 0) {
                    if ((filter & 4) != 0) {
                        // Invert the condition.
                        hasBit0 = (hasBit0 == 0) ? 1 : 0;
                    }
                } else {
                    // Filter requires bit0 to be set.
                    if (hasBit0) break;
                }

                // Advance to next candidate.
                candidate = (ListNode*)this->pBest->next;
                this->pBest = candidate;
            }

            // If we exited the inner loop because we returned to curNode, 
            // check if the current node itself matches.
            if (this->pBest == curNode || (curNode->flags & 0xFFFFFFFE) == 0) {
                // Skip inactive nodes (as above).
                do {
                    curNode = (ListNode*)this->pCurrent->next;
                    this->pCurrent = curNode;
                    if (curNode == endSentinel) break;
                } while ((curNode->flags & 0xFFFFFFFE) == 0);
                this->pBest = nullptr;
            } else {
                // Found a matching candidate – exit outer loop.
                break;
            }
        }
        curNode = this->pCurrent;
    }

    // If a valid node was found, pack result into the iterator's result array.
    if (this->pCurrent != endSentinel) {
        ListNode* selected = this->pBest;
        // result[0] : value obtained from dereferencing the next pointer of the current node.
        this->result[0] = **(uint**)&this->pCurrent->next;
        this->result[1] = (uint)selected;
        this->result[2] = selected->flags & 0xFFFFFFFE;
        this->result[3] = selected->field_8;           // +0x08
        this->result[4] = (selected->flags & 0xFFFFFFFE) -
                          selected->field_8 +
                          selected->field_0;            // +0x00
        this->result[5] = ((selected->flags & 1) == 0) ? 0x02 : 0x04;
        return &this->result[0];                       // return pointer to result
    }

    return nullptr;
}