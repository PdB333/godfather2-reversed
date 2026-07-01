// FUNC_NAME: BaseObject::destroy
void __fastcall BaseObject::destroy(BaseObject* thisObject)
{
    // Set vtable to destructor vtable (likely for this class)
    thisObject->vtable = &PTR_FUN_00d733a8;

    // If there is a child object at offset +0x10, call its destructor/release via stored function pointer at +0x1C
    if (thisObject->childObject != nullptr)
    {
        (thisObject->destroyChildFunc)(thisObject->childObject); // +0x1C: function pointer
    }

    // Switch vtable to a base subobject vtable after destruction of derived parts
    thisObject->vtable = &PTR_FUN_00e32808;

    // Clear singly-linked list starting at offset +0x4
    // Node structure: [0] = some field, [4] = next pointer
    ListNode* currentNode = reinterpret_cast<ListNode*>(thisObject->listHead); // +0x04: list head
    while (currentNode != nullptr)
    {
        ListNode* nextNode = currentNode->next; // +0x04: next pointer (offset +4 in node)
        currentNode->next = nullptr;
        currentNode->data = nullptr;            // +0x00: clear first field
        currentNode = nextNode;
    }
}