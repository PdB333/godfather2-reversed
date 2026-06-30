// FUNC_NAME: AICarBehavior::handleEvent
// Address: 0x006b72d0
// Role: Processes various events for an AI car behavior (enter, exit, update, disable, proximity)

#include <cstdint>

// Event type constants (guessed from global symbols)
static const int kEventEnter = 0x0120e93c;    // DAT_0120e93c
static const int kEventExit = 0x0112a628;     // DAT_0112a628
static const int kEventUpdate = 0x0112a600;   // DAT_0112a600
static const int kEventDisable = 0x0112a648;  // DAT_0112a648
static const int kEventProximity = 0x0112a610; // DAT_0112a610

// External functions (stubs)
extern void processEventUnpack(void* event);                            // 0x008badd0
extern void releaseEvent(void* event);                                 // 0x004086d0
extern void* getEntity(int entityId);                                  // 0x006b0ee0
extern int createTransform();                                          // 0x006b4860
extern void setTransform(int transformX, int transformY);              // 0x006b7240
extern void releaseEventData(void* data);                              // 0x00408680
extern float calculateDistanceSquared(float* a, float* b);             // 0x00414c30

// Event data structures (inferred from usage)
struct EventEnterData {
    int entityId;    // +0x04? Actually accessed as *(int*)(param_2[1]+4) then offset 0x38
};

struct EventUpdateData {
    int entityId;    // +0x04, same
    float position[3]; // +0x08? offset 8
    float range;     // +0x0c? offset 12
    uint8_t processed; // +0x10? flag
};

void __thiscall AICarBehavior::handleEvent(int thisPtr, int* event)
{
    float fVar1;
    float* pfVar2;
    int eventType;
    float local_34[3];
    float local_28[3];
    float distanceSq;
    float rangeSq;
    uint32_t flags;
    int entityId;
    void* entity;
    void* transform;

    processEventUnpack(event);           // Unpack the event structure
    eventType = *event;                  // First field is the event type

    if (eventType == kEventEnter) {
        // Set bit 31 in flags field at offset 0x254
        *(uint32_t*)(thisPtr + 0x254) |= 0x80000000;
        releaseEvent(&kEventEnter);      // Release the event type resource

        entityId = *(int*)(thisPtr + 0x158);  // Get associated entity ID
        if (entityId != 0) {
            entity = getEntity(entityId); // Get entity pointer
            if (entity != 0) {
                transform = createTransform();
                setTransform(transform, transform); // Set up transform
            }
            // Release multiple event data structures
            releaseEventData(&kEventExit);
            releaseEventData(&kEventUpdate);
            releaseEventData(&kEventProximity);
        }
        return;
    }

    if (eventType == kEventExit) {
        // Second field of event points to more data
        int eventDataPtr = event[1];
        if (*(int*)(*(int*)(eventDataPtr + 4) + 0x38) == *(int*)(thisPtr + 0x158)) {
            transform = createTransform();
            int t2 = createTransform(transform);
            setTransform(t2, transform);
            return;
        }
    }

    if (eventType == kEventUpdate) {
        int eventDataPtr = event[1];
        if (*(int*)(*(int*)(eventDataPtr + 4) + 0x38) == *(int*)(thisPtr + 0x158)) {
            setTransform(*(int*)(eventDataPtr + 8), *(int*)(eventDataPtr + 0xc));
            return;
        }
    }

    if (eventType == kEventDisable) {
        flags = *(uint32_t*)(thisPtr + 0x254);
        if ((flags >> 0x1d & 1) != 0) {   // Check bit 29? Or bit 0x20000000? Actually shift 29 -> bit 29
            *(uint32_t*)(thisPtr + 0x254) &= 0xdfffffff; // Clear bit 29
            if (*(int**)(thisPtr + 0xf4) != 0) {
                (*(code**)(**(int**)(thisPtr + 0xf4) + 0x44))(0xf86f4484, 4); // Callback
                return;
            }
        }
    }

    if ((eventType == kEventProximity) &&
        (*(char*)(event[1] + 0x10) == '\0') &&
        (*(int*)(*(int*)(event[1] + 4) + 0x38) == *(int*)(thisPtr + 0x158)) &&
        ((~*(uint8_t*)(thisPtr + 0x254) & 1) != 0))  // Check bit 0 not set
    {
        // Distance test from base class vtable (offset -0x3c)
        void* basePtr = reinterpret_cast<char*>(thisPtr) - 0x3c;
        float* vtable = *(float**)basePtr;

        // vtable + 0xc0: get something (position?)
        float f1 = (*(vtable[0xc0]))(0);
        local_34[0] = f1;
        float f2 = (*(vtable[0xc4]))();
        if (local_34[0] < f2 * 0.5f) { // _DAT_00d5c458 is likely 0.5
            // Get position from base vtable + 0x104
            (*(vtable[0x104]))(reinterpret_cast<char*>(thisPtr) - 0x3c + 0x20, local_28); // auStack_20 = buffer
            fVar1 = *(float*)(event[1] + 0xc);
            pfVar2 = *(float**)(event[1] + 8);
            local_34[0] = *pfVar2;
            local_34[1] = pfVar2[1];
            local_34[2] = pfVar2[2];
            // calculateDistanceSquared on some aligned stack?
            distanceSq = calculateDistanceSquared(reinterpret_cast<float*>(reinterpret_cast<char*>(thisPtr) - 0x3c + 0x24), local_34); // auStack_24 = &fStack_34? Actually auStack_24 is a byte array used as output
            rangeSq = fVar1 * local_28[0]; // fStack_18 is some factor
            if (distanceSq < rangeSq * rangeSq) {
                *(uint8_t*)(event[1] + 0x10) = 1; // Mark as processed
            }
        }
    }
    return;
}