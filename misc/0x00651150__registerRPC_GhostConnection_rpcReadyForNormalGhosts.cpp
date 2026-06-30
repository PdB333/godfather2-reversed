// FUNC_NAME: registerRPC_GhostConnection_rpcReadyForNormalGhosts

// Initializes a static RPC entry for GhostConnection's rpcReadyForNormalGhosts.
// Prepends this entry to a global linked list of RPC registrations (DAT_012059ec).
void registerRPC_GhostConnection_rpcReadyForNormalGhosts(void)
{
    // Zero out fields: +0x60, +0x64, +0x68, +0x6C
    g_rpcEntry + 0x60 = 0;  // _DAT_01223340
    g_rpcEntry + 0x64 = 0;  // _DAT_01223338
    g_rpcEntry + 0x68 = 0;  // _DAT_01223344
    g_rpcEntry + 0x6C = 0;  // _DAT_0122333c

    // +0x00: pointer to RPC class vtable/type info (PTR_LAB_00e43030)
    g_rpcEntry + 0x00 = &PTR_LAB_00e43030;

    // +0x20: copy the RPC name string (63 bytes max)
    _strncpy(g_rpcEntry + 0x20, "RPC_GhostConnection_rpcReadyForNormalGhosts", 0x3f);

    // +0x70: save previous global head (linking this node)
    g_rpcEntry + 0x70 = g_RPCListHead;  // _DAT_01223348 = DAT_012059ec

    // +0x08: ? (0)
    g_rpcEntry + 0x08 = 0;  // _DAT_012232e0
    // +0x10: ? (0)
    g_rpcEntry + 0x10 = 0;  // _DAT_012232e8
    // +0x14: ? (0)
    g_rpcEntry + 0x14 = 0;  // _DAT_012232ec
    // +0x18: ? (0)
    g_rpcEntry + 0x18 = 0;  // _DAT_012232f0
    // +0x1C: ? (0)
    g_rpcEntry + 0x1C = 0;  // _DAT_012232f4
    // +0x0C: ? (2)
    g_rpcEntry + 0x0C = 2;  // _DAT_012232e4
    // +0x04: ? (1)
    g_rpcEntry + 0x04 = 1;  // _DAT_012232dc

    // Update global head to point to this new entry
    g_RPCListHead = g_rpcEntry;  // DAT_012059ec = &DAT_012232d8
}