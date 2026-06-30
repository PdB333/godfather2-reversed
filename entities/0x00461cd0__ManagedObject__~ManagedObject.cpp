// FUNC_NAME: ManagedObject::~ManagedObject
int* __thiscall ManagedObject::~ManagedObject(int* this, byte deleteFlag) {
    if (this[0] != 0) {
        *(int*)(this[0] + 8) = 0; // Clear back reference at offset 0x08 in linked object
        this[0] = 0; // Null out managed pointer
    }
    if ((deleteFlag & 1) != 0) {
        operator delete(this); // Deallocate memory if delete flag is set
    }
    return this; // Return this pointer (common EA destructor convention)
}