// FUNC_NAME: RefCounted::safeRelease
// Function at 0x004f2ce0: Decrements reference count and calls destructor if count reaches zero, 
// but only if the object passes a validity check. Returns a pointer to a static "valid" flag on success, null on failure.
// Object layout: +0 vtable, +4 reference count (int)
// vtable[1] (offset 4) = destructor, vtable[2] (offset 8) = validity check (takes an argument)

static const char g_validFlag = 0; // Dummy valid flag

char* __fastcall RefCounted::safeRelease(void* thisPtr, int context, int* obj)
{
    if (obj != nullptr)
    {
        // Call validity check via vtable at offset 8, passing context
        bool isValid = (**(bool (__thiscall**)(void*, int))(*obj + 8))(obj, context);
        if (isValid)
        {
            // Decrement reference count at offset 4
            int* refCount = obj + 1;
            (*refCount)--;
            if (*refCount == 0)
            {
                // Call destructor via vtable at offset 4
                (**(void (__thiscall**)(void*))(*obj + 4))(obj);
            }
            return const_cast<char*>(&g_validFlag); // Return pointer to valid flag
        }
        else
        {
            // Even if invalid, decrement and possibly destroy
            int* refCount = obj + 1;
            (*refCount)--;
            if (*refCount == 0)
            {
                (**(void (__thiscall**)(void*))(*obj + 4))(obj);
            }
        }
    }
    return nullptr;
}