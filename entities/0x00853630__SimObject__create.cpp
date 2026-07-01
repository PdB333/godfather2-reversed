// FUNC_NAME: SimObject::create
SimObject* SimObject::create(SimManager* manager, void* initData)
{
    // Allocate 0xB0 bytes with 0x10 alignment
    SimObject* obj = (SimObject*)operator_new(0xB0, 0x10);
    if (obj != nullptr) {
        obj->vtable = &SimObject_vtable;           // +0x00
        obj->referenceCount = 0;                    // +0x04
        obj->flags = 0;                              // +0x08
        obj->field_0C = 0;                           // +0x0C
        obj->field_10 = 0;                           // +0x10
        obj->nextNode = nullptr;                     // +0x14
        obj->prevNode = nullptr;                     // +0x18
        obj->id = -1;                                // +0x1C
        obj->managerPtr = nullptr;                   // +0xA0 (offset 0x28*4)
        obj->flags |= 3;                             // +0x08
    }

    // Insert into manager's linked list (manager has a dummy node at +0x48)
    int* nodePtr = obj->nextNode;  // Actually obj->listNode; but we treat the object as a node
    if (manager != nullptr) {
        nodePtr = (int*)((char*)manager + 0x48);
    }
    // Node structure: +0x00 = next, +0x04 = prev
    if (obj->nextNode != nodePtr) {
        if (obj->nextNode != nullptr) {
            FUN_004daf90(obj->nextNode);  // Possibly detach
        }
        obj->nextNode = nodePtr;
        if (nodePtr != nullptr) {
            obj->prevNode = *(int*)((char*)nodePtr + 4);  // Read old prev
            *(int**)((char*)nodePtr + 4) = &obj->nextNode; // Update prev of nodePtr
        }
    }

    // Call virtual initialization functions
    ((void (*)(void*))(obj->vtable[0x30 / 4]))(nullptr);   // vfunc at +0x30
    if (obj->field_0C != 0) {
        FUN_004daf90(obj->field_0C);
        obj->field_0C = 0;
    }
    ((void (*)(SimManager*))(obj->vtable[0x10 / 4]))(manager);  // vfunc at +0x10
    ((void (*)(SimManager*))(obj->vtable[0x18 / 4]))(manager);  // vfunc at +0x18
    obj->managerPtr = manager;                                // +0xA0
    ((void (*)(void*))(obj->vtable[0x20 / 4]))(initData);     // vfunc at +0x20
    ((void (*)(void*))(obj->vtable[0x24 / 4]))(initData);     // vfunc at +0x24
    obj->referenceCount++;                                    // +0x04

    return obj;
}