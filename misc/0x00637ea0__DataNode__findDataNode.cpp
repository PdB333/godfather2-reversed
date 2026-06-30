// FUNC_NAME: DataNode::findDataNode
// Address: 0x00637ea0
// Searches a linked list of DataNode structures using a key and subkey (int or float comparison).
// Returns pointer to the data field (offset 0x08) if found, otherwise returns pointer to a global sentinel.
// The list head is obtained from getFirstNode() (FUN_00637490).
// DataNode layout:
//   +0x00: int key     (type discriminator)
//   +0x04: int subKey  (compared as int or float depending on key)
//   +0x08: void* data  (the returned pointer points here)
//   +0x10: DataNode* next

struct DataNode {
    int key;       // +0x00
    int subKey;    // +0x04
    void* data;    // +0x08
    DataNode* next; // +0x10
};

// Global sentinel node (DAT_00e2a93c) – used when key is not found.
extern DataNode g_sentinelDataNode; // Actually just a placeholder; the function returns its data field address.

// Forward declaration; getFirstNode() returns the head of the linked list.
DataNode* getFirstNode(void);

// __fastcall: first param (searchKey) passed in EDI, second param (unused) maybe in ECX? 
// Ghidra shows unaff_EDI, so we model as fastcall with EDI for the struct pointer.
DataNode* __fastcall findDataNode(DataNode* searchKey)
{
    int keyToFind = searchKey->key;
    DataNode* curNode = getFirstNode();

    if (curNode == nullptr) {
        return &g_sentinelDataNode;
    }

    do {
        if (curNode->key == keyToFind) {
            switch (curNode->key) {
            case 0:
                // No subkey comparison; return data pointer immediately.
                return (int*)&curNode->data;

            default:
                // Int comparison for subkey.
                if (curNode->subKey == searchKey->subKey) {
                    return (int*)&curNode->data;
                }
                break;

            case 3:
                // Float comparison for subkey (due to IEEE 754 bit pattern equality here).
                if (*(float*)&curNode->subKey == *(float*)&searchKey->subKey) {
                    return (int*)&curNode->data;
                }
                break;
            }
        }
        curNode = curNode->next;
    } while (curNode != nullptr);

    // Not found – return the sentinel data address.
    return (int*)&g_sentinelDataNode;
}