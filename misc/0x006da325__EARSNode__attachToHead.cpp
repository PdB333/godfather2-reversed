// FUNC_NAME: EARSNode::attachToHead
// Reconstructed C++ for function at 0x006da325
// This function initializes an EARSNode object and inserts it into a doubly linked list.
// Based on the given decompiled code, this appears to be a constructor that also attaches
// the node to a list. The list head is expected to be at an offset of 0x48 from a base pointer.

class EARSNode {
public:
    // Vtable at offset 0x0
    void* vtable;
    // Unknown pointer at +0x4
    void* unkPtr1;
    // Char flag at +0x8
    char charFlag;
    // Max value at +0xC (set to 0xFF)
    unsigned int maxVal;
    // Next pointer at +0x10
    EARSNode* m_pNext;
    // Prev pointer at +0x14
    EARSNode* m_pPrev;
    // Float at +0x20
    float value1;
    // Constant uint at +0x24
    unsigned int constant1;
    // Constant uint at +0x28
    unsigned int constant2;
    // Constant uint at +0x2C (same as constant2)
    unsigned int constant3;
    // Four floats at +0x30 to +0x3C (set to same value)
    float quat[4];
    // Pointer at +0x40 (set to 0)
    void* unkPtr2;
    // Copied constant at +0x50
    unsigned int copiedConst1;
    // Copied constant at +0x54
    unsigned int copiedConst2;
    // Float at +0x58
    float value2;
};

// Global constants referenced from data section
extern void* PTR_FUN_00d5f5b0;  // vtable pointer
extern unsigned int _DAT_00d5780c; // constant1 value
extern unsigned int _DAT_00d5cf70; // constant2 value

// External functions
void FUN_004daf90(void* pNextAddr);  // Remove from current list (detach)
void FUN_006da2b0();                 // Base constructor or additional init

// Constructor/init function – returns this
EARSNode* __fastcall FUN_006da325(EARSNode* this, int insertFlag, EARSNode* listHeadOrNull) {
    // Note: The decompiler signatures are based on register usage.
    // Here insertFlag corresponds to the Z flag (true means Z flag set, false means clear)
    // listHeadOrNull is passed in EAX (non-zero when Z flag false, points to a structure with node at +0x48)
    // In practice, the caller sets these via previous operations.

    // Initialize fields
    this->unkPtr1 = 0;  // unaff_EBX assumed 0
    this->charFlag = 0; // (char)0
    this->maxVal = 0xFF;
    this->vtable = &PTR_FUN_00d5f5b0;
    this->m_pNext = 0;
    this->m_pPrev = 0;
    this->value1 = in_XMM0_Da; // Provided in XMM0
    this->constant1 = _DAT_00d5780c;
    this->constant2 = _DAT_00d5cf70;
    this->constant3 = _DAT_00d5cf70;
    // Set quaternion components to the same float
    this->quat[0] = in_XMM1_Da;
    this->quat[1] = in_XMM1_Da;
    this->quat[2] = in_XMM1_Da;
    this->quat[3] = in_XMM1_Da;
    this->unkPtr2 = 0;

    // Determine new list insertion target
    EARSNode* newNext = 0;
    if (!insertFlag) {
        // When Z flag was not set: listHeadOrNull points to a structure; the node is at offset +0x48
        newNext = reinterpret_cast<EARSNode*>(reinterpret_cast<char*>(listHeadOrNull) + 0x48);
    } // else newNext remains 0

    // Insert this node into the list at newNext (if not already there)
    if (this->m_pNext != newNext) {
        if (this->m_pNext != 0) {
            FUN_004daf90(&(this->m_pNext));
            in_XMM1_Da = 0; // Clear float? This appears in original but may be a side effect.
        }
        this->m_pNext = newNext;
        if (newNext != 0) {
            this->m_pPrev = newNext->m_pNext;
            newNext->m_pNext = this;
        }
    }

    // Call base init function
    FUN_006da2b0();

    // Final assignments
    this->charFlag = 0; // repeated set
    this->copiedConst1 = this->constant1; // from +0x24
    this->copiedConst2 = _DAT_00d5780c;
    this->value2 = in_XMM1_Da; // Possibly the float from above
    return this;
}