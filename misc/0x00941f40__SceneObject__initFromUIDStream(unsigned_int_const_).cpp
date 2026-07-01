// FUNC_NAME: SceneObject::initFromUIDStream(unsigned int const*)

#include <cstdint>

// Forward declarations of internal helpers
// At address 0x00941ee0 - scene object base initialization
void sceneObjectBaseInit(); 
// At address 0x004211e0 - validate and extract handle from UID stream
int validateUIDStream(int const* uidStream);
// At address 0x009c8f80 - get global memory allocator singleton
void* getMemoryAllocator();
// At address 0x0060ffd0 - initialize internal node (size 0xA0)
void initInternalNode(void* nodePtr);
// At address 0x004bfbf0 - register node with scene manager
void registerNode(int handle);

struct AllocDescriptor {
    int32_t type;       // 0x00
    int32_t alignment;  // 0x04
    int32_t flags;      // 0x08
};

// Class layout:
// +0x00: m_pInternalNode (pointer to allocated node)
// +0x60: m_uid[4] (128-bit UID copied from stream)
// +0x70: m_unknownRetAddr (possibly return address or cookie)
// Total size: at least 0x74 bytes
struct SceneObject {
    // +0x00
    void* m_pInternalNode;      
    // ... padding or other members up to +0x60
    // +0x60
    uint32_t m_uid[4];           
    // +0x70
    uint32_t m_retAddrOrCookie; // See below – might be saved return address
};

void __thiscall FUN_00941f40(SceneObject* this_, int const* uidStream)
{
    sceneObjectBaseInit();                         // PRE: base class init

    int internalHandle = validateUIDStream(uidStream);
    if (internalHandle != 0) {
        // Ensure uidStream is a valid UID, then allocate an internal node
        void* allocator = getMemoryAllocator();      // singleton allocator
        AllocDescriptor desc = { 2, 0x10, 0 };       // type=2, alignment=16, flags=0

        // Use first vtable entry of allocator to allocate (size 0xA0 = 160 bytes)
        void* nodePtr;
        int (*allocateFunc)(int, void*) = *(int (**)(int, void*))allocator;
        int allocResult = allocateFunc(0xA0, &desc);
        if (allocResult == 0) {
            nodePtr = nullptr;
        } else {
            nodePtr = reinterpret_cast<void*>(allocResult);
            initInternalNode(nodePtr);                     // construct the node
            // clear two fields at offsets 0x90 and 0x94 (part of the node)
            *(uint32_t*)((uint8_t*)nodePtr + 0x90) = 0;
            *(uint32_t*)((uint8_t*)nodePtr + 0x94) = 0;
        }

        registerNode(internalHandle);                 // register with manager

        this_->m_pInternalNode = nodePtr;             // store node
        // The following line stores a value that Ghidra decoded as the return address.
        // It may be a third parameter or a saved cookie; we keep it as a field.
        // Note: 'unaff_retaddr' was a Ghidra artifact – we treat it as an unknown value.
        // For reconstruction we leave a placeholder. The actual source likely had
        // a third parameter (e.g., an ownership flag) that was passed in a register.
        int unaff_retaddr;  // This local is never assigned (Ghidra remnant)
        this_->m_retAddrOrCookie = (uint32_t)unaff_retaddr; // +0x70
    }

    // Copy 4 ints from the UID stream into the object
    this_->m_uid[0] = uidStream[0];  // +0x60
    this_->m_uid[1] = uidStream[1];  // +0x64
    this_->m_uid[2] = uidStream[2];  // +0x68
    this_->m_uid[3] = uidStream[3];  // +0x6C
}