// FUNC_NAME: DelayedActionController::update
// Function address: 0x00457a10
// Purpose: Updates a delayed action/timer state machine. Manages activation, pause, and callback triggering.
// Field offsets:
//   0xE0  - bool m_activeFlag? (set to 0 on pause)
//   0xEC  - ? (not used here)
//   0xF8  - bool m_timerActive? (flag for timer remove)
//   0x138 - char* m_dataPointerA? (cleared on pause if non-null)
//   0x13C - int  m_duration? (set to 0 on pause)
//   0x148 - char* m_dataPointerB? (cleared on pause if non-null)
//   0x14C - int  m_unknown? (set to 0 on pause)
//   0x158 - int  m_targetValue? (set from global DAT_00e2eff4 when starting)
//   0x164 - int  m_timerLow? (reset to 0)
//   0x168 - int  m_timerHigh? (reset to 0)
//   0x16C - int  m_state (0 = idle, 1 = running)
//   0x170 - bool  m_paused? (if != 0, skips main block)
//   0x204 - void (*m_callbackFunc)(int,int)
//   0x208 - bool  m_callbackFired? (set to 1 after calling)
//   0x20C - int   m_callbackArg1
//   0x210 - int   m_callbackArg2

#include <cstdint>

class DelayedActionController {
public:
    // (vtable, etc. not shown)
    void update();  // __thiscall
};

// Global externs (from Ghidra)
extern int DAT_00e2e4c8;     // mutex/lock object
extern int DAT_00e2eff4;     // some global value (target time? timestamp?)
extern int DAT_01206940;     // timer slot or handle

// Called helper functions
extern void FUN_00ab4db0(int*); // lock (mutex) – takes address of global
extern bool FUN_00458a80();     // some condition check (e.g., "is complete?")
extern void FUN_004086d0(int*); // timer removal (takes address of global timer)
extern void FUN_00ab4e70();     // unlock

void DelayedActionController::update() {
    // Lock global mutex (likely for thread safety)
    FUN_00ab4db0(&DAT_00e2e4c8);

    // Check if state is active (non-zero)
    if (m_state != 0) {
        bool bComplete = FUN_00458a80();  // check condition (maybe time elapsed?)
        int globalVal = DAT_00e2eff4;     // some global value (e.g., current time)
        if (!bComplete) {
            // Not yet complete: reset timer counts and set target value
            m_timerLow = 0;
            m_timerHigh = 0;
            m_targetValue = globalVal;   // store the global value as target
            m_state = 0;                  // mark as idle (reset)
        }
        // If state is still non-zero after the check, jump to callback handling
        if (m_state != 0) goto check_callback;
    }

    // Check pause flag (m_paused)
    if (m_paused == 0) {
        // Not paused: clean up data pointers and flags
        m_duration = 0;
        if (m_dataPointerA != nullptr) {
            *m_dataPointerA = 0;   // clear first byte?
        }
        m_unknownField = 0;
        if (m_dataPointerB != nullptr) {
            *m_dataPointerB = 0;
        }
        m_activeFlag = 0;
        m_timerLow = 0;
        m_timerHigh = 0;
        // If timer active flag is set, remove timer and clear flag
        if (m_timerActive) {
            m_timerActive = false;
            FUN_004086d0(&DAT_01206940);  // remove global timer
        }
    }

check_callback:
    // Check if there's a callback function set, not yet fired, and state is exactly 1
    if ((m_callbackFunc != nullptr) && (!m_callbackFired) && (m_state == 1)) {
        m_callbackFired = true;
        // Call the callback with arguments: (m_callbackArg1, 2, m_callbackArg2)
        // Note: The game passes constant 2 as second parameter? Possibly an enum.
        m_callbackFunc(m_callbackArg1, 2, m_callbackArg2);
    }

    FUN_00ab4e70(); // unlock
    return;
}