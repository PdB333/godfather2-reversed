// FUNC_NAME: MissionPhaseTimer::updateTimer
// 0x005e8860 - Updates a two-phase timer, firing events when each phase's duration elapses.
// Fields:
//   +0x26c: m_bEnabled (int, bool) - timer enabled
//   +0x281: m_bPhase1Complete (byte) - phase 1 completed flag
//   +0x484: m_bPhase1Active (int, bool) - phase 1 is active
//   +0x1cc: m_timerObject (int) - handle to timer object (used with time manager)
//   +0x270: m_phase1Duration (int) - target time for phase 1
//   +0x27c: m_eventId (int) - event identifier for callback
//   +0x274: m_phase2Duration (int) - target time for phase 2
//   +0x282: m_bPhase2Complete (byte) - phase 2 completed flag

#include <cstdint> // For int, byte if needed; assuming char for bytes

// Forward declarations for globals used
extern class TimeManager* g_timeManager;  // *DAT_01223510
extern class EventManager* g_eventManager; // DAT_0122350c
extern int getGlobalTime(void); // DAT_0122350c? Actually FUN_005e9780 is separate

class MissionPhaseTimer {
public:
    int m_bEnabled;           // +0x26c
    char m_bPhase1Complete;   // +0x281
    int m_bPhase1Active;      // +0x484
    int m_timerObject;        // +0x1cc
    int m_phase1Duration;     // +0x270
    int m_eventId;            // +0x27c
    int m_phase2Duration;     // +0x274
    char m_bPhase2Complete;   // +0x282
};

void __thiscall MissionPhaseTimer::updateTimer(void)
{
    if (this->m_bEnabled != 0) {
        // --- Phase 1: Not yet completed and currently active ---
        if (this->m_bPhase1Complete == 0) {
            if (this->m_bPhase1Active != 0) {
                // Get current time from the timer object via the global TimeManager
                // The TimeManager's vtable at offset 0x68 holds a getTime method.
                int currentTime = g_timeManager->getTime(this->m_timerObject);
                // Ensure valid (non-negative) time and compare with duration
                if ((currentTime >= 0) && (currentTime >= this->m_phase1Duration)) {
                    this->m_bPhase1Complete = 1;
                    g_eventManager->fireEvent(this->m_eventId, 6); // Phase 1 complete event
                }
            }
        }
        // --- Phase 2: Phase 1 completed, phase 2 not yet done ---
        else if ((this->m_phase2Duration >= 0) && (this->m_bPhase2Complete == 0)) {
            int globalTime = getGlobalTime();
            if ((globalTime >= 0) && (globalTime >= this->m_phase2Duration)) {
                this->m_bPhase2Complete = 1;
                g_eventManager->fireEvent(this->m_eventId, 7); // Phase 2 complete event
            }
        }
    }
}