// FUNC_NAME: LinkedListManager::initNode (0x005df540)
// Initializes an internal linked list node and attaches a cloned sub-object.

class LinkedListManager {
public:
    struct Node {
        Node* next;          // +0x00
        Node* prev;          // +0x04
        Node* data;          // +0x08 (points to self in this context)
        uint8_t  flag;       // +0x15 (set to 1)
        // ... possibly more fields
    };

    // +0x00: pointer to a sub-object (has vtable)
    // +0x04: some integer (used as a clone flag)
    // +0x1C: Node* m_pListHead
    // +0x20: int32_t m_unknown (set to 0)

    void __thiscall initNode();
};

// External function declarations (inferred from decompiled names)
extern void* __fastcall cloneObject(void* param1, void* param2); // FUN_004265d0
extern void  __fastcall attachObject(LinkedListManager* self, void* obj, void* clone); // FUN_005e0170
extern LinkedListManager::Node* allocateNode(); // FUN_005e0b10 - returns a new node

void __thiscall LinkedListManager::initNode()
{
    // Retrieve the sub-object pointer and the extra integer stored at this+0x00 and this+0x04
    uint32_t* objPtr = *(uint32_t**)this; // objPtr = (int*)*this (first dword of `this` is pointer to sub-object with vtable)
    int32_t  cloneFlag = *(int32_t*)((uint8_t*)this + 4); // iVar2 = this[1]

    // Call a virtual function (index 2) on the sub-object
    (*(void (__thiscall**)(uint32_t*))(*objPtr + 8))(objPtr); // (**(code**)(*piVar3+8))(piVar3)

    // Optionally clone the sub-object if cloneFlag != 0
    void* clonedObj = nullptr;
    if (cloneFlag != 0) {
        clonedObj = cloneObject((void*)cloneFlag, objPtr);
    }

    // Attach the (possibly cloned) object to this manager
    attachObject(this, objPtr, clonedObj);

    // Allocate a new list node and store it at offset 0x1C
    Node* node = allocateNode();
    *(Node**)((uint8_t*)this + 0x1C) = node;

    // Initialize the node as a circular list head
    node->flag = 1;
    node->next = node;
    node->prev = node;
    node->data = node;   // node+8 points to itself (consistent with circular list)

    // Clear the unknown field at offset 0x20
    *(uint32_t*)((uint8_t*)this + 0x20) = 0;
}