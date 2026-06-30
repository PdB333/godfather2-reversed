// FUNC_NAME: releaseComponent
void releaseComponent(void* component) {
    // Check if component is in a state that requires release
    bool isActive = isComponentActive(component);
    if (!isActive) {
        // Retrieve vtable from global class descriptor
        // DAT_012234ec is a pointer to class descriptor (+4 holds vtable pointer)
        void** vtable = *(void***)(DAT_012234ec + 4);
        // Call second virtual function (index 1, offset 4) with component and flag=0 (no delete)
        typedef void (*ReleaseFunc)(void*, int);
        ReleaseFunc release = (ReleaseFunc)vtable[1];
        release(component, 0);
    }
}