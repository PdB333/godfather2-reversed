// FUNC_NAME: RPC_AuthorityTransferRequest::initStatic

#include <cstring>

// Forward declaration for the vtable symbol (defined elsewhere)
extern void* s_RPC_AuthorityTransferRequest_vtable; // from PTR_LAB_00e33638

// Structure for an RPC event descriptor (size unknown, offsets relative to base at 0x0120ebf8)
struct RPC_EventDescriptor {
    void* vtable;                                // +0x00
    uint32_t field_0x04;                         // +0x04 (init to 1)
    uint32_t field_0x08;                         // +0x08 (init to 0)
    uint32_t field_0x0C;                         // +0x0C (init to 2)
    uint32_t field_0x10;                         // +0x10 (init to 0)
    uint32_t field_0x14;                         // +0x14 (init to 0)
    uint32_t field_0x18;                         // +0x18 (init to 0)
    uint32_t field_0x1C;                         // +0x1C (init to 0)
    char name[0x40];                             // +0x20 (string buffer, max length 0x3F)
    uint32_t field_0x60;                         // +0x60 (init to 0)
    uint32_t field_0x64;                         // +0x64 (init to 0)
    uint32_t field_0x68;                         // +0x68 (init to 0)
    uint32_t field_0x6C;                         // +0x6C (init to 0)
    RPC_EventDescriptor* next;                   // +0x70 (linked list pointer to next event)
};

// Global instance of the AuthorityTransferRequest event descriptor
static RPC_EventDescriptor g_authorityTransferRequestEvent;

// Head of the global linked list of RPC events (previously DAT_012059ec)
static RPC_EventDescriptor* g_rpcEventListHead;

// Static initializer that registers the RPC authority transfer request event
void RPC_AuthorityTransferRequest::initStatic()
{
    // Initialize vtable and fields
    g_authorityTransferRequestEvent.vtable = &s_RPC_AuthorityTransferRequest_vtable;
    g_authorityTransferRequestEvent.field_0x04 = 1;
    g_authorityTransferRequestEvent.field_0x08 = 0;
    g_authorityTransferRequestEvent.field_0x0C = 2;
    g_authorityTransferRequestEvent.field_0x10 = 0;
    g_authorityTransferRequestEvent.field_0x14 = 0;
    g_authorityTransferRequestEvent.field_0x18 = 0;
    g_authorityTransferRequestEvent.field_0x1C = 0;

    // Set the event name
    std::strncpy(g_authorityTransferRequestEvent.name,
                 "RPCEV_NetReflectable_RPC_AuthorityTransferRequest",
                 0x3F);

    // Initialize remaining fields to zero
    g_authorityTransferRequestEvent.field_0x60 = 0;
    g_authorityTransferRequestEvent.field_0x64 = 0;
    g_authorityTransferRequestEvent.field_0x68 = 0;
    g_authorityTransferRequestEvent.field_0x6C = 0;

    // Insert this event at the head of the global list
    g_authorityTransferRequestEvent.next = g_rpcEventListHead;
    g_rpcEventListHead = &g_authorityTransferRequestEvent;
}