// FUNC_NAME: EARS::safeReleaseTwoObjects
void __cdecl safeReleaseTwoObjects(void* obj1, void* obj2)
{
    // obj1 is passed in EAX (first argument), obj2 in param_2 (stack)
    if (obj1 != nullptr) {
        // Call some release/cleanup function (maybe decrement ref count)
        FUN_0049a640(0); // Possibly a debug trace or refcount init
        // Call virtual destructor at vtable+4
        (*(void(**)(void))((int*)obj1 + 1))(); // vtable[1] = destructor
        // Finalize or unlink the object
        FUN_00497960(obj1, obj1, /* unaff_EDI*/); // third param is register that might be extra context
    }
    if (obj2 != nullptr) {
        FUN_00496470(); // Similar cleanup for second object? Might be different type
        (*(void(**)(void))((int*)obj2 + 1))();
        FUN_00497960(obj2, obj2, /* unaff_EDI*/);
    }
}