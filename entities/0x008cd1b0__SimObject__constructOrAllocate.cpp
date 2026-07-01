// FUNC_NAME: SimObject::constructOrAllocate
void SimObject::constructOrAllocate(void* thisObj) {
    if (thisObj != nullptr) {
        // Initialize memory to zero (likely memset or some engine initialization)
        initializeMemory();
        
        // Get the global allocator (vtable pointer from a singleton)
        int* allocatorVtable = (int*)getGlobalAllocator();
        
        // Call first virtual function (offset 4) to allocate/construct with size 0xA0 (160 bytes)
        (**(code**)(allocatorVtable + 4))(thisObj, 0xA0);
    }
}