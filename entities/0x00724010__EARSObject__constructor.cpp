// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* thisPtr) {
    // Set vtable pointer to class-specific table
    thisPtr->vtable = &PTR_FUN_00d620c8;
    
    // Set function table pointer at offset 0x3C (param_1[0xf])
    thisPtr->someFunctionTable = &PTR_FUN_00e32808;
    
    // Clean up linked list starting at offset 0x40 (param_1[0x10])
    LinkedListNode* node = (LinkedListNode*)thisPtr->listHead;
    while (node != nullptr) {
        LinkedListNode* next = node->next; // node[1]
        node->data = 0;                    // node[0]
        node->next = nullptr;              // node[1]
        node = next;
    }
    
    // Call base initialization routine
    FUN_0043b400();
}