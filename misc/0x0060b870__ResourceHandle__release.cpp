// FUNC_NAME: ResourceHandle::release
// Address: 0x0060b870
// Role: Releases a managed resource, cleaning up and setting a destroyed flag.

// External data: Global vtable pointer for resource objects
extern void** DAT_01205868; // Points to vtable of resource objects

// Forward declaration of cleanup function
void FUN_0060b3b0(void* resource, int param2); // Unknown, likely resource cleanup

class ResourceHandle {
public:
    void* m_pOwner;          // offset +0x00: Owner or active flag (checked for non-zero)
    uint8_t pad[0x10-0x04];  // padding to next field
    void* m_pResource;       // offset +0x10: Pointer to the managed resource object
    int m_resourceId;        // offset +0x14: Identifier or argument for virtual call
    int m_param2;            // offset +0x18: Second parameter for cleanup
    uint8_t m_bDestroyed;    // offset +0x1C: Flag set to 1 after destruction

    void __thiscall release(void);
};

void __thiscall ResourceHandle::release(void) {
    // Perform initial cleanup
    FUN_0060b3b0(m_pResource, m_param2);

    if (m_pOwner != 0) {
        // Call the second virtual function (offset +4) of the resource's vtable
        // Signature: void __thiscall resourceFunc(void* resource, int id)
        typedef void (__thiscall *VirtualFunc)(void*, int);
        VirtualFunc func = (VirtualFunc)((*DAT_01205868)[1]); // second entry
        func(m_pResource, m_resourceId);

        // Clear resource pointer and mark as destroyed
        m_pResource = 0;
        m_bDestroyed = 1;
    }
}