// FUNC_NAME: DebugNamedNode::DebugNamedNode
// Address: 0x008a7c30
// Role: Constructor for a named debug node that inserts itself into a global linked list.
//       Stores a 63-character name and three DWORD parameters, zeros several fields,
//       and links to previous head of the global list.

// Global linked list head pointer
static DebugNamedNode* g_debugNodeListHead = nullptr;

class DebugNamedNode {
public:
    // vtable pointer (RTTI) at +0x00
    void* vtable;

    uint32_t paramA; // +0x04 - third constructor argument
    uint32_t paramC; // +0x08 - fifth constructor argument (note: stored before paramB)
    uint32_t paramB; // +0x0C - fourth constructor argument
    uint32_t pad1;   // +0x10 - zeroed
    uint32_t pad2;   // +0x14 - zeroed
    uint32_t pad3;   // +0x18 - zeroed
    uint32_t pad4;   // +0x1C - zeroed

    char name[64];   // +0x20 - null-terminated string, max 63 chars

    // padding/unused region from +0x60 to +0x6F (not shown, but next pointer is at +0x70)

    DebugNamedNode* next; // +0x70 - pointer to previous head, forming a linked list

    // Constructor
    // param_2: name string (copied to name buffer)
    // param_3: value stored at +0x04
    // param_4: value stored at +0x0C
    // param_5: value stored at +0x08
    __thiscall DebugNamedNode(const char* param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5) {
        // Call base class constructor (likely sets vtable pointer and initializes other base fields)
        FUN_0064cc90();

        // Set vtable pointer
        this->vtable = &PTR_LAB_00d79be8;

        // Copy name (max 63 chars + null)
        strncpy(this->name, param_2, 0x3F);
        this->name[0x3F] = '\0'; // ensure null termination

        // Assign parameters to fields (note the order: paramC gets fifth arg)
        this->paramA = param_3;
        this->paramB = param_4;
        this->paramC = param_5;

        // Zero out 4 DWORDs at +0x10 through +0x1C
        this->pad1 = 0;
        this->pad2 = 0;
        this->pad3 = 0;
        this->pad4 = 0;

        // Link this node into the global linked list
        this->next = g_debugNodeListHead;
        g_debugNodeListHead = this;
    }
};