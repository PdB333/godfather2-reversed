// FUNC_NAME: ResourceHolder::releaseResource
// Address: 0x004ab370
// Role: Releases a stored resource pointer (at offset +0x10) via external cleanup function, then nulls it out. Returns this for chaining.

class ResourceHolder {
public:
    // +0x10: Pointer to a resource object that needs cleanup
    void* m_pResource;  // offset 0x10

    // __thiscall: this in ECX
    ResourceHolder* __thiscall releaseResource() {
        if (m_pResource != 0) {
            FUN_004daf90(m_pResource);  // external cleanup function
            m_pResource = 0;
        }
        return this;
    }
};