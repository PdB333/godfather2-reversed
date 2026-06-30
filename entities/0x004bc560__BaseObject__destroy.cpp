// FUNC_NAME: BaseObject::destroy
// Function address: 0x004bc560
// Role: Destructor-like cleanup that releases three sub-objects and optionally deallocates this memory.
// Offsets: +0x0c, +0x18, +0x24 are pointers to sub-objects.

int BaseObject::destroy(byte deallocateFlag)
{
    // Free sub-object at offset +0x24
    if (this->subObject24 != nullptr) {
        freeObject(this->subObject24);
    }
    // Free sub-object at offset +0x18
    if (this->subObject18 != nullptr) {
        freeObject(this->subObject18);
    }
    // Free sub-object at offset +0x0C
    if (this->subObject0C != nullptr) {
        freeObject(this->subObject0C);
    }
    // If deallocate flag is set, delete this instance
    if ((deallocateFlag & 1) != 0) {
        deallocateMemory(this);
    }
    return this; // Return pointer for chaining (unusual but present)
}