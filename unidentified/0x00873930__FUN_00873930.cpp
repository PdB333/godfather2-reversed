// FUNC_NAME: SomeClass::startCooldownTimer
// This function checks if any of four target pointers (offsets +0xE4, +0xE8, +0xEC, +0xF0) are non-null
// and if the timer flag at +0x06 is not already set. If so, it starts a 5-second cooldown timer
// (using a global time base at DAT_01205224) and resets a counter at +0x11C.
class SomeClass {
public:
    char pad_0[6];               // +0x00
    bool m_timerActive;          // +0x06
    int m_timerEnd;              // +0x08
    // ... other fields ...
    void* m_target1;             // +0xE4
    void* m_target2;             // +0xE8
    void* m_target3;             // +0xEC
    void* m_target4;             // +0xF0
    // ... more fields ...
    int m_someCounter;           // +0x11C
};

extern int g_globalTime; // DAT_01205224

void __thiscall SomeClass::startCooldownTimer() {
    if ((m_target1 != nullptr || m_target2 != nullptr || m_target3 != nullptr || m_target4 != nullptr) &&
        !m_timerActive) {
        m_timerEnd = g_globalTime + 5000;
        m_timerActive = true;
        m_someCounter = 0;
    }
}