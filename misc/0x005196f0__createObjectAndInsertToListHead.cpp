// FUNC_NAME: createObjectAndInsertToListHead
// Address: 0x005196f0
// This function creates a new object via a factory's vtable and inserts it at the head of a doubly linked list.
// The list manager pointer is expected in the ESI register (set by caller; likely a global or an instance pointer).
// param_1 (ECX): pointer to a factory object with a vtable; vtable[1] (offset 4) is the creation method.
// param_2 (EDX): fifth argument passed to the creation method (possibly an ID or flag).
// param_3 to param_6: first four arguments to the creation method (stack arguments).
// Return: void.

void __fastcall createObjectAndInsertToListHead(void* factoryObject, int extraArg5, int arg1, int arg2, int arg3, int arg4)
{
    int newNode;
    // ESI holds pointer to the list manager. In x86 fastcall, ESI is not a parameter; it is set by the caller.
    // The manager structure has a linked list head at offset +0x10.
    int* listManager = /* ESI */;  // Value provided by caller via register.

    // Call vtable[1] (second virtual function) on the factory object to create a new node.
    // Signature: int (__cdecl *)(int, int, int, int, int) at offset 4 of vtable.
    newNode = (*(int (**)(void))(*((int**)factoryObject) + 1))(arg1, arg2, arg3, arg4, extraArg5);
    if (newNode != 0)
    {
        // Node fields: +0xC4 = next pointer, +0xC8 = prev pointer (doubly linked list node)
        *(int*)(newNode + 200) = 0;           // prev = nullptr (new node becomes head)
        *(int*)(newNode + 0xC4) = *(int*)(listManager + 0x10); // next = current head

        if (*(int*)(listManager + 0x10) != 0)
        {
            // Update old head's prev to point to the new node
            *(int*)(*(int*)(listManager + 0x10) + 200) = newNode;
        }

        // Set list head to the new node
        *(int*)(listManager + 0x10) = newNode;
    }
}