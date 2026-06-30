// FUNC_NAME: RefPointer::operator=
int* __thiscall RefPointer::operator=(const RefPointer& other) // 0x006ccd70
{
    // Self-assignment guard
    if (this != &other) {
        int newPtr = *other.m_ptr;   // Dereference other's stored pointer

        // Only change if the pointer value actually differs
        if (*this->m_ptr != newPtr) {
            // Release old reference (decrement refcount or delete)
            if (*this->m_ptr != 0) {
                ReleaseRef(this); // FUN_004daf90
            }

            // Store new pointer
            *this->m_ptr = newPtr;

            // If the new pointer is non-null, insert this node into the intrusive
            // linked list of references that the pointed object maintains.
            // The pointed object's +4 field is the head of that list.
            if (newPtr != 0) {
                // The node structure is: [0] = pointer to object, [4] = next pointer.
                // Save the current head of the list as our next.
                this->m_next = *(int**)(newPtr + 4);
                // Make this node the new head of the list.
                *(int**)(newPtr + 4) = this;
            }
        }
    }
    return this;
}