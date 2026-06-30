// FUNC_NAME: EARS::ContainerNode::ContainerNode(EARS::ContainerNode* parent, int param)
// Address: 0x0073ed00

// This is a constructor for a container node that registers itself into a parent list.
// The parent is expected to have a virtual function (vtable index 4) that returns a status
// and possibly a pointer to a node. The node's offset 0x48 from its base is used for list linking.
// Member layout:
// +0x00: vtable (set to &PTR_LAB_00d6386c)
// +0x14: m_capacity (int)
// +0x15: m_size (int)
// +0x16: m_pHead (pointer to node, may be treated as list head)
// +0x17: m_pTail (pointer to node)
// +0x18: m_flags (short)
// +0x12: m_pParentOffsetMember (pointer to a subobject inside parent, used to derive parent base)

// The parent base (piVar6) is obtained by subtracting 0x48 from that pointer.
// The parent's vtable at index 4 is called with a hash 0x369ac561 and an out parameter.
// The result determines whether to allocate/replace a node.
// After linking, a value from FUN_0077dd80() is stored in m_capacity and also in the base of the
// node (or parent container) at offset 0x2580.

#include <stdint.h>

class EARS_ContainerNode;

// Forward declarations for functions called
extern "C" void FUN_004ac120(EARS_ContainerNode* parent, int arg);
extern "C" void FUN_004daf90(void* ptr);   // Possibly destructor for a list node
extern "C" uint32_t FUN_0077dd80();         // Returns some global value

class EARS_ContainerNode {
public:
    // Virtual table pointer (offset 0x00)
    // Members:
    // offset 0x12: m_pParentOffsetMember (pointer to a member inside parent)
    // offset 0x14: m_capacity
    // offset 0x15: m_size
    // offset 0x16: m_pHead (pointer to a node)
    // offset 0x17: m_pTail (pointer to a node)
    // offset 0x18: m_flags (short)
    
    // Constructor
    // __thiscall
    EARS_ContainerNode(EARS_ContainerNode* parent, int arg) {
        // Call base class constructor
        FUN_004ac120(parent, arg);
        
        // Set vtable
        *reinterpret_cast<void***>(this) = &PTR_LAB_00d6386c;
        
        // Initialize capacity and size to 4
        this->m_capacity = 4;
        this->m_size = 4;
        
        // Initialize head, tail, and flags
        int** ppHead = reinterpret_cast<int**>(&this->m_pHead); // +0x16
        *ppHead = 0;                 // m_pHead = 0
        this->m_pTail = 0;          // m_pTail = 0
        *reinterpret_cast<short*>(&this->m_pTail + 2) = 0; // short at +0x18 (m_flags)
        
        // Get parent base from offset member
        void* pParentOffsetMember = reinterpret_cast<void*>(this->m_pParentOffsetMember); // +0x12
        int* piVar6;
        if (pParentOffsetMember == 0) {
            piVar6 = 0;
        }
        else {
            // The parent offset member points 0x48 bytes into the parent container
            piVar6 = reinterpret_cast<int*>(static_cast<char*>(pParentOffsetMember) - 0x48);
        }
        
        // Prepare output parameter (initialized to 0)
        int outParam = 0;
        
        // Call virtual function on parent base (vtable index 4: at offset 0x10)
        // Signature: char __thiscall (uint hash, int* outParam)
        // Hash: 0x369ac561
        char cResult = 0;
        if (piVar6 != 0) {
            typedef char (__thiscall* VFuncType)(void*, uint, int*);
            VFuncType vfunc = *(VFuncType**)(*(void***)piVar6)[4];
            cResult = vfunc(piVar6, 0x369ac561, &outParam);
        }
        
        // Use outParam and the return value to compute a node pointer
        // NOTE: unaff_retaddr is a Ghidra artifact; treat as some register value.
        uint unaff_retaddr = 0; // Simulate unknown value; likely from a register
        uint uVar3 = -(uint)(cResult != 0) & unaff_retaddr;
        int* iVar4;
        if (uVar3 == 0) {
            iVar4 = 0;
        }
        else {
            iVar4 = reinterpret_cast<int*>(static_cast<uintptr_t>(uVar3 + 0x48));
        }
        
        // Update head pointer (m_pHead) and link the node
        if (*ppHead != iVar4) {
            if (*ppHead != 0) {
                FUN_004daf90(ppHead); // Destroy old list
            }
            *ppHead = iVar4; // Set new head
            if (iVar4 != 0) {
                // Save the old next pointer (at node+4) into m_pTail
                this->m_pTail = *reinterpret_cast<int**>(iVar4 + 4);
                // Set node's next pointer (at +4) to point back to the head pointer variable
                *reinterpret_cast<int**>(static_cast<char*>(iVar4) + 4) = reinterpret_cast<int*>(ppHead);
            }
        }
        
        // Recompute iVar4 as the base of the node (offset -0x48 from head)
        if (*ppHead == 0) {
            iVar4 = 0;
        }
        else {
            iVar4 = reinterpret_cast<int*>(static_cast<char*>(*ppHead) - 0x48);
        }
        
        // Get a value from external function
        uint32_t value = FUN_0077dd80();
        this->m_capacity = value;
        
        // Store this value at a large offset (0x2580) from the node base
        if (iVar4 != 0) {
            *reinterpret_cast<uint32_t*>(static_cast<char*>(iVar4) + 0x2580) = value;
        }
        
        // Update size to equal capacity
        this->m_size = this->m_capacity;
    }
    
    // Member variables (approximate)
    // +0x00: void** vtable;
    // +0x04...: unknown, but +0x12 is m_pParentOffsetMember
    // We'll define the structure pragmatically.
    // Since the exact layout is unknown, we'll use computed offsets.
    // But for clarity, we'll define the members below as accessible via offsets.
    // However, to keep code clean, we'll just use reinterpret_cast in the constructor.
    
    // Placeholder member definitions (not actually used in this function)
    // However, they help understanding.
    int m_capacity; // +0x14
    int m_size;     // +0x15
    int* m_pHead;   // +0x16
    int* m_pTail;   // +0x17
    short m_flags;  // +0x18
    // m_pParentOffsetMember at +0x12 (4 bytes)
    // This is actually offset 0x12 from this, but we haven't defined it.
    // For the code, we just compute as needed.
};

// The vtable pointer is set to a global symbol
extern void* PTR_LAB_00d6386c; // vtable for this class

// Note: The exact class name is unknown; this is a reconstruction based on the decompilation.
// The function uses intrusive list insertion and a parent resource lookup.