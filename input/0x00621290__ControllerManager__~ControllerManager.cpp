// FUNC_NAME: ControllerManager::~ControllerManager
void __fastcall ControllerManager::~ControllerManager(ControllerManager* this)
{
    int node;
    
    // Set vtable pointer to derived class vtable (destructor phase 1)
    this->vtable = &PTR_FUN_00e414d8; // Derived vtable
    FUN_00621390(); // Call base destructor chain
    
    // Free member at offset 0x10 (mChildObject?)
    node = this->field_10; // param_1[4]
    if (node != 0) {
        FUN_00621750(); // Additional cleanup for this child
        FUN_009c8eb0(node); // operator delete
        this->field_10 = 0;
    }
    
    // Remove and free a linked list node at offset 0x0C (mListViewNode?)
    node = this->field_0C; // param_1[3]
    if (node != 0) {
        // Unlink node from doubly-linked list (list management)
        // Node at offset 0x1C contains pointers to adjacent nodes
        FUN_006227f0(*(undefined4*)(*(int*)(node + 0x1C) + 4)); // Notify removal?
        *(int*)(*(int*)(node + 0x1C) + 4) = *(int*)(node + 0x1C); // Update prev
        *(undefined4*)(node + 0x20) = 0; // Clear next?
        *(undefined4*)*(undefined4*)(node + 0x1C) = *(undefined4*)(node + 0x1C); // Update list head?
        *(int*)(*(int*)(node + 0x1C) + 8) = *(int*)(node + 0x1C); // Update tail?
        node = this->field_0C;
        if (node != 0) {
            FUN_00621ca0(); // Additional destructor for node
            FUN_009c8eb0(node); // operator delete
        }
        this->field_0C = 0;
    }
    
    // Call virtual destructors for embedded objects
    (**(code**)(*(int*)this->field_04 + 0xC))(); // object at offset 0x04
    (**(code**)(*(int*)this->field_18 + 0xC))(); // object at offset 0x18
    
    // Free buffer at offset 0x1C
    FUN_009c8f10(this->field_1C);
    
    // Change vtable to base vtable (destructor phase 2)
    this->vtable = &PTR_LAB_00e414dc; // Base vtable
    
    // Clear global singleton pointer
    DAT_012234ac = 0;
    return;
}