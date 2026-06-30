// FUNC_NAME: DebugManager::processEvent
// Address: 0x004df270
// Checks if an incoming debug event ID matches the currently registered global debug event.
// If matched, sets a flag on the debug object and dispatches the event handler.

#include <cstdint>

// Forward declarations
void* DebugManager_getObject();                     // FUN_004e0d30
void DebugManager_registerCallback(const char*);    // FUN_004d9500
void DebugManager_handleEvent(void*, uint32_t, uint32_t, uint32_t); // FUN_004df210

// Global debug state (from .data section)
extern uint32_t gDebugRegisteredFlag;   // _DAT_012278ac
extern int32_t gDebugEventGuid[4];      // DAT_0122789c, DAT_012278a0, DAT_012278a4, DAT_012278a8

uint32_t* DebugManager::processEvent(
    uint32_t* result,
    int32_t* eventId,
    uint32_t param3,
    uint32_t param4,
    uint32_t param5)
{
    // Check if the event ID contains any non-zero component
    if (eventId[0] != 0 || eventId[1] != 0 || eventId[2] != 0 || eventId[3] != 0)
    {
        void* pObjPtr = DebugManager_getObject();
        if (pObjPtr != nullptr)
        {
            // Dereference to get the actual debug object address
            uint32_t debugObject = *(uint32_t*)pObjPtr;
            if (debugObject != 0)
            {
                // Register the debug callback GUID on first use
                if ((gDebugRegisteredFlag & 1) == 0)
                {
                    gDebugRegisteredFlag |= 1;
                    DebugManager_registerCallback("{BDFF6379-6379-BDFF-7963-FFBD7963FFBD}");
                }

                // Compare the incoming event ID with the stored debug event ID
                if (gDebugEventGuid[0] == eventId[0] &&
                    gDebugEventGuid[1] == eventId[1] &&
                    gDebugEventGuid[2] == eventId[2] &&
                    gDebugEventGuid[3] == eventId[3])
                {
                    // Set bit 5 (0x20) at offset 0x14 of the debug object
                    *(uint32_t*)(debugObject + 0x14) |= 0x20;
                }

                // Dispatch the event to the handler
                DebugManager_handleEvent(reinterpret_cast<void*>(debugObject), param3, param4, param5);
            }
        }
        return result; // Return unchanged result pointer
    }

    // Event ID is all zeros – clear result and return
    *result = 0;
    return result;
}