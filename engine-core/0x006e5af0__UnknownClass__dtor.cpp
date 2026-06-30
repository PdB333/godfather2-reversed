// FUNC_NAME: UnknownClass::dtor  
void __fastcall UnknownClass::dtor(UnknownClass* this)  
{  
    // Set vtable to first destructor vtable  
    *(void**)this = &vtable_00d5faf8; // +0x00  

    // Check if child object at +0x60 exists  
    if (this->childPtr != nullptr) {  
        // Deallocate child object  
        deallocateObject(this->childPtr); // FUN_004daf90  
        this->childPtr = nullptr;  
    }  

    // Switch vtable to base class vtable (or second stage)  
    *(void**)this = &vtable_00e32808;  

    // Clear linked list starting at +0x04  
    ListNode* current = this->firstNode; // +0x04  
    while (current != nullptr) {  
        ListNode* next = current->next; // +0x04 (offset 4 within node)  
        current->next = nullptr;  
        current->data = nullptr;        // +0x00  
        current = next;  
    }  

    // Note: nodes themselves are not freed; maybe they are allocated elsewhere  
    // or this is just clearing pointers and the memory is managed externally.  
}