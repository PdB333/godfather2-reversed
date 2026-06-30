// FUNC_NAME: EARSObject::~EARSObject (base destructor clearing child list)
void __thiscall EARSObject::~EARSObject(void)
{
    // +0x00: vtable pointer, set to base class vtable for destructor chain
    *(void**)this = (void*)&PTR_LAB_00e42de4;

    // +0x04: pointer to head of a singly-linked list of 12-byte nodes (each node: field0, field1, next)
    Node* node = *(Node**)((int)this + 4);
    while (node != nullptr)
    {
        Node* next = node->next;   // +0x08: next pointer
        node->field0 = 0;          // +0x00: first field (e.g., flags)
        node->field1 = 0;          // +0x04: second field (e.g., data)
        node->next = nullptr;      // +0x08: clear next pointer
        node = next;
    }
}