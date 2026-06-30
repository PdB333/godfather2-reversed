// FUNC_NAME: Entity::setActiveResource
void __thiscall Entity::setActiveResource(void* thisPtr, int newResourceHandle) {
    int flags = *(unsigned char*)((int)thisPtr + 0x300);
    if ((flags & 1) != 0) {
        markDirty(1);  // FUN_00541bb0
    }
    int currentHandle = *(int*)((int)thisPtr + 0x20c);
    if (newResourceHandle != currentHandle) {
        if (currentHandle != 0) {
            releaseHandle();  // FUN_009f01a0 – decrement refcount
            int resourceData = *(int*)((int)thisPtr + 0x210);
            if (*(int*)(resourceData + 0x10) != 0) {
                cleanupSubResource(resourceData);          // FUN_009f1b20
                releaseSubResource(resourceData + 8);      // FUN_009f1ad0
                releaseHandle();                           // FUN_009f01a0 – again?
            }
            *(int*)(resourceData + 0x10) = 0;
            // Call virtual function at index 2 of the component at +0x13c
            void* component = *(void**)((int)thisPtr + 0x13c);
            void (*vfunc)(void*) = *(void**)(*(int*)component + 8);
            vfunc(0);  // called with 0 as argument (likely 'deactivate')
        }
        *(int*)((int)thisPtr + 0x20c) = newResourceHandle;
        if (newResourceHandle != 0) {
            acquireHandle();              // FUN_009f0190 – increment refcount
            initializeNewResource();      // FUN_00542390
            // Call the same virtual function on the component (with no argument)
            void* component = *(void**)((int)thisPtr + 0x13c);
            void (*vfunc)() = *(void**)(*(int*)component + 8);
            vfunc();  // 'activate'
        }
    }
}