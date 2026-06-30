// FUNC_NAME: EntityManager::processPendingRemovals

void __thiscall EntityManager::processPendingRemovals(void* this, ListBase* list) {
    // this - unused except for storing a flag byte
    // list - pointer to a container structure:
    //   +0x04: pointer to an array of Item structures (size 0x70 each)
    //   +0x1c: optional active element pointer (checked for non-null and then released)
    // Each Item structure (0x70 bytes):
    //   +0x40: pointer to an EARSObject (entity/component to potentially remove)

    int iVar2 = list; // keep list pointer
    int activeElement = *(int*)(list + 0x1c); // +0x1c: active/current element pointer
    unsigned char flagByte = (unsigned char)this; // store low byte of this as flag

    // Check if active element exists and has a reference count > 0 (or similar)
    if (activeElement != 0 && *(int*)(activeElement + 8) != 0) {
        FUN_009e7530(activeElement); // release/reference count decrement
    }

    int** arrayPtr = *(int***)(iVar2 + 4); // pointer to array descriptor: [base, count, ...?]
    int base = *arrayPtr;
    int count = arrayPtr[1];
    int elementSize = 0x70;

    // Iterate over each element in the array
    for (int* current = (int*)base; current != (int*)(base + count * elementSize); current = (int*)((char*)current + 0x70)) {
        int objectPtr = *(int*)((char*)current + 0x40); // offset +0x40: pointer to object
        if (objectPtr == 0) {
            // Jump to label LAB_005587db: check again after potential deletion
            goto LAB_005587db;
        }

        // Get a unique string identifier from the object via a global singleton
        int singletonBase = *(int*)0x0113dfc8; // global singleton pointer (e.g., ObjectNameManager)
        int (*getFunc)() = **(int***)(singletonBase + 0x14); // +0x14: function pointer (e.g., getCurrentName)
        int nameId = getFunc();

        // Retrieve the name string from the object
        int (*getName)(int) = **(int***)(*arrayPtr + 0x10); // arrayPtr[0] -> some vtable, +0x10: getName method
        int objNameId = getName(objectPtr);

        char* compareResult = (char*)FUN_00ab06f0(&list, objNameId); // compare against some saved name?
        if (*compareResult != '\0') {
            // Name matches – skip to LAB_005587db
            goto LAB_005587db;
        }

LAB_005587f1:
        objectPtr = *(int*)((char*)current + 0x40);
        if (objectPtr != 0) {
            int singletonBase2 = *(int*)0x0113dfc8;
            int (*getFunc2)() = **(int***)(singletonBase2 + 0x14);
            int nameId2 = getFunc2();

            int objNameId2 = getName(objectPtr);

            char* compareResult2 = (char*)FUN_00ab06f0((int)&flagByte + 2, objNameId2); // compare against 2-byte offset from flag
            if (*compareResult2 == '\0') {
                // Name does not match – continue to next element
                goto LAB_0055883d;
            }
        }

        objectPtr = *(int*)((char*)current + 0x40);
        if (objectPtr != 0 && *(int*)(objectPtr + 8) != 0) {
            FUN_009e71f0((int)&flagByte + 3, objectPtr); // delete/release with flag
        }

LAB_0055883d:
        // Continue loop
    }

    return;

LAB_005587db:
    // Re-check object pointer after potential deletion from earlier branch
    objectPtr = *(int*)((char*)current + 0x40);
    if (objectPtr == 0) {
        goto LAB_005587f1;
    }
    if (*(int*)(objectPtr + 8) != 0) {
        FUN_009e7530(objectPtr); // release
    }
    goto LAB_005587f1;
}