// FUNC_NAME: GlobalTimerSystem::updateTimerSlots
// Address: 0x0043bee0
// Decrements timer counters on all active slots (11 slots, each 28 bytes).
// Slots are part of a global timer system structure at DAT_01223414.
// When a timer reaches zero and a related flag is zero, the slot is marked inactive (id = -1).

struct TimerSlot {
    int id;            // +0x00 Slot identifier, -1 when unused
    int timerCount;    // +0x04 Counter to decrement each frame
    int field_0x08;    // +0x08 Unknown padding
    int field_0x0c;    // +0x0C Unknown padding
    int flag;          // +0x10 Flag indicating whether timer is still needed
};

struct TimerSystem {
    int field_0x00;            // +0x00 Unknown base field
    TimerSlot slots[11];       // +0x04 Array of 11 timer slots (0x1c bytes each)
};

// Global pointer to the timer system
TimerSystem* g_pTimerSystem = (TimerSystem*)DAT_01223414;

void GlobalTimerSystem::updateTimerSlots(void)
{
    if (!g_pTimerSystem) {
        return;
    }

    const int numSlots = 11;
    TimerSlot* slots = g_pTimerSystem->slots; // offset 0x04

    for (int i = 0; i < numSlots; i++) {
        TimerSlot* slot = &slots[i];
        if (slot->id == -1) { // check if slot is active
            continue;
        }
        if (slot->timerCount == 0) {
            continue;
        }

        slot->timerCount--;
        if (slot->timerCount == 0 && slot->flag == 0) {
            slot->id = -1; // reset slot for reuse
        }
    }
}