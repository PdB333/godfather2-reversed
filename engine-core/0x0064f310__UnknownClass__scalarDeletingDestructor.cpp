// FUNC_NAME: UnknownClass::scalarDeletingDestructor
// Function address: 0x0064f310
// Role: Scalar deleting destructor – calls the base destructor, then conditionally deallocates memory via operator delete.
// param_2 is a byte flag: if bit 0 is set, memory is freed.

void * __thiscall scalarDeletingDestructor(void *this, byte flag)
{
    // Call the actual class destructor (FUN_0064b440)
    baseDestructor(this);

    // If the flag indicates delete (bit 0), call operator delete (FUN_009c8eb0)
    if (flag & 1)
    {
        operatorDelete(this);
    }

    return this;
}