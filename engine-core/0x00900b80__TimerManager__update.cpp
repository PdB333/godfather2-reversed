// FUNC_NAME: TimerManager::update

#include <cstdint>

// Central game timer value (float)
extern float g_currentTime;

// Forward declarations for internal helpers
float __fastcall getElapsedTime(int contextHandle);
void __fastcall cleanupTimerList(int* list);
void __fastcall notifyTimerManagerChange(int param);

// Timer entry structure (3 ints per entry)
struct TimerEntry {
    int context;      // +0x00: handle to the timed object
    int unknown;      // +0x04: not used in this function
    int timestamp;    // +0x08: recorded time when action was last processed
};

// Dynamic list of timer entries for a specific type
struct TimerList {
    TimerEntry* entriesA;   // +0x00: array for cancellation checks
    int countA;             // +0x04: number of entries in entriesA
    int padding;            // +0x08: not used (aligns to +0x0C)
    TimerEntry* entriesB;   // +0x0C: array for update checks
    int countB;             // +0x10: number of entries in entriesB
};

// Main timer manager class
class TimerManager {
public:
    // Vtable offsets (relative to this->vtable):
    // +0x18: onAllTimersComplete()
    // +0x14c: onTimerExpired(int context)
    // +0x150: onTimerUpdate(int context)
    // +0x154: onTimerCancelled(int context)

    // Member layout (offsets from this)
    uint16_t m_flags;                // +0x60: bitfield for timer state
    //  0x0400: timerUpdateFlag
    //  0x0800: timerExpiredFlag
    //  0x1000: timerCancelledFlag
    //  0x2000: allTimersDoneFlag
    //  0x3000: mask for all-timers-done check
    float m_timerThreshold;          // +0x6c: minimum interval for update (stored as int)
    float m_lastUpdateTime;          // +0x6d: time of last update (stored as int)
    TimerList* m_timerList;          // +0x74: pointer to dynamic timer lists
    uint8_t m_timerControl;          // +0x182: bitmask enabling timer types
    //  0x01: enable expired timer (vtable+0x14c)
    //  0x02: enable update timer (vtable+0x150)
    //  0x04: enable cancelled timer (vtable+0x154)

    void update();

    // Virtual functions (via vtable)
    void onAllTimersComplete() {
        (*(void (__thiscall**)(TimerManager*))(*(uintptr_t*)this + 0x18))(this);
    }
    void onTimerExpired(int context) {
        (*(void (__thiscall**)(TimerManager*, int))(*(uintptr_t*)this + 0x14c))(this, context);
    }
    void onTimerUpdate(int context) {
        (*(void (__thiscall**)(TimerManager*, int))(*(uintptr_t*)this + 0x150))(this, context);
    }
    void onTimerCancelled(int context) {
        (*(void (__thiscall**)(TimerManager*, int))(*(uintptr_t*)this + 0x154))(this, context);
    }
};

void __thiscall TimerManager::update() {
    float currentTime = g_currentTime;
    TimerList* list = m_timerList;

    if (list == nullptr) {
        // No timer list – handle static flag-based timers
        if (!(m_flags & 0x0400) && (m_flags & 0x0800) && (m_timerControl & 0x01)) {
            onTimerExpired(0);
        }
        if ((m_timerControl & 0x02) &&
            (m_flags & 0x0c00) &&
            (m_lastUpdateTime < 0.0f || m_timerThreshold <= currentTime - m_lastUpdateTime)) {
            m_lastUpdateTime = currentTime;
            onTimerUpdate(0);
        }
        if ((m_timerControl & 0x04) && (m_flags & 0x0400) && !(m_flags & 0x0800)) {
            onTimerCancelled(0);
        }
        uint16_t oldFlags = m_flags;
        m_flags = oldFlags & 0xefff; // clear 0x1000 bit
        if ((oldFlags & 0x3000) == 0x3000 && !(oldFlags & 0x2000)) {
            onAllTimersComplete();
        }
    } else {
        // Process entries in the timer lists
        int countB = list->countB;
        int countA = list->countA;

        // Process update timers (entriesB)
        if ((m_timerControl & 0x03) && countB != 0) {
            TimerEntry* entry = list->entriesB;
            for (int i = 0; i < countB; i++) {
                int context = entry->context;
                if (context != 0) {
                    int data = context - 0x48;
                    if (data != 0) {
                        float elapsed = getElapsedTime(data);
                        if (elapsed >= 0.0f) {
                            if (m_timerControl & 0x02) {
                                if (currentTime - elapsed < m_timerThreshold) {
                                    entry->timestamp = (int)elapsed;
                                } else {
                                    onTimerUpdate(data);
                                    entry->timestamp = (int)currentTime;
                                    currentTime = currentTime; // no-op (keeps fVar5)
                                }
                            }
                        } else {
                            onTimerExpired(data);
                            currentTime = currentTime; // no-op
                        }
                    }
                }
                entry++;
            }
        }

        // Process cancellation timers (entriesA)
        if ((m_timerControl & 0x04) && countA != 0) {
            TimerEntry* entry = list->entriesA;
            for (int i = 0; i < countA; i++) {
                int context = entry->context;
                if (context != 0) {
                    int data = context - 0x48;
                    if (data != 0) {
                        float elapsed = getElapsedTime(data);
                        if (elapsed < 0.0f) {
                            onTimerCancelled(data);
                        }
                    }
                }
                entry++;
            }
        }

        // If all update timers are done, fire completion callback
        if (countB == 0) {
            uint16_t oldFlags = m_flags;
            m_flags = oldFlags & 0xefff;
            if ((oldFlags & 0x3000) == 0x3000 && !(oldFlags & 0x2000)) {
                onAllTimersComplete();
            }
        }

        // Cleanup timelists (internal)
        cleanupTimerList(&list->entriesB);
        notifyTimerManagerChange(0);
    }

    // Update flags for next frame
    uint16_t newFlags = m_flags;
    if (newFlags & 0x0800) {
        newFlags |= 0x0400;
    } else {
        newFlags &= 0xfbff;
    }
    m_flags = newFlags & 0xf7ff;
}