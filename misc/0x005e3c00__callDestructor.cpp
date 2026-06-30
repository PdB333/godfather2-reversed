// FUNC_NAME: callDestructor
// Function at 0x005e3c00: Calls an object's destructor via a global destructor manager interface.
// The global at DAT_01223518 holds a pointer to a struct with a vtable pointer at offset 4.
// The destructor function is the second entry in that vtable (index 1), called with (obj, 0).

int callDestructor(void* object)
{
    // DAT_01223518 is a global variable pointing to a manager structure
    extern int* g_DestructorManagerBase; // placeholder for DAT_01223518

    int result = 0;

    // Check if manager is valid and object is non-null
    if (g_DestructorManagerBase != nullptr && object != nullptr)
    {
        // At offset 4 from the manager base is a pointer to an object with a vtable
        void* managerObj = *(void**)((char*)g_DestructorManagerBase + 4);
        if (managerObj != nullptr)
        {
            // Get the vtable pointer from the manager object
            void* vtable = *(void**)managerObj;
            // The second entry in the vtable (offset 4) is the destructor function
            typedef void (*DestructorFunc)(void*, int);
            DestructorFunc destructor = (DestructorFunc)((void**)vtable)[1];
            // Call destructor with second argument 0 (only destruct, do not free memory)
            destructor(object, 0);
            result = 1;
        }
    }
    return result;
}