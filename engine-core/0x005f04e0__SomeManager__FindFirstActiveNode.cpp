// FUNC_NAME: SomeManager::FindFirstActiveNode
// Address: 0x005f04e0
// Iterates over a linked list of nodes (offset +0x08 head pointer, +0x12 short count), 
// finds the first node where associated data (offset +0x0C) satisfies:
//   - data->field38 >= 1
//   - IsValidForContext(context, data->field30) returns non-zero
// If the node's flag (offset +0x08 char) is 0, outputs the data pointer to outData.
// Returns the node pointer or 0 if not found.

// Forward declaration of comparison function (likely checks if data is valid for the given context)
extern int __cdecl IsValidForContext(int context, int someId);

struct Node {
    // +0x00: unknown (4 bytes)
    Node* next;         // +0x04
    char flag;          // +0x08 (0 = available?)
    void* data;         // +0x0C
};

struct Data {
    // ... other fields ...
    int someId;         // +0x30
    int someCount;      // +0x38
};

class SomeManager {
public:
    Node* head;         // +0x08
    short someShort;    // +0x12
    // other members...

    int __thiscall FindFirstActiveNode(int* outData, int context) {
        Node* nodePtr = nullptr;
        if (outData != nullptr && (*outData = 0, context != 0) &&
            this->someShort != 0 && (nodePtr = this->head, nodePtr != nullptr)) {
            while (true) {
                Data* dataPtr = static_cast<Data*>(nodePtr->data);
                if (dataPtr == nullptr || dataPtr->someCount < 1) {
                    // data is null or count < 1, skip
                } else {
                    int result = IsValidForContext(context, dataPtr->someId);
                    if (result != 0) {
                        break;
                    }
                }
                nodePtr = nodePtr->next;
                if (nodePtr == nullptr) {
                    return 0;
                }
            }
            if (nodePtr->flag == 0) {
                *outData = reinterpret_cast<int>(nodePtr->data); // return data pointer as int
            }
        }
        return reinterpret_cast<int>(nodePtr); // return node pointer as int
    }
};