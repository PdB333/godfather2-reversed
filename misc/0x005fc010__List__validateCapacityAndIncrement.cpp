// FUNC_NAME: List::validateCapacityAndIncrement
// Address: 0x005fc010
// Role: Checks if the list has reached its maximum capacity (0x3fffffff) and increments the element count if not.
// Handles throwing an exception when the list is too long (likely an assertion in debug builds).
// Note: This function appears to be part of a custom EA EARS STL-like list implementation.
// Offset 0x1c stores the current number of elements in the list.

void __thiscall List::validateCapacityAndIncrement() {
    // Check if current size equals the sentinel maximum (0x3fffffff)
    if (*(int*)(this + 0x1c) == 0x3fffffff) {
        // List is full – trigger error/exception
        // Calling a debug assertion function (likely prints error and/or halts)
        FUN_0043f9f0("list<T> too long", 0x10);

        // The following sequence sets up and throws an exception
        // Local exception-related variables (simplified here)
        int local28 = 0xf;               // Some flags/category
        int local2c = 0;
        int local3c = local3c & 0xffffff00; // Preserve low byte
        char* local20 = "unknown";
        void** local24 = &PTR_FUN_00da9810; // Exception vtable?
        int local4 = 0xf;
        int local8 = 0;
        int local18 = local18 & 0xffffff00;

        // Initialize exception object
        FUN_0043eeb0(local40, 0, 0xffffffff); // local40 is a buffer for exception

        local24 = &PTR_FUN_00da9828;

        // Call registered exception handler if present
        if (DAT_0113d3a0 != (code*)0x0) {
            (*DAT_0113d3a0)(&local24);
        }

        // Throws via indirect call
        (*(code*)local24[2])();
        std::_Throw((exception*)&local24);

        // Cleanup after throw (dead code if throw doesn't return)
        local24 = &PTR_FUN_00da9810;
        if (0xf < local4) {
            FUN_009c8eb0(local18); // Deallocate
        }
        local8 = 0;
        local18 = local18 & 0xffffff00;
        local4 = 0xf;
        local24 = &PTR_LAB_00e31044;
        if (0xf < local28) {
            FUN_009c8eb0(local3c); // Deallocate
        }
    }

    // Increment the element count
    *(int*)(this + 0x1c) = *(int*)(this + 0x1c) + 1;
}