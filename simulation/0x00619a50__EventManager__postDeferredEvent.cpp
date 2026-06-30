// FUNC_NAME: EventManager::postDeferredEvent
// Address: 0x00619a50
// Role: Stores event parameters into global state and conditionally processes the event.
//       Used to defer function calls with up to 5 parameters plus saved registers (EAX, ESI, XMM0).
//       The actual event processing is done by processEvent once the system is ready.

#include <cstdint>

// Global storage for pending event parameters
static uint32_t gPendingEvent_param1;   // 0x0112781c
static uint32_t gPendingEvent_param2;   // 0x01127808
static uint32_t gPendingEvent_param3;   // 0x01127834
static uint32_t gPendingEvent_param4;   // 0x01127838
static uint32_t gPendingEvent_param5;   // 0x0112783c
static uint32_t gPendingEvent_eax;      // 0x01127814
static uint32_t gPendingEvent_esi;      // 0x01127818
static uint32_t gPendingEvent_xmm0;     // 0x01127830

// Global state pointers and IDs
static void* gExpectedPointer;          // 0x012058e8 (expected to equal &gSomeStructure)
static void** gSomeStructurePtrPtr;     // 0x01127760 (address of a pointer)
static uint32_t gSomeID1;               // 0x01127774 (event type or identifier)
static uint32_t gSomeID2;               // 0x01127884 (another identifier, must equal gSomeID1)
static uint32_t gEventType;             // 0x01127864 (subtype or additional parameter)

// Flags indicating slots to release before processing
static uint32_t gSlotToRelease1;        // 0x01127858
static uint32_t gSlotToRelease2;        // 0x0112785c
static uint32_t gSlotToRelease3;        // 0x01127860
static uint32_t gSlotToRelease4;        // 0x01127870

// Forward declarations
void releaseResource(uint32_t handle);  // 0x006063b0
void processEvent(uint32_t id1, uint32_t eventType, void* data); // 0x0060add0

void __cdecl EventManager::postDeferredEvent(
    uint32_t param1,
    uint32_t param2,
    uint32_t param3,
    uint32_t param4,
    uint32_t param5)
{
    // Store all parameters into global state
    gPendingEvent_param1 = param1;
    gPendingEvent_param2 = param2;
    gPendingEvent_param3 = param3;
    gPendingEvent_param4 = param4;
    gPendingEvent_param5 = param5;

    // Capture current register values (assumed to be set by caller)
    // In x86 calling convention, these may contain extra context
    gPendingEvent_eax = __eax;      // saved EAX register
    gPendingEvent_esi = __esi;      // saved ESI register
    gPendingEvent_xmm0 = __xmm0;    // saved XMM0 register (possibly float)

    // Check if the system is ready to process the event immediately
    // The comparison between gExpectedPointer and &gSomeStructurePtrPtr
    // verifies that the event system has been initialized to the expected state.
    if (gExpectedPointer == reinterpret_cast<void*>(&gSomeStructurePtrPtr) &&
        gSomeID1 == gSomeID2)       // ensure the event type identifier is consistent
    {
        // Release any previously allocated resources held in the slot variables
        if (gSlotToRelease1 != 0)
            releaseResource(gSlotToRelease1);
        if (gSlotToRelease2 != 0)
            releaseResource(gSlotToRelease2);
        if (gSlotToRelease3 != 0)
            releaseResource(gSlotToRelease3);
        if (gSlotToRelease4 != 0)
            releaseResource(gSlotToRelease4);

        // Process the stored event now, passing the ID, event type, and pointer to the stored XMM0 value
        processEvent(gSomeID1, gEventType, &gPendingEvent_xmm0);
    }
    // If not ready, the event remains stored in global state for later processing
    // (likely called again from the main loop or network tick)
}