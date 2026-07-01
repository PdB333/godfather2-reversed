// FUNC_NAME: SortedIDListManager::removeByID
struct SortedIDNode {
    SortedIDNode* next;      // +0x04: pointer to next node in sorted list
    unsigned char pad1[0x40]; // +0x08 to +0x43: unknown data
    unsigned short id;       // +0x44: unique identifier for this node (sorted ascending)
};

class SortedIDListManager {
public:
    SortedIDNode* head; // +0x60: pointer to first node in sorted singly linked list

    // Returns 2 on all code paths (success code?). Looks up node by id and calls Fun_00991470 to handle removal.
    int __thiscall removeByID(void* unusedParam, unsigned int targetID) {
        SortedIDNode* currentNode = this->head;
        if (currentNode != nullptr) {
            while (true) {
                if (currentNode->id == targetID) {
                    // Found the node – hand it off to an internal destructor/unlink function
                    FUN_00991470(currentNode);
                    break;
                }
                // Since the list is sorted ascending, if targetID is less than current node's ID,
                // no further nodes can match => abort search.
                if (targetID < currentNode->id) {
                    break;
                }
                currentNode = currentNode->next;
                if (currentNode == nullptr) {
                    break;
                }
            }
        }
        return 2; // Always returns 2 – possibly an "OK" or "not applicable" status code
    }
};