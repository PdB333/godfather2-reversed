// FUNC_NAME: Timer::Timer
// Function at 0x00845870: Constructor for a timer-like object. Clears 0x2c bytes at offset 4, sets two flags at +0x30 and +0x31 to 0, and initializes a default value at +0x34 from a global.

// Global default value (likely a timer interval or timeout)
extern int g_defaultTimerValue; // _DAT_00d5780c

class Timer {
public:
    // +0x00: vtable pointer (not touched by constructor)
    // +0x04: 0x2c bytes of state (zeroed)
    // +0x30: byte flag1
    // +0x31: byte flag2
    // +0x34: int default value

    // __fastcall: this in ECX
    void __fastcall Timer() {
        // Zero out state data from offset 4 to 4+0x2c-1
        __builtin_memset(reinterpret_cast<char*>(this) + 4, 0, 0x2c);
        
        // Explicitly zero two flags (beyond the memset range)
        reinterpret_cast<char*>(this)[0x30] = 0;
        reinterpret_cast<char*>(this)[0x31] = 0;
        
        // Initialize default value from global
        reinterpret_cast<int*>(this)[0x34 / 4] = g_defaultTimerValue;
    }
};