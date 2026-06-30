// FUNC_NAME: UnknownClass::scalarDeletingDestructor
int* __thiscall UnknownClass::scalarDeletingDestructor(int* this, byte flags)
{
    if (*this != 0) {
        // Call the actual destructor body (FUN_004daf90)
        this->destructor();
    }
    if ((flags & 1) != 0) {
        // Scalar delete: free memory (FUN_009c8eb0)
        operator delete(this);
    }
    return this;
}