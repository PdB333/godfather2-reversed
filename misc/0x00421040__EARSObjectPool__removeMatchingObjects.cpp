// FUNC_NAME: EARSObjectPool::removeMatchingObjects
void EARSObjectPool::removeMatchingObjects(char type)
{
    // This function removes all pool objects that either match a given type
    // or have their usage flag (inUse) set to zero.
    // The pool internally maintains a singly linked list of nodes, each node
    // contains a pointer to the actual object + an intrusive next pointer.
    // Node layout (32-bit): +0x00: object* (the actual EARSObject), +0x04: next*
    // Object layout (partial): +0x00: refCount (int), +0x04: vtable?, 
    // +0x06: flags (byte), +0x08: two unknown fields used as call args,
    // +0x0C: ..., +0x10: another vtable pointer?,
    // +0x14: inUse (int, 0 = not in use), +0x18: secondary object pointer (typeInfo?)
    // The object pointed to by +0x18 has a type char at offset +0x0C.

    Node* prev = nullptr;
    Node* curr = head; // head is at this+4

    while (curr != nullptr)
    {
        Node* next = curr->next;
        Object* obj = curr->object;

        // Check if object should be removed: matches type OR is not in use.
        if ((*(char*)(obj->typeInfo + 0xC) == type) || (obj->inUse == 0))
        {
            // Remove node from list
            if (prev == nullptr)
            {
                // Removing head
                Node* newHead = head->next;
                freeNode(head); // FUN_009c8eb0
                head = newHead;
            }
            else
            {
                Node* nodeToRemove = prev->next;
                Node* afterRemoved = nodeToRemove->next;
                prev->next = afterRemoved;
                freeNode(nodeToRemove); // FUN_009c8eb0
            }

            count--; // this+8

            // Decrement object's reference count
            obj->refCount--;

            if (obj->refCount == 0)
            {
                // Check bit0 of flags byte at +0x06
                if ((obj->flags & 1) != 0)
                {
                    debugPrint(); // FUN_004218d0
                    obj->flags &= ~1;
                }

                if (obj->inUse != 0)
                {
                    // Call a virtual function on the typeInfo object
                    // The typeInfo object has its own vtable at first field.
                    struct TypeInfo
                    {
                        int* vtable;
                        // ... other fields at +4, +8
                    };
                    TypeInfo* ti = obj->typeInfo;
                    // Build some parameter structure from ti fields
                    ParamStruct ps;
                    ps.field0 = ti->field1;     // +4
                    ps.field1 = ti->field2;     // +8
                    ps.ptr = &obj->field7;      // +0x1C? Actually piVar1+7 is offset 28 (0x1C)
                    ps.size = obj->inUse;       // +0x14

                    // Call vtable entry at index 2 (offset 8) using the built structure
                    ti->vtable[2](&ps);
                }

                if (obj->vtbl2 != nullptr) // +0x10
                {
                    // Call two functions from vtbl2
                    // (vtable entry 1 = offset 4, entry 3 = offset 0xC)
                    obj->vtbl2->function1(obj->param1, obj->param2);
                    obj->vtbl2->function3();
                }

                freeObject(obj); // FUN_009c8eb0 on piVar1
            }
        }
        else
        {
            prev = curr;
        }

        curr = next;
    }
}