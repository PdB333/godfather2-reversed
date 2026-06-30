// FUNC_NAME: TimedEvent::setTimer
// Address: 0x0070b4d0
// This method manages a timer node linked into a parent list (pParentList).
// It either cancels the timer (if pParentList == 0) or starts/schedules it.
// The timer entry is stored in fields at offsets +0xE0, +0xE8, +0xE9 (relative to this).
// The virtual function at vtable[0x19c] is called after setting the timer.

#include <cstdint>

// Forward declarations for helper functions
void releaseTimerNode(int* pNode);                       // FUN_004daf90
uint32_t getGlobalTickCount();                           // FUN_008b6ae0
float getTimeScaleFactor();                              // FUN_008b70b0

class TimedEvent {
public:
    // Offsets (in int units, each 4 bytes):
    // +0xE0: m_startTime (uint32_t) - time when timer was started
    // +0xE8: m_pTimerNode (int*) - pointer to the timer node (linked list node)
    // +0xE9: m_pNext (int*) - next pointer in the timer list

    void setTimer(int callbackHandle, int* pParentList) {
        int* pTimerNode = reinterpret_cast<int*>(&m_pTimerNode); // &(param_1[0xE8])
        int currentTimerNode = m_pTimerNode; // param_1[0xe8]

        if (pParentList == nullptr) {
            // Cancel timer: release node if it exists
            if (currentTimerNode != 0) {
                releaseTimerNode(pTimerNode);
                m_pTimerNode = 0;
            }
            // Use default time scale (global)
            float timeScale = *reinterpret_cast<float*>(0x00d5ccf8);
            m_startTime = 0;
            // Notify callback with default scale
            (this->*(vtable[0x19c / 4]))(callbackHandle, timeScale);
        } else {
            // Schedule timer – link into parent's list
            int* newTimerNode = reinterpret_cast<int*>(reinterpret_cast<char*>(pParentList) + 0x48);
            if (currentTimerNode != newTimerNode) {
                if (currentTimerNode != 0) {
                    releaseTimerNode(pTimerNode);
                }
                m_pTimerNode = newTimerNode;
                if (newTimerNode != nullptr) {
                    // Insert at head of singly linked list stored in pParentList+0x4c
                    m_pNext = *reinterpret_cast<int*>(reinterpret_cast<char*>(pParentList) + 0x4c);
                    *reinterpret_cast<int**>(reinterpret_cast<char*>(pParentList) + 0x4c) = pTimerNode;
                }
            }
            // Record current tick and time scale
            m_startTime = getGlobalTickCount();
            float timeScale = getTimeScaleFactor();
            // Notify callback with the actual time scale
            (this->*(vtable[0x19c / 4]))(callbackHandle, timeScale);
        }
    }

private:
    // Data members (offsets based on decompilation)
    uint32_t m_startTime;   // +0xE0 (0x380 bytes from this)
    int* m_pTimerNode;      // +0xE8 (0x3A0)
    int* m_pNext;          // +0xE9 (0x3A4) – used for list linking
    // ... other members
};