// FUNC_NAME: releaseTwoObjects
void releaseTwoObjects(void* allocator, void* obj1, void* obj2) {
    if (obj1 != nullptr) {
        // Call pre-release with flag 0 (e.g., shutdown or uninit)
        preRelease(0);
        // Call virtual destructor or release function at vtable+4
        (*(void(**)(void))(*(int*)obj1 + 4))();
        // Deallocate memory via allocator
        deallocateMemory(allocator, obj1);
    }
    if (obj2 != nullptr) {
        // Call pre-release for object2 (different function? or same without arg)
        preReleaseAlt();
        // Call virtual destructor at vtable+4
        (*(void(**)(void))(*(int*)obj2 + 4))();
        // Deallocate memory
        deallocateMemory(allocator, obj2);
    }
}