// FUNC_NAME: GhostConnection::registerRpcStartGhosting

// Structure representing an RPC descriptor used for network message registration.
// Offsets relative to base address are documented in comments.
struct RpcDescriptor {
    // +0x00: Function pointer to the RPC handler
    void (*callback)();
    // +0x04: Flags or type identifier (1 in this registration)
    int field_0x04;
    // +0x08: Unused (0)
    int field_0x08;
    // +0x0C: Some version or sequence (2 in this registration)
    int field_0x0C;
    // +0x10: Reserved (0)
    int field_0x10;
    // +0x14: Reserved (0)
    int field_0x14;
    // +0x18: Reserved (0)
    int field_0x18;
    // +0x1C: Reserved (0)
    int field_0x1C;
    // +0x20: Null-terminated RPC name (up to 63 characters, padded to 64 bytes)
    char name[64];
    // +0x60: Additional state (0)
    int field_0x60;
    // +0x64: Additional state (0)
    int field_0x64;
    // +0x68: Additional state (0)
    int field_0x68;
    // +0x6C: Additional state (0)
    int field_0x6C;
    // +0x70: Pointer to next descriptor in the registration list
    RpcDescriptor* next;
};

// Static global descriptor instance for the "RPC_GhostConnection_rpcStartGhosting" message
// Located at address 0x01223260
static RpcDescriptor s_ghostStartRpcDescriptor;

// Head of the linked list of all registered RPC descriptors (global variable at 0x012059EC)
extern RpcDescriptor* g_RpcDescriptorList;

// Registers the RPC for starting ghosting on GhostConnection.
// This function is called during startup to initialize the descriptor and link it into the global list.
void registerRpcStartGhosting(void)
{
    // Zero out the state fields at offsets +0x60 to +0x6C (four ints)
    s_ghostStartRpcDescriptor.field_0x60 = 0;
    s_ghostStartRpcDescriptor.field_0x64 = 0;
    s_ghostStartRpcDescriptor.field_0x68 = 0;
    s_ghostStartRpcDescriptor.field_0x6C = 0;

    // Set the callback pointer to the actual handler function
    // PTR_LAB_00e42ffc is a known function address (likely static or extern)
    s_ghostStartRpcDescriptor.callback = (void (*)())PTR_LAB_00e42ffc;

    // Copy the RPC name into the descriptor's name buffer (max 63 chars + null)
    strncpy(s_ghostStartRpcDescriptor.name, "RPC_GhostConnection_rpcStartGhosting", 0x3F);

    // Set the next pointer to the current head of the registration list
    // Then update the head to point to this descriptor (effectively prepending)
    s_ghostStartRpcDescriptor.next = g_RpcDescriptorList;
    g_RpcDescriptorList = &s_ghostStartRpcDescriptor;

    // Initialize the remaining descriptor fields
    s_ghostStartRpcDescriptor.field_0x04 = 1;    // Mark as active or specific type
    s_ghostStartRpcDescriptor.field_0x08 = 0;
    s_ghostStartRpcDescriptor.field_0x0C = 2;    // Version or priority
    s_ghostStartRpcDescriptor.field_0x10 = 0;
    s_ghostStartRpcDescriptor.field_0x14 = 0;
    s_ghostStartRpcDescriptor.field_0x18 = 0;
    s_ghostStartRpcDescriptor.field_0x1C = 0;

    return;
}