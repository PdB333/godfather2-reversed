// FUNC_NAME: initGlobalRPCEventHandler_SurrenderedAuthority

#include <string.h> // for strncpy

// RPC event handler struct based on offsets from 0x0120ea00
// +0x00: void* vtable
// +0x04: int field_04 (maybe reference count or enabled flag)
// +0x08: int field_08
// +0x0C: int handlerType (set to 2)
// +0x10: int field_10
// +0x14: int field_14
// +0x18: int field_18
// +0x1C: int field_1C
// +0x20: char name[0x40] (64 bytes, event identifier string)
// +0x60: int field_60
// +0x64: int field_64
// +0x68: int field_68
// +0x6C: int field_6C
// +0x70: RPCEventHandler* next (linked list pointer)

struct RPCEventHandler {
    void* vtable;               // +0x00
    int field_04;               // +0x04
    int field_08;               // +0x08
    int handlerType;            // +0x0C
    int field_10;               // +0x10
    int field_14;               // +0x14
    int field_18;               // +0x18
    int field_1C;               // +0x1C
    char name[0x40];            // +0x20
    int field_60;               // +0x60
    int field_64;               // +0x64
    int field_68;               // +0x68
    int field_6C;               // +0x6C
    RPCEventHandler* next;      // +0x70
};

// Global singleton instance at 0x0120ea00
#define g_rpcEventHandler_SurrenderedAuthority ((RPCEventHandler*)0x0120ea00)
// Global head of registered RPC event handler list at 0x012059ec
#define g_rpcEventHandlerListHead ((RPCEventHandler**)0x012059ec)

// Constructor-like static initializer for the SurrenderedAuthority RPC handler.
// This function is called at startup to create and register the global handler.
void initGlobalRPCEventHandler_SurrenderedAuthority(void)
{
    RPCEventHandler* handler = g_rpcEventHandler_SurrenderedAuthority;

    // Clear trailing fields (likely padding or unused members)
    handler->field_60 = 0;
    handler->field_64 = 0;
    handler->field_68 = 0;
    handler->field_6C = 0;

    // Set virtual function table
    handler->vtable = (void*)&PTR_LAB_00e31908;

    // Copy the RPC event name string (truncated to 63 chars + null)
    strncpy(handler->name, "RPCEV_NetEventHandler_RPC_SurrenderedAuthority", 0x3f);

    // Insert at front of global linked list
    handler->next = *g_rpcEventHandlerListHead;  // +0x70: old head

    // Zero remaining fields
    handler->field_08 = 0;
    handler->field_10 = 0;
    handler->field_14 = 0;
    handler->field_18 = 0;
    handler->field_1C = 0;

    // Set handler type to 2 and mark as active (field_04 = 1)
    handler->handlerType = 2;   // +0x0C
    handler->field_04 = 1;      // +0x04

    // Update global list head to point to this new handler
    *g_rpcEventHandlerListHead = handler;
}