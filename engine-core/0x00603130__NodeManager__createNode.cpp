// FUNC_NAME: NodeManager::createNode

// Address: 0x00603130
// NodeManager class manages a dynamic array of node objects.
// Each node is a small structure (0x10 bytes) containing:
//   +0x00: pointer to an owner object (vtable-based, likely a factory or descriptor)
//   +0x04: a handle/ID obtained from FUN_00605c20()
//   +0x08: a byte flag (initially 0)
//   +0x0C: user parameter (param_2)
//
// Class layout (this):
//   +0x18: pointer to owner object (used for virtual call)
//   +0x20: pointer to a global manager (provides max index and data array)
//   +0x30: pointer to array of node pointers
//   +0x34: current size (number of nodes)
//   +0x38: capacity (allocated slots)
//   +0x3C: an index used for secondary lookup (e.g., current slot in another pool)

struct Node {
    void* owner;          // +0x00
    void* handle;         // +0x04   (result of FUN_00605c20)
    char  flag;           // +0x08   (byte, initially 0)
    void* userParam;      // +0x0C   (param_2)
};

class NodeManager {
public:
    // Creates a new node and inserts it into the internal array.
    // Returns pointer to the new node.
    Node* __thiscall createNode(void* param_2) {
        Node* newNode;
        int* ownerPtr;           // piVar1
        uint index;              // uVar2
        Node* result;            // puVar7
        void* fallbackData;      // puVar5
        int capacity;            // iVar6
        // Stack variables for event callback
        int eventCode = 0x01222248;  // DAT_01222248
        int eventArg1 = 0;
        char eventArg2 = 0;

        // Allocate 16 bytes for a new node
        newNode = (Node*)FUN_009c8e50(0x10);  // likely operator new or custom allocator
        if (newNode != nullptr) {
            ownerPtr = *(int**)(this + 0x18);  // this->owner
            newNode->owner = ownerPtr;
            newNode->handle = nullptr;
            newNode->flag = 0;
            newNode->userParam = param_2;
            // Call virtual function on the owner (offset 0x8 in vtable)
            (*(void(__thiscall**)(void))(*(int*)ownerPtr + 8))();
            // Get a handle/ID from external function
            newNode->handle = (void*)FUN_00605c20();
            result = newNode;
        } else {
            result = nullptr;
        }

        // Determine secondary data pointer based on current index
        index = *(uint*)(this + 0x3C);  // this->index
        if (index < *(uint*)(*(int*)(this + 0x20) + 0xA4)) {
            // Compute pointer into a big array: element size = 0x61
            fallbackData = (void*)(index * 0x61 + *(int*)(*(int*)(this + 0x20) + 0xAC));
        } else {
            fallbackData = &DAT_01222260;  // fallback global buffer
        }

        // If the handle's object has more than 1 references, perform additional init
        if (*(uint*)((int)newNode->handle + 0x14) > 1) {
            FUN_00605c70(index, fallbackData);
        }

        // Resize internal array if needed
        if (*(int*)(this + 0x34) == *(int*)(this + 0x38)) {  // size == capacity
            if (*(int*)(this + 0x38) == 0) {
                capacity = 1;
            } else {
                capacity = *(int*)(this + 0x38) * 2;
            }
            FUN_00604b60(capacity);  // reallocates array
        }

        // Insert node into array
        *(Node**)(*(int*)(this + 0x30) + *(int*)(this + 0x34) * 4) = result;
        *(int*)(this + 0x34) += 1;  // increment count

        // Fire an event callback
        FUN_00408a00(&eventCode, 0);

        return result;
    }
};