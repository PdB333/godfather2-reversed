// FUNC_NAME: EARS::Framework::RefCountedPtr::assign
void __thiscall RefCountedPtr::assign(int*& ptr) {
    // Only process if the pointer is non-null
    if (ptr != 0) {
        // Call vtable function at offset 0xC (index 3) on the object.
        // This likely retrieves an internal "real" pointer or increments a reference count.
        // The function is called with the object as 'this'.
        ptr = reinterpret_cast<int*>(
            (*(code ***)ptr)[3]()  // vtable call, passes 'ptr' implicitly as 'this'
        );

        // Delegate to a helper that manages the assignment (e.g., update ref counts,
        // register in a manager, etc.). &ptr is passed as a double pointer.
        FUN_0065d650(this, &ptr);
    }
    return;
}