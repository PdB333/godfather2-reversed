// FUNC_NAME: ObjectArray::addUnique
void __thiscall ObjectArray::addUnique(void* this, void* object) {
    uint count = *(uint*)((int)this + 0x14);
    if (count != 0) {
        int* array = *(int**)((int)this + 0x10);
        for (uint i = 0; i < count; i++) {
            if (array[i] == (int)object) {
                return; // already in list
            }
        }
    }
    // Mark object as inactive/not in use (offset +0x68)
    *(byte*)((int)object + 0x68) = 0;
    int capacity = *(int*)((int)this + 0x18);
    if (count == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        FUN_006aa370(newCapacity); // reallocate internal array
    }
    int* array = *(int**)((int)this + 0x10);
    array[count] = (int)object;
    *(uint*)((int)this + 0x14) = count + 1;
    FUN_006aa0e0(object); // initialize/register object
}