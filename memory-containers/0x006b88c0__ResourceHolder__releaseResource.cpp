// FUNC_NAME: ResourceHolder::releaseResource
// Address: 0x006b88c0
// This function releases a resource pointed to by offset +0x98 and clears the pointer.
// The callee at 0x009c8eb0 is assumed to be a resource deallocation function.

class ResourceHolder {
    // +0x00 ... (unknown members)
    // +0x98 void* m_pResource; // Pointer to owned resource
public:
    void __thiscall releaseResource();
};

void __thiscall ResourceHolder::releaseResource()
{
    void* pResource = *(void**)((char*)this + 0x98); // Get pointer at +0x98
    if (pResource != 0) {
        // Call release function on the resource (FUN_009c8eb0)
        FreePointer(pResource);
        // Clear pointer to avoid dangling reference
        *(void**)((char*)this + 0x98) = 0;
    }
}