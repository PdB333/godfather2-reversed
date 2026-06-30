// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x00473a60
// Role: Base destructor for EARS objects - removes this from global active list and clears child pointer list

typedef void* VTablePtr;

class EARSObject {
public:
    VTablePtr* vtable;          // +0x00
    void* childListHead;        // +0x04 (linked list of children/pointers)
    VTablePtr* secondVtable;    // +0x08 (alternate vtable or function pointer)
    EARSObject* nextActive;     // +0x0C (next in global active list)
    EARSObject* prevActive;     // +0x10 (previous in global active list, used for relinking)

    void __fastcall destroy();
};

// Global active list head (external variable)
extern EARSObject* g_activeListHead; // or some sentinel stored elsewhere

void __fastcall EARSObject::destroy() {
    // Set vtable to base class during destruction
    this->vtable = &PTR_FUN_00e32ad8;
    this->secondVtable = &PTR_LAB_00e32aec;

    // Remove this from the intrusive singly linked active list
    // List is circular: each node's nextActive is pointer to next node,
    // and the last node's nextActive points to the address of g_activeListHead
    EARSObject* next = this->nextActive;  // +0x0C
    if (next != nullptr) {
        // Access the node pointed to by nextActive,
        // its field at +0x04 (which is actually the 'next' pointer inside that node)
        // This field typically points back to the previous node's 'nextActive' address
        int* nextNodeField = *(int**)((int)next + 4); // offset 4 in the next node
        if (nextNodeField == (int*)&this->nextActive) {
            // If it points to this node's own nextActive, it means this is the only node
            // Update that field to point to this->prevActive (or null if none)
            *(int*)((int)next + 4) = (int)this->prevActive;
        } else {
            // Traverse to find the node whose 'next' pointer points to this node's nextActive
            int* currentNode = nextNodeField;
            int* traversalPtr = (int*)currentNode[1]; // offset 4 again (next of that node)
            while (traversalPtr != (int*)&this->nextActive) {
                currentNode = traversalPtr;
                traversalPtr = (int*)currentNode[1];
            }
            // Update that node's next to skip this node
            currentNode[1] = (int)this->prevActive;
        }
    }

    // Set vtable to fully destroyed state
    this->vtable = &PTR_FUN_00e32808;

    // Clear the child list (each child node is a two-dword structure: pointer and next)
    // Iterate through list starting at +0x04
    EARSObject** childNode = (EARSObject**)this->childListHead;
    while (childNode != nullptr) {
        EARSObject** nextChild = (EARSObject**)childNode[1]; // next pointer in node
        childNode[1] = nullptr;
        childNode[0] = nullptr;
        childNode = nextChild;
    }
}