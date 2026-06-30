// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(EARSObject* this)
{
    // Offset +0x00: vtable pointer.
    // First set to a special destructor vtable to chain virtual destruction.
    *(void**)this = (void*)&PTR_FUN_00d5f5b0;

    // Offset +0x10: pointer to a sub-object or allocated resource.
    if (*(uint32_t*)((uint8_t*)this + 0x10) != 0) {
        FUN_004daf90(this + 4); // Likely releases the resource at offset 0x10
    }

    // Set vtable again, possibly to a null vtable to prevent further calls.
    *(void**)this = (void*)&PTR_FUN_00e32808;

    // Offset +0x04: linked list head. Iterate and clear all nodes.
    uint32_t* node = *(uint32_t**)((uint8_t*)this + 0x04);
    while (node != nullptr) {
        uint32_t* nextNode = (uint32_t*)node[1]; // node->next
        node[1] = 0; // Clear next pointer
        node[0] = 0; // Clear data (or vtable of sub-object)
        node = nextNode;
    }

    // Cleanup complete.
    return;
}