// FUNC_NAME: initNetReflectableRPCAuthorityTransferResponseGranted

// This function initializes a static descriptor for the network RPC event
// "RPCEV_NetReflectable_RPC_AuthorityTransferResponseGranted". It sets up a
// linked list node in the global RPC descriptor registry.

#include <cstring>

// Descriptor structure for a registered RPC event in the net reflection system.
// Offsets are relative to the base address of the object (0x0120eb80).
struct RPCDescriptor {
    void* vtable;               // +0x00: pointer to the class vtable
    int field04;                // +0x04: unknown (set to 1)
    int field08;                // +0x08: unknown (set to 2)
    int field0C;                // +0x0C: unknown (set to 0)
    int field10;                // +0x10: unknown (set to 0)
    int field14;                // +0x14: unknown (set to 0)
    int field18;                // +0x18: unknown (set to 0)
    int field1C;                // +0x1C: unknown (set to 0)
    char name[0x40];            // +0x20: string identifier for the RPC event (max 63+null)
    int field60;                // +0x60: unknown (set to 0)
    int field64;                // +0x64: unknown (set to 0)
    int field68;                // +0x68: unknown (set to 0)
    int field6C;                // +0x6C: unknown (set to 0)
    RPCDescriptor* next;        // +0x70: pointer to the next descriptor in the global list
};

// Global head pointer for the RPC descriptor linked list (previously DAT_012059ec)
extern RPCDescriptor* g_RPCDescriptorListHead;

// Static instance of the descriptor for this RPC event (at address 0x0120eb80)
extern RPCDescriptor g_AuthorityTransferResponseGrantedDescriptor;

// ----------------------------------------------------------------------------
void initNetReflectableRPCAuthorityTransferResponseGranted()
{
    // Zero out the fields at offsets +0x60 through +0x6C
    g_AuthorityTransferResponseGrantedDescriptor.field60 = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field64 = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field68 = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field6C = 0;

    // Set the virtual function table pointer (PTR_LAB_00e33630)
    g_AuthorityTransferResponseGrantedDescriptor.vtable = &PTR_LAB_00e33630;

    // Copy the RPC event name into the descriptor
    strncpy(g_AuthorityTransferResponseGrantedDescriptor.name,
            "RPCEV_NetReflectable_RPC_AuthorityTransferResponseGranted",
            0x3f);

    // Link the descriptor into the global list:
    //   1. Save the current head as 'next'
    g_AuthorityTransferResponseGrantedDescriptor.next = g_RPCDescriptorListHead;

    //   2. Set fields at +0x04 through +0x1C
    g_AuthorityTransferResponseGrantedDescriptor.field04 = 1;
    g_AuthorityTransferResponseGrantedDescriptor.field08 = 2;
    g_AuthorityTransferResponseGrantedDescriptor.field0C = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field10 = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field14 = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field18 = 0;
    g_AuthorityTransferResponseGrantedDescriptor.field1C = 0;

    //   3. Update the global head to point to this descriptor
    g_RPCDescriptorListHead = &g_AuthorityTransferResponseGrantedDescriptor;
}