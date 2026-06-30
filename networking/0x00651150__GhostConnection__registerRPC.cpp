// FUNC_NAME: GhostConnection::registerRPC
// Address: 0x00651150
// Initializes and registers a static RPC descriptor for GhostConnection's rpcReadyForNormalGhosts

struct RPCDescriptor {
    void* handler;      // +0x00
    int field4;         // +0x04
    int field8;         // +0x08
    int fieldC;         // +0x0C
    int field10;        // +0x10
    int field14;        // +0x14
    int field18;        // +0x18
    int field1C;        // +0x1C
    char name[0x40];    // +0x20 (actually 0x3f bytes used)
    int field60;        // +0x60
    int field64;        // +0x64
    int field68;        // +0x68
    int field6C;        // +0x6C
    void* next;         // +0x70 (linked list next)
};

extern void* DAT_012059ec; // global head of RPC descriptor list

static RPCDescriptor* const g_rpcDesc = (RPCDescriptor*)0x012232d8;

void GhostConnection::registerRPC() {
    // Initialize descriptor fields
    g_rpcDesc->handler = (void*)0x00e43030; // PTR_LAB_00e43030
    g_rpcDesc->field4 = 1;
    g_rpcDesc->field8 = 0;
    g_rpcDesc->fieldC = 2;
    g_rpcDesc->field10 = 0;
    g_rpcDesc->field14 = 0;
    g_rpcDesc->field18 = 0;
    g_rpcDesc->field1C = 0;
    
    // Copy RPC name (buffer size 0x40, but strncpy uses 0x3f)
    _strncpy(g_rpcDesc->name, "RPC_GhostConnection_rpcReadyForNormalGhosts", 0x3f);
    
    // Zero out remaining fields
    g_rpcDesc->field60 = 0;
    g_rpcDesc->field64 = 0;
    g_rpcDesc->field68 = 0;
    g_rpcDesc->field6C = 0;
    
    // Link this descriptor into the global RPC list
    g_rpcDesc->next = DAT_012059ec; // save previous head
    DAT_012059ec = g_rpcDesc;        // update head to this descriptor
}