// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this) {
    // Set initial vtable (base class)
    this->vtable = reinterpret_cast<void**>(&PTR_FUN_00e37f58);
    
    // Call base class constructor
    FUN_004ebba0();
    
    // Set derived vtable (or override after base init)
    this->vtable = reinterpret_cast<void**>(&PTR_FUN_00e37110);
    
    // Check field at +0x10 (likely an ID or index)
    int id = this->field_0x10;
    if (id != 0) {
        // Global pool manager at DAT_01206880, offset +0x14 holds a free list pointer
        int** freeListPtr = reinterpret_cast<int**>(DAT_01206880 + 0x14);
        
        // Write a sentinel/label at the current free node +0x00
        *(void***)(*freeListPtr) = &PTR_LAB_01123be8;
        // Advance free list pointer past the sentinel field
        *freeListPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(*freeListPtr) + 4);
        
        // Write the ID at the free node +0x04
        **reinterpret_cast<int**>(freeListPtr) = id;
        // Advance free list pointer past the ID field
        *freeListPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(*freeListPtr) + 4);
        
        // Clear the object's ID and next field to indicate it has been pooled
        this->field_0x10 = 0;
        this->field_0x14 = 0;
    }
}