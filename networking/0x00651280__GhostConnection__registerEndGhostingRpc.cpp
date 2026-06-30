// FUNC_NAME: GhostConnection::registerEndGhostingRpc
// Address: 0x00651280
// Initializes a static RPC registration block for GhostConnection::rpcEndGhosting.
// Prepends the block to a global linked list of RPC registrations.

struct RpcRegistrationBlock {
    void* vtable;                 // +0x00
    uint32_t flags;               // +0x04
    uint32_t field_08;            // +0x08
    uint32_t field_0C;            // +0x0C
    uint32_t field_10;            // +0x10
    uint32_t field_14;            // +0x14
    uint32_t field_18;            // +0x18
    uint32_t field_1C;            // +0x1C
    char rpcName[0x40];          // +0x20
    uint32_t field_60;            // +0x60
    uint32_t field_64;            // +0x64
    uint32_t field_68;            // +0x68
    uint32_t field_6C;            // +0x6C
    RpcRegistrationBlock* next;   // +0x70
};

// Global list head (DAT_012059ec)
extern RpcRegistrationBlock* g_rpcRegistrationHead;

// Static instance of the registration block (spans DAT_012231e8..DAT_01223258)
static RpcRegistrationBlock g_ghostEndGhostingRpc;

void __cdecl registerEndGhostingRpc(void)
{
    g_ghostEndGhostingRpc.field_60 = 0;
    g_ghostEndGhostingRpc.field_68 = 0;
    g_ghostEndGhostingRpc.field_6C = 0;
    g_ghostEndGhostingRpc.field_64 = 0;

    g_ghostEndGhostingRpc.vtable = (void*)&PTR_LAB_00e43074;   // vtable for RPC registration

    // Copy RPC name with null termination, limit to 63 chars
    strncpy(g_ghostEndGhostingRpc.rpcName, "RPC_GhostConnection_rpcEndGhosting", 0x3f);

    // Save current head to the next pointer
    g_ghostEndGhostingRpc.next = g_rpcRegistrationHead;

    // Initialize remaining fields
    g_ghostEndGhostingRpc.field_10 = 0;
    g_ghostEndGhostingRpc.field_18 = 0;
    g_ghostEndGhostingRpc.field_1C = 0;
    g_ghostEndGhostingRpc.field_08 = 0;   // actually field at +0x08 (DAT_012231f0)
    g_ghostEndGhostingRpc.field_0C = 2;   // type? (DAT_012231f4)
    g_ghostEndGhostingRpc.flags = 1;      // (DAT_012231ec)

    // Prepend block to global list
    g_rpcRegistrationHead = &g_ghostEndGhostingRpc;
}