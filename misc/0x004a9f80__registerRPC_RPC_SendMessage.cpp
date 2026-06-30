// FUNC_NAME: registerRPC_RPC_SendMessage

// Structure for an RPC entry in the linked list
struct RPCEntry {
    RPCEntry* pNext;           // +0x00
    uint32_t  flags;           // +0x04 (set to 1)
    uint32_t  typeOrSize;      // +0x08 (set to 2)
    uint32_t  unknown0C;       // +0x0C
    uint32_t  savedHead;       // +0x10 (previous list head)
    uint32_t  unknown14;       // +0x14
    uint32_t  unknown18;       // +0x18
    uint32_t  unknown1C;       // +0x1C
    char      name[0x40];      // +0x20 (null-terminated, max 0x3F chars)
    // +0x60 and beyond are global flags not part of this structure
};

// Global pointers and flags (from data sections)
extern RPCEntry* g_pRPCListHead;          // DAT_012059ec
extern uint32_t  g_RPCFlags_01218008;     // +0x60 region
extern uint32_t  g_RPCFlags_01218000;
extern uint32_t  g_RPCFlags_0121800c;
extern uint32_t  g_RPCFlags_01218004;

// The static RPC entry for "RPC_RPC_SendMessage"
static RPCEntry g_RPCEntry_SendMessage;   // at 0x01217fa0

// Forward declaration of the default next pointer (vtable or list head)
extern RPCEntry* g_DefaultRPCLink;        // PTR_LAB_00e35644

void registerRPC_RPC_SendMessage(void)
{
    // Clear global RPC control flags
    g_RPCFlags_01218008 = 0;
    g_RPCFlags_01218000 = 0;
    g_RPCFlags_0121800c = 0;
    g_RPCFlags_01218004 = 0;

    // Initialize the static entry
    g_RPCEntry_SendMessage.pNext      = g_DefaultRPCLink;
    strncpy(g_RPCEntry_SendMessage.name, "RPC_RPC_SendMessage", 0x3F);

    // Save the current list head into the entry's savedHead field
    g_RPCEntry_SendMessage.savedHead  = (uint32_t)g_pRPCListHead;

    // Zero out the remaining unknown fields
    g_RPCEntry_SendMessage.unknown0C  = 0;
    g_RPCEntry_SendMessage.unknown14  = 0;
    g_RPCEntry_SendMessage.unknown18  = 0;
    g_RPCEntry_SendMessage.unknown1C  = 0;

    // Set entry type and flags
    g_RPCEntry_SendMessage.typeOrSize = 2;
    g_RPCEntry_SendMessage.flags      = 1;

    // Prepend this entry to the linked list
    g_pRPCListHead = &g_RPCEntry_SendMessage;
}