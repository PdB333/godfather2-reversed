// FUNC_NAME: ObjectPoolManager::createObjectFromTemplate
int __thiscall ObjectPoolManager::createObjectFromTemplate(ObjectPoolManager* this, int templateIndex) {
    // this+0x34: pointer to ushort array mapping templateIndex -> templateId
    ushort templateId = *(ushort*)(*(int*)((char*)this + 0x34) + templateIndex * 2);
    int newObject = 0;

    if (templateId != 0xFFFF) {
        // this+0x38: pointer to array of 8-byte slot status blocks (first int = occupancy flag)
        int* slotStatusBase = *(int**)((char*)this + 0x38);
        if (*(int*)((char*)slotStatusBase + templateIndex * 8) == 0) { // slot is free
            // this+0x28: base address of object pool (each object 0x10 bytes)
            int poolOffset = templateId * 0x10;
            int objectPtr = FUN_005faf10(poolOffset + *(int*)((char*)this + 0x28));
            if (objectPtr != 0) {
                FUN_005fa490(objectPtr); // construct/initialize object at that address
                newObject = objectPtr;
            }
        }
    }
    return newObject;
}