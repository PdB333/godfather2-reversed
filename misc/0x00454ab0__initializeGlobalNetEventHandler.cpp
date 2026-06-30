// FUNC_NAME: initializeGlobalNetEventHandler
// Address: 0x00454ab0
// Role: Initializes the global NetEventHandler static instance and registers it in the handler chain.

struct NetEventHandler {
    void* vtable;           // +0x00
    int active;             // +0x04
    int unknown08;          // +0x08
    int unknown0C;          // +0x0C
    int unknown10;          // +0x10
    int unknown14;          // +0x14
    int unknown18;          // +0x18
    int unknown1C;          // +0x1C
    char name[64];          // +0x20
    // padding maybe
    int unknown60;          // +0x60
    int unknown64;          // +0x64
    int unknown68;          // +0x68
    int unknown6C;          // +0x6C
    NetEventHandler* next;  // +0x70  // linked list next pointer
};

// Static global instance (address 0x0120e980)
static NetEventHandler g_netEventHandler;

// Global head of event handler list (address 0x012059ec)
extern NetEventHandler* g_netEventHandlerHead;

void initializeGlobalNetEventHandler(void)
{
    // Zero out fields at +0x60 through +0x6C
    g_netEventHandler.unknown60 = 0;
    g_netEventHandler.unknown68 = 0;
    g_netEventHandler.unknown6C = 0;
    g_netEventHandler.unknown64 = 0;

    // Set vtable pointer to global vtable (likely for NetEventHandler class)
    g_netEventHandler.vtable = &PTR_LAB_00e318c4;

    // Copy class name into name buffer (size 0x3f = 63 chars + null)
    _strncpy(g_netEventHandler.name, "NetEventHandler", 0x3f);

    // Link this instance into the global handler chain (insert at head)
    g_netEventHandler.next = g_netEventHandlerHead;

    // Clear additional fields
    g_netEventHandler.unknown0C = 0;
    g_netEventHandler.unknown08 = 0;
    g_netEventHandler.unknown10 = 0;
    g_netEventHandler.unknown14 = 0;
    g_netEventHandler.unknown18 = 0;
    g_netEventHandler.unknown1C = 0;

    // Mark as active
    g_netEventHandler.active = 1;

    // Update global head to point to this instance
    g_netEventHandlerHead = &g_netEventHandler;
}