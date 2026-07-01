// FUNC_NAME: EarsObject::scalarDeletingDestructor
void* __thiscall EarsObject::scalarDeletingDestructor(EarsObject* this, byte deleteFlag)
{
    // Call the actual destructor (virtual or base destructor)
    this->~EarsObject();

    // If the flag indicates heap-allocation, free the memory
    if (deleteFlag & 1) {
        // Operator delete with known size (0xC4 = 196 bytes)
        operator delete(this, 0xC4);
    }

    return this;
}