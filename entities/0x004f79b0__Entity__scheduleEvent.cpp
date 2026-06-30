// FUNC_NAME: Entity::scheduleEvent
// Address: 0x004f79b0
// Purpose: Checks if entity's GUID is non-zero, then queues an event via the EventScheduler singleton.

#include <cstdint>

class EventScheduler {
public:
    static EventScheduler* getInstance();          // FUN_004e0f60
    void lock();                                   // FUN_0051d730
    uint32_t queueEvent(int queueId, uint32_t param2, uint32_t param3); // FUN_0051c7c0
};

class Entity {
    // +0x00: uint32_t guidParts[4]; // 128-bit GUID (non-zero if valid)
public:
    uint32_t scheduleEvent(uint32_t param2, uint32_t param3) __thiscall {
        // Check if this entity has a valid GUID (all 4 parts are non-zero)
        if ((guidParts[0] == 0 && guidParts[1] == 0) && (guidParts[2] == 0 && guidParts[3] == 0)) {
            return 0;
        }

        EventScheduler* scheduler = EventScheduler::getInstance();
        if (scheduler == nullptr) {
            return 0;
        }

        int queueId = *reinterpret_cast<int*>(scheduler); // First int of scheduler singleton holds queue ID
        scheduler->lock();
        return scheduler->queueEvent(queueId, param2, param3);
    }

private:
    uint32_t guidParts[4]; // +0x00
};