// FUNC_NAME: registerGhostConnectionRPCStartGhosting
// Address: 0x00651070
// This function initializes a static RPC descriptor for the "RPC_GhostConnection_rpcStartGhosting" RPC
// and links it into the global RPC descriptor list.

struct RPCDescriptor {
    void* vtable;          // +0x00
    int field_04;          // +0x04
    int field_08;          // +0x08
    int field_0C;          // +0x0C
    int field_10;          // +0x10
    int field_14;          // +0x14
    int field_18;          // +0x18
    int field_1C;          // +0x1C
    char name[64];         // +0x20 (0x40 bytes)
    int field_60;          // +0x60
    int field_64;          // +0x64
    int field_68;          // +0x68
    int field_6C;          // +0x6C
    RPCDescriptor* next;   // +0x70
};

// Global head of RPC descriptor list (DAT_012059ec)
RPCDescriptor* gRPCHead = nullptr;

// Static instance of the descriptor (DAT_01223260)
static RPCDescriptor gGhostRPCDescriptor;

void registerGhostConnectionRPCStartGhosting(void)
{
    // Zero out fields at offsets +0x68, +0x60, +0x6C, +0x64
    gGhostRPCDescriptor.field_68 = 0;
    gGhostRPCDescriptor.field_60 = 0;
    gGhostRPCDescriptor.field_6C = 0;
    gGhostRPCDescriptor.field_64 = 0;

    // Set vtable pointer (likely to a static function table for RPC handling)
    gGhostRPCDescriptor.vtable = &PTR_LAB_00e42ffc;

    // Copy the RPC name string (max 63 characters + null)
    _strncpy(gGhostRPCDescriptor.name, "RPC_GhostConnection_rpcStartGhosting", 0x3f);

    // Link this descriptor into the global list (insert at head)
    gGhostRPCDescriptor.next = gRPCHead;

    // Set remaining fields
    gGhostRPCDescriptor.field_0C = 2;
    gGhostRPCDescriptor.field_04 = 1;

    // Update head to point to this descriptor
    gRPCHead = &gGhostRPCDescriptor;
}