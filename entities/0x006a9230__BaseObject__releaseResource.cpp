// FUNC_NAME: BaseObject::releaseResource
// Function at 0x006a9230: Releases a resource pointed to by offset +0x14.
// After releasing, clears the pointer and returns 1 (success).
int __thiscall BaseObject::releaseResource(void *this) {
    void *resourcePtr = *(void **)((char *)this + 0x14); // +0x14: pointer to sub-resource
    if (resourcePtr != 0) {
        // Call resource-specific release/delete function
        FUN_005e6660(resourcePtr);
        *(void **)((char *)this + 0x14) = 0;
    }
    return 1;
}