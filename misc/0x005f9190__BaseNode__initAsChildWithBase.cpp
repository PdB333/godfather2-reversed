// FUNC_NAME: BaseNode::initAsChildWithBase
undefined4* __thiscall BaseNode::initAsChildWithBase(BaseNode* this, void* baseObj) {
    // baseObj is likely a pointer to a base class object (e.g., a scene node)
    // this is the new node being initialized as a child of baseObj
    void* baseVtable = *(void**)baseObj;          // +0x00: vtable of base
    int baseField1 = *(int*)(baseObj + 4);        // +0x04: some field in base (maybe ID or size)
    
    // Call a virtual function on the base object at vtable offset 8 (index 2)
    // This is likely a pre-initialization step for the base
    (*(void (__thiscall*)(void*))(*(int*)baseVtable + 8))(baseObj);
    
    int result;
    if (baseField1 == 0) {
        result = 0;
    } else {
        result = FUN_004265d0(baseField1, baseObj); // create or fetch some resource
    }
    FUN_005f9900(this, baseObj, result); // associate this node with base
    
    // Get a child list pointer from this node; if null, use a local buffer
    void* childList = *(void**)(this + 4); // +0x04: pointer to child list
    if (childList == nullptr) {
        int localBuffer[3] = {0, 0, 0};
        childList = localBuffer;
    }
    
    // Call the first virtual function on the base object (vtable offset 0) with two args
    // This likely creates a new child node or attaches something
    int newNode = (*(int (__thiscall*)(int, void*))(**(int**)this))(0xc, childList);
    if (newNode != 0) {
        *(int*)newNode = newNode;         // self-reference: node->prev = node
        *(int*)(newNode + 4) = newNode;   // node->next = node
    }
    
    // Store the new node in this node's fields
    *(int*)(this + 0x1c) = newNode;      // +0x1c (offset 28): child pointer
    *(int*)(this + 0x18) = 0;            // +0x18 (offset 24): some flag
    
    return this;
}