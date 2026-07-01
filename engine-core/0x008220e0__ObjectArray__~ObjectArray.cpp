// FUNC_NAME: ObjectArray::~ObjectArray

struct Node {
    Node* unk0; // +0x00
    Node* next; // +0x04
};

class ObjectArray {
public:
    // +0x00: vtable pointer (set multiple times during destruction)
    void* vtable;
    // +0x04: head of linked list (free list or node chain)
    Node* freeListHead;
    // +0x10: context pointer for custom deletion callback
    void* customContext;
    // +0x1C: custom deletion function pointer (called with customContext)
    void (*customDeleter)(void*);
    // +0x38: pointer to array of object pointers
    void** arrayPtr;
    // +0x3C: number of elements in the array
    int arrayCount;

    // Destructor – releases owned objects, frees memory, and clears internal list.
    ~ObjectArray();
};

// External helper functions (reverse engineered from callee addresses)
extern void deallocateArray(void* ptr); // FUN_009c8f10 – likely operator delete[] or pool free
extern void baseDestructor();          // FUN_00821ac0 – base class or global cleanup

// Vtable symbols
extern void* VTABLE_OBJECTARRAY; // PTR_FUN_00d733e0
extern void* VTABLE_PARENT;      // PTR_FUN_00d733a8
extern void* VTABLE_ROOT;        // PTR_FUN_00e32808

ObjectArray::~ObjectArray() {
    // --- Set vtable to this class's vtable ---
    this->vtable = &VTABLE_OBJECTARRAY;

    // Release every non‑null object in the array
    if (this->arrayCount != 0) {
        for (uint i = 0; i < (uint)this->arrayCount; i++) {
            void* obj = this->arrayPtr[i];
            if (obj != nullptr) {
                // Call the first virtual function (likely a release/destroy method) with argument 1
                (*(void (*)(int))(*(void**)obj))(1);
            }
        }
    }

    // Free the array container itself
    if (this->arrayPtr != nullptr) {
        deallocateArray(this->arrayPtr);
    }

    // --- Call base class destructor (global cleanup) ---
    baseDestructor();

    // --- Update vtable to parent's vtable after base destructor ---
    this->vtable = &VTABLE_PARENT;

    // Invoke custom deletion callback if present
    if (this->customContext != nullptr) {
        this->customDeleter(this->customContext);
    }

    // --- Set final vtable to root base ---
    this->vtable = &VTABLE_ROOT;

    // Walk and clear the linked list (likely a free list or auxiliary node chain)
    Node* node = this->freeListHead;
    while (node != nullptr) {
        Node* nextNode = node->next; // save next pointer
        node->next = nullptr;        // null out both fields
        node->unk0 = nullptr;
        node = nextNode;
    }
}