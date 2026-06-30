// FUNC_NAME: ObjectContainer::removeObject
// Address: 0x006bcf20
// Class: ObjectContainer (likely part of EARS game object management)
// Notes: Removes an object from an internal array by swapping with the last element.
//   Checks a flag at object+0x1f58 to determine if object is registered.
//   If not found, logs an error via FUN_004088c0 (likely error logger).
//   Notifies two listeners at this+0x54, then calls object->onRemovedFromList().

void __thiscall ObjectContainer::removeObject(ObjectContainer *this, void *object)
{
    int index;
    int lastIndex;
    int *array;
    void *owner;

    // Check if object has the "registered" flag (bit 0x15 at offset 0x1f58)
    if (((*(uint *)((byte *)object + 0x1f58) >> 0x15) & 1) == 0) {
        // Object not registered; log error
        FUN_004088c0((byte *)object + 0x3c);
        return;
    }

    index = this->findObjectIndex(object);  // FUN_006bcb60
    if (index < 0) return;  // Not found (shouldn't happen)

    lastIndex = this->count - 1;  // this->count at +0x6c
    if (index != lastIndex) {
        // Swap with last element
        array = this->array;  // +0x68
        *(int *)(array + index * 2) = *(int *)(array + lastIndex * 2);
        *(int *)(array + index * 2 + 1) = *(int *)(array + lastIndex * 2 + 1);
    }
    this->count--;

    owner = this->owner;  // +0x54
    FUN_007351c0(owner);   // Notify first listener
    FUN_00790d30(owner);   // Notify second listener

    // Notify object that it has been removed
    FUN_006bda80(object);  // object->onRemovedFromList()

    return;
}