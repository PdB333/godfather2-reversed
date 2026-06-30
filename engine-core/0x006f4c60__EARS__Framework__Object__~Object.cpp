// FUNC_NAME: EARS::Framework::Object::~Object
// Function address: 0x006f4c60
// Destructor for the base Object class.
// Class layout (based on offsets):
//   +0x00: vtable pointer
//   +0x04: head of singly-linked list (Node*)
//   +0x20: pointer to a reference-counted child object (RefCountedObj*)

struct RefCountedObj; // forward declaration

struct Node {
    void* data;       // +0x00
    Node* next;       // +0x04
};

struct Object {
    void** vtable;    // +0x00
    Node* listHead;   // +0x04
    // ... possibly other fields ...
    RefCountedObj* childObj; // +0x20
};

void __fastcall Object::~Object(Object* this) {
    // Save the child object pointer before vtable switch
    RefCountedObj* child = this->childObj;

    // Set vtable to first destructor table (base class destructor)
    this->vtable = &PTR_FUN_00d606b8;

    // Release the reference-counted child
    if (child != nullptr) {
        // The child's reference count is stored immediately before the object data
        int* refCount = reinterpret_cast<int*>(child) - 1;
        if (*refCount == 0) {
            // No more references, delete the allocation (header + object)
            FUN_009c8f10(refCount);
        } else {
            // Call virtual release method (vtable[0] with argument 3)
            (*(void (**)(int))(child->vtable[0]))(3);
        }
    }

    // Switch to second vtable (derived or final destructor)
    this->vtable = &PTR_FUN_00e32808;

    // Clear the linked list (nodes are not deallocated, just reset)
    Node* current = this->listHead;
    while (current != nullptr) {
        Node* next = current->next; // +0x04
        current->next = nullptr;
        current->data = nullptr;
        current = next;
    }
}