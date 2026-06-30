// FUNC_NAME: RpcEvent::registerAuthorityTransferResponseDeniedEvent
#include <cstring>

// Structure for an RPC event descriptor (size ~0x74 bytes)
// Fields are based on observed assignments at global addresses.
// Actual layout may vary; offsets are documented in comments.
struct RpcEvent {
    void* vtable;                         // +0x00
    int field_0x04;                       // +0x04 (set to 0)
    int field_0x08;                       // +0x08 (set to 0)
    int flags;                            // +0x0C (set to 1)
    int field_0x10;                       // +0x10 (set to 0)
    int version;                          // +0x14 (set to 2)
    int field_0x18;                       // +0x18 (set to 0)
    int field_0x1C;                       // +0x1C (set to 0)
    int field_0x20;                       // +0x20 (set to 0)
    int field_0x24;                       // +0x24 (set to 0)
    char name[63];                        // +0x28
    // Padding and additional fields follow:
    int field_0x60;                       // +0x60 (set to 0)
    int field_0x64;                       // +0x64 (set to 0)
    int field_0x68;                       // +0x68 (set to 0)
    int field_0x6C;                       // +0x6C (set to 0)
    RpcEvent* next;                       // +0x70 (linked list)
};

// Global linked list head for registered RPC events
// Address: 0x012059ec
static RpcEvent* g_pRpcEventListHead;

// Static instance of the RPC event descriptor for this specific event
// Address: 0x0120eb08
static RpcEvent s_rpcEvent;

void RpcEvent::registerAuthorityTransferResponseDeniedEvent()
{
    // Initialize the static event descriptor
    s_rpcEvent.vtable        = reinterpret_cast<void*>(0x00e33618); // VTable for RpcEvent
    s_rpcEvent.field_0x04    = 0;
    s_rpcEvent.field_0x08    = 0;
    s_rpcEvent.flags         = 1;
    s_rpcEvent.field_0x10    = 0;
    s_rpcEvent.version       = 2;
    s_rpcEvent.field_0x18    = 0;
    s_rpcEvent.field_0x1C    = 0;
    s_rpcEvent.field_0x20    = 0;
    s_rpcEvent.field_0x24    = 0;
    strncpy(s_rpcEvent.name, "RPCEV_NetReflectable_RPC_AuthorityTransferResponseDenied", 63);
    s_rpcEvent.field_0x60    = 0;
    s_rpcEvent.field_0x64    = 0;
    s_rpcEvent.field_0x68    = 0;
    s_rpcEvent.field_0x6C    = 0;

    // Link into the global list (singly linked, new node becomes head)
    s_rpcEvent.next = g_pRpcEventListHead;
    g_pRpcEventListHead = &s_rpcEvent;
}