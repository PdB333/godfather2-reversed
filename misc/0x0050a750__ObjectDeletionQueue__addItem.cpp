// FUNC_NAME: ObjectDeletionQueue::addItem
// Function address: 0x0050a750
// Role: Enqueues an object for deferred destruction, storing its vtable and two data fields into a global deletion queue buffer, then calls the actual destructor.

void __fastcall ObjectDeletionQueue::addItem(void* object)
{
    if (object == nullptr)
        return;

    // Read two fields from the object (likely size/flags/reference count)
    int data1 = *(int*)((uint8_t*)object + 0x4C);
    int data2 = *(int*)((uint8_t*)object + 0x50);

    // Global structure at DAT_01206880; offset 0x14 is a pointer to the current write pointer in a preallocated buffer.
    int** writeHandle = (int**)(DAT_01206880 + 0x14);

    // Write the vtable pointer for this object type (used by the queue processor to call the proper destructor)
    **writeHandle = (int)&PTR_LAB_011250b8;
    (*writeHandle)++;

    // Write the object pointer
    **writeHandle = (int)object;
    (*writeHandle)++;

    // Write the two additional fields
    **writeHandle = data1;
    (*writeHandle)++;
    **writeHandle = data2;
    (*writeHandle)++;

    // Call the actual destructor/finalizer
    FUN_009c8eb0(object);
}