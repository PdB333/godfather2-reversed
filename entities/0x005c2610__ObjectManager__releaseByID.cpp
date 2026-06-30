// FUNC_NAME: ObjectManager::releaseByID

void ObjectManager::releaseByID(int id)
{
    int count = *(int *)(this + 0x14); // +0x14: number of objects
    if (count <= 0) {
        return;
    }

    int index = 0;
    while (true) {
        // +0x10: pointer to array of object pointers
        ManagedObject* obj = *(ManagedObject**)(*(int *)(this + 0x10) + index * 4);
        // obj->funcTable is at offset 0x10 from obj (piVar1[4])
        // funcTable[1] (offset 4) returns the object's ID
        int objID = obj->funcTable->getID();
        if (objID == id) {
            break;
        }
        index++;
        if (index >= count) {
            return;
        }
    }

    ManagedObject* obj = *(ManagedObject**)(*(int *)(this + 0x10) + index * 4);
    // Check flag at offset 0x4a (bit 1, value 2)
    if ((*(unsigned short*)((int)obj + 0x4a) & 2) != 0) {
        preRemove(); // FUN_005c0b40
        obj->field_0x28 = 0; // piVar1[10]
        obj->field_0x30 = 0; // piVar1[12]
        obj->field_0x2c = 0; // piVar1[11]
        if (obj->field_0x28 != 0) {
            // Release resource via some manager
            (**(code**)(**(int**)(DAT_012234ec + 4) + 4))(obj->field_0x28, 0);
        }
        obj->field_0x28 = 0;
        // Call release method on obj's funcTable[0] (offset 0)
        obj->funcTable->release(); // (**(code**)(*piVar1 + 4))()? Wait, careful: (**(code**)(*piVar1 + 4))() - that would be calling vtable[1]? Actually piVar1 is obj, *piVar1 is vtable, +4 is second entry. But earlier we used piVar1[4] as funcTable. Let's re-check: The code says: (**(code **)(*piVar1 + 4))(); That is calling the function at vtable+4 (the second entry of the main vtable). That is different from the funcTable at offset 0x10. So there are two vtables: main vtable at offset 0, and a separate function table at offset 0x10. The main vtable's second entry is called here. That might be a destructor or release. We'll call it obj->vtable->release2().
        obj->vtable->release2(); // (**(code**)(*piVar1 + 4))()
        obj->field_0x20 = 0; // piVar1[8]
        obj->field_0x24 = 0; // piVar1[9]
        postRemove(); // FUN_005c08f0
        // Clear flag bit 1
        *(unsigned short*)((int)obj + 0x4a) &= 0xfffd;
    }
    // Call funcTable[0] with argument 1 (maybe final release)
    obj->funcTable->releaseWithArg(1); // (**(code**)piVar1[4])(1)
    // Remove from array: decrement count and shift last element into this slot
    count--;
    *(int *)(this + 0x14) = count;
    if (index < count) {
        *(int*)(*(int *)(this + 0x10) + index * 4) = *(int*)(*(int *)(this + 0x10) + count * 4);
    }
}