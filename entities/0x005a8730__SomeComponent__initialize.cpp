// FUNC_NAME: SomeComponent::initialize
// Address: 0x005a8730
// Role: Lazy initialization of a component; checks a flag at offset +2, creates a resource if not initialized, then allocates memory via global function pointer.

void SomeComponent::initialize() {
    // Call base initialization (likely sets up some global state or base class)
    baseInit();

    // Check if the component is already initialized (short at offset +2)
    if ((*(short*)(this + 2) == 0) && (int resourceHandle = createResource(), resourceHandle != 0)) {
        // Perform additional setup for the resource
        setupResource();

        // Allocate memory of size 0x50 (80 bytes) associated with the resource handle
        // DAT_0119caf8 is a global function pointer, likely a memory allocator or factory
        (*g_allocFunc)(resourceHandle, 0x50);
    }
}