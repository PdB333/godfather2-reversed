// FUNC_NAME: EARS::MemoryNode::MemoryNode

// Reconstructed constructor for a memory node (intrusive doubly linked list node) used in the EARS engine pool allocator.
// Address: 0x005f8f90

#include <cstdint>

// Forward declarations for helper functions (unknown)
int32_t FUN_004265d0(int32_t param, void* ptr);
void FUN_005f9680(void* this_ptr, void* allocator, int32_t size);

// The node class is part of a memory pool; each node has a pointer to its allocator (vtable-based)
// and a 'next' pointer for the free list. When the node is created, it self-links as a circular list element.
class EARS::MemoryNode {
public:
    // +0x00: Pointer to the allocator object (its first field is a vtable)
    void* m_pAllocator; // offset 0
    
    // +0x04: Size or type identifier (used to request allocation from the allocator)
    int32_t m_allocationSize; // offset 4
    
    // +0x06 - +0x13: Other fields (unknown), likely padding or other node data
    
    // +0x18: Next pointer in the circular list (offset 24)
    MemoryNode* m_pNext; // offset 24
    
    // +0x1C: Previous pointer in the circular list (offset 28)
    MemoryNode* m_pPrev; // offset 28 (set to 0 in this constructor, then overwritten later)
    
    // Constructor: initializes the node and allocates a linked list element from the allocator.
    // The allocator is assumed to have two virtual methods:
    //   vtable[2] (offset 8): void initialize(void* ptr) - called to set up the allocator state
    //   vtable[0] (offset 0): void* allocate(uint32_t size, void* buffer) - allocator method
    // The buffer parameter is a temporary memory region; if m_pNext (offset 4) is null, a stack buffer is used.
    void constructor() {
        // Get allocator pointer from this node
        void* allocator = m_pAllocator; // from this+0
        
        // The allocator's vtable is at the start. Call virtual function at vtable index 2 (offset 8)
        // which presumably initializes the allocator with the node as context? 
        // The parameter is the allocator itself (cast to int for calling)
        typedef void (__thiscall* InitFunc)(void*);
        InitFunc initFunc = *(InitFunc*)(*(uintptr_t*)allocator + 8);
        initFunc(allocator);

        // Determine size for allocation: if m_allocationSize is zero, use 0; otherwise call helper FUN_004265d0
        int32_t allocSize = 0;
        if (m_allocationSize != 0) {
            allocSize = FUN_004265d0(m_allocationSize, allocator);
        }

        // Call another helper that likely sets up the node with the allocator and computed size
        FUN_005f9680(this, allocator, allocSize);

        // Determine buffer to pass to the allocator's allocate method.
        // If the node's "next" pointer (offset 4? actually the code checks param_1[1] which is offset 4)
        // is null, we use a stack-local buffer as a temporary allocation target.
        void* buffer = nullptr;
        if (m_pNext == nullptr) { // offset 4 interpreted as m_pNext? (unlikely, but code says offset 4)
            // Stack buffer (initialized to zero) used as fallback
            uint32_t stackBuf[3] = {0, 0, 0};
            buffer = stackBuf;
        }

        // Call the allocator's first virtual function (vtable[0]) with size 0xC (12 bytes) and the buffer pointer.
        // This appears to be a memory allocation method that returns a pointer to a new node.
        typedef void* (__thiscall* AllocateFunc)(void*, uint32_t, void*);
        AllocateFunc allocFunc = *(AllocateFunc*)(*(uintptr_t*)allocator + 0); // offset 0
        MemoryNode* newNode = static_cast<MemoryNode*>(allocFunc(allocator, 0xC, buffer));

        // Initialize the new node as a circular linked list element (self-referencing)
        if (newNode != nullptr) {
            // Set the node's first field (offset 0) to itself (prev pointer? actually self-link)
            *(intptr_t*)newNode = reinterpret_cast<intptr_t>(newNode);
            
            // Set the node's second field (offset 4) to itself (next pointer? self-link)
            // Note: the condition checks that &newNode[1] != nullptr, which is always true if newNode != nullptr.
            if (reinterpret_cast<intptr_t*>(newNode) + 1 != nullptr) {
                *(intptr_t*)(reinterpret_cast<uint8_t*>(newNode) + 4) = reinterpret_cast<intptr_t>(newNode);
            }
        }

        // Store the new node at offset 24 (m_pNext) and clear offset 28 (m_pPrev)
        m_pNext = newNode; // offset 24
        m_pPrev = nullptr; // offset 28 (code sets param_1[7] = 0, which is offset 28)
    }
};

// Note: The mapping of offsets is approximate. The code uses param_1[0] (offset 0), param_1[1] (offset 4),
// param_1[6] (offset 24), param_1[7] (offset 28). The virtual function indices are offset 8 and 0 in the vtable.
// The use of 'next' at offset 4 is ambiguous; it might be a size or a flag. Reconstructed for consistency.