// FUNC_NAME: SmartPointer::operator=
void __thiscall SmartPointer::operator=(const SmartPointer &other)
{
    int *currentPtr = this->m_ptr;
    if (currentPtr != 0) {
        // Decrement refCount at offset +4
        int *refCountPtr = (int *)(currentPtr + 4);
        *refCountPtr = *refCountPtr - 1;
        if (currentPtr[1] == 0) { // refCount became 0
            // Call destructor via vtable (offset +4)
            (**(code **)(*currentPtr + 4))();
        }
        this->m_ptr = 0;
    }
    // Assign new pointer from other
    int newPtr = other.m_ptr;
    this->m_ptr = newPtr;
    if (newPtr != 0) {
        // Increment refCount at offset +4
        *(int *)(newPtr + 4) = *(int *)(newPtr + 4) + 1;
    }
}