// FUNC_NAME: EventDispatcher::notifyListeners
// Address: 0x006bed40
// Role: Iterates over a list of listener objects and dispatches an event to each.
// Uses a temporary linked list node (likely for scope-bound cleanup of a pool allocation).

#include <cstdint>

// Forward declarations for external functions
int32_t __stdcall FUN_00791300(void);    // Possibly allocates a temporary node from a pool
void FUN_00408bf0(void* eventData, void* sender, int32_t unk); // Dispatches event
void FUN_004daf90(void** node);           // Removes a temporary node from its list

// Known globals (from the binary)
extern uint32_t DAT_0112ad8c;      // Possibly event type or some constant
extern uint32_t DAT_01205228;      // Another constant

// VTable pointer for the event data structure (likely part of a larger class)
extern void* PTR_FUN_00d5dbbc;    // VTable of the event notification object

// Structure representing a list of event listeners.
// +0x00: Array of pointers to listener objects (each 4 bytes)
// +0x04: Count of listeners in the array
struct ListenerList {
    void** listeners; // +0x00
    int32_t count;    // +0x04
};

// Temporary structure used for event dispatching (size ~0x30 bytes)
// Laid out on the stack; the leading DWORD is a type tag.
struct EventNotification {
    uint32_t typeTag;      // +0x00: DAT_0112ad8c (probably event ID)
    void** unknown1;       // +0x04: pointer to a local pointer field (self-reference)
    uint8_t padding1[4];   // +0x08: aligns next field
    void* vtablePtr;       // +0x0C: points to PTR_FUN_00d5dbbc
    uint32_t eventId;      // +0x10: 0xc1e565d0 (GUID-like)
    int32_t field14;       // +0x14: unused? 0 initially
    int32_t field18;       // +0x18: used for temporary node manipulation
    uint32_t field1C;      // +0x1C: 0
    uint32_t field20;      // +0x20: 0
    uint32_t field24;      // +0x24: 0
    uint8_t padding2[4];   // +0x28
    uint32_t field2C;      // +0x2C: DAT_01205228
};

void __thiscall EventDispatcher::notifyListeners(void* thisObj, ListenerList* list)
{
    uint32_t index = 0;
    
    // Iterate over all listeners in the list
    if (list->count != 0) {
        do {
            // Get the current listener object (if non-null)
            void* listener = list->listeners[index];
            if (listener != nullptr) {
                // Some kind of initialisation / check
                if (FUN_00791300() != 0) {
                    // Allocate a temporary node from a pool
                    void* tempNode = (void*)FUN_00791300();
                    
                    // Build the event notification structure on the stack
                    EventNotification eventData; // size ~0x30
                    eventData.typeTag = DAT_0112ad8c;
                    eventData.unknown1 = (void**)&eventData.vtablePtr; // points to vtablePtr field
                    eventData.vtablePtr = (void*)&PTR_FUN_00d5dbbc;
                    eventData.eventId = 0xc1e565d0;
                    eventData.field18 = 0;
                    eventData.field1C = 0;
                    eventData.field20 = 0;
                    eventData.field24 = 0;
                    eventData.field2C = DAT_01205228;
                    
                    // Prepare the temporary node:
                    // If tempNode is non-null, advance to offset 0x48 (node body)
                    if (tempNode != nullptr) {
                        tempNode = (char*)tempNode + 0x48;
                    }
                    
                    // If tempNode is valid, initialise its +4 field to point to itself
                    // (this likely inserts the node into a linked list; the node is on the stack)
                    if (tempNode != nullptr) {
                        eventData.field14 = *(int32_t*)((char*)tempNode + 4);
                        *(int32_t*)((char*)tempNode + 4) = (int32_t)&tempNode;
                    }
                    
                    // Compute the sender field: from this object offset +0x3C, or null if this is null
                    void* sender = (thisObj != nullptr) ? (void*)((char*)thisObj + 0x3C) : nullptr;
                    
                    // Dispatch the event (call with pointer to eventData, sender, and a zero)
                    FUN_00408bf0(&eventData, sender, 0);
                    
                    // If we initialised a tempNode, remove it from its list
                    if (tempNode != nullptr) {
                        FUN_004daf90(&tempNode);
                    }
                }
            }
            index++;
        } while (index < (uint32_t)list->count);
    }
}