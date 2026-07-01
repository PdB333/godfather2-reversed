// FUNC_NAME: NetConnection::checkReadyState
bool __thiscall NetConnection::checkReadyState(SomeInterface* interface) {
    // this +0x74: flags (uint)
    uint flags = *(uint*)(this + 0x74);
    int* state = (int*)(this + 0x6c); // +0x6c: state variable (maybe sequence or timeout)
    int* innerPtr = *(int**)(this + 0x50); // +0x50: pointer to an inner object (e.g., packet window)

    // Check bit 1 of flags (0x2 mask)
    if ((flags >> 1) & 1) {
        // Bit is set: need to evaluate interface and inner object
        // Output struct from interface virtual call (size 8 bytes)
        struct OutputData {
            int a;   // local_4
            int b;   // local_8
        };

        OutputData output;
        // Call virtual function at vtable offset 0x1CC on interface object
        // This likely fills output with some state (e.g., sequence numbers)
        (*(void (__thiscall*)(SomeInterface*, OutputData*))(*(uint*)interface + 0x1CC))(interface, &output);

        // Get the container object that owns the inner object
        // innerPtr points to a member at offset 0x48 within a larger object
        int* container = nullptr;
        if (innerPtr != nullptr) {
            container = (int*)(innerPtr - 0x48 / sizeof(int)); // subtract 0x48 bytes to get base
        } else {
            // Should not happen when bit is set, but guard for safety
            return false;
        }

        // Call virtual function at vtable offset 0x1E4 on container object
        // Returns an int indicating some condition (e.g., isComplete)
        int containerResult = (*(int (__thiscall*)(int*))(*(uint*)container + 0x1E4))(container);

        // Global function to check output data (e.g., verify sequence)
        // FUN_00543270 likely tests the output struct for validity
        if (containerResult == 0 && FUN_00543270(&output) != 0) {
            // Reset state variable to 0
            *(int*)(this + 0x6c) = 0;
            return true;
        }
        return false;
    } else {
        // Bit not set: check if state variable is 0
        if (*(int*)(this + 0x6c) == 0) {
            return true;
        }
        return false;
    }
}