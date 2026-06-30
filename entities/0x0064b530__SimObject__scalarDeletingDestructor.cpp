// FUNC_NAME: SimObject::scalarDeletingDestructor
// Function address: 0x0064b530
// Role: Scalar deleting destructor. Calls base destructor at 0x0064b440 and, if the deleting flag is set, calls operator delete (0x009c8eb0) on the object.

SimObject* __thiscall SimObject::scalarDeletingDestructor(unsigned char deletingFlag)
{
    // Call the base destructor (FUN_0064b440) to clean up derived portions
    this->~SimObject();

    // If the object was dynamically allocated, release its memory
    if ((deletingFlag & 1) != 0)
    {
        operator delete(this);
    }

    return this;
}