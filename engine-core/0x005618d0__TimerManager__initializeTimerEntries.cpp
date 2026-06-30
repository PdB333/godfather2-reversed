// FUNC_NAME: TimerManager::initializeTimerEntries
// Address: 0x005618d0
// This function initializes a set of timer entries for the current thread.
// It uses thread-local storage to get a context, then sets up an array of timer structures
// and registers each with a callback.

#include <windows.h> // For TlsGetValue

// Forward declarations of internal functions
void timerContextInitialize(void* context, int param);
void timerContextFinalize(void* context);
void registerTimerEntry(void* timerEntry, void* callback);
void timerCallbackFunction(void* param); // Callback for timer expiry

// Structure representing a single timer entry (size 0x30 bytes)
struct TimerEntry {
    int period;          // +0x10: Timer period (e.g., 0x7d000 = 512000 ms?)
    int id;              // +0x14: Timer ID (copied from this+0xc)
    int flags;           // +0x18: Flags (initially 0)
    int state;           // +0x1c: State (initially 0)
    char unknown;        // +0x20: Byte field (initially 0)
    int padding[5];      // Padding to align next fields
    int callbackIndex;   // +0x38: Index for callback (iVar2 + 2)
    void* context;       // +0x3c: Pointer to the owning TimerManager instance
};

// Class representing the timer manager (size unknown, but includes fields at +0x4, +0xc, +0x18)
class TimerManager {
public:
    int timerCount;          // +0x04: Number of timers to initialize
    int timerId;             // +0x0c: Common ID for all timers
    TimerEntry entries[1];   // +0x18: Array of timer entries (actual size = timerCount * 0x30)
};

void TimerManager::initializeTimerEntries() {
    // Get thread-local context
    void* tlsContext = TlsGetValue(DAT_01139830); // DAT_01139830 is the TLS index
    timerContextInitialize(tlsContext, *(int*)((char*)this + 0xc));

    tlsContext = TlsGetValue(DAT_01139830);
    timerContextFinalize(tlsContext);

    int count = *(int*)((char*)this + 4);
    if (count > 0) {
        TimerEntry* entry = (TimerEntry*)((char*)this + 0x18);
        for (int i = 0; i < count; i++) {
            // Initialize each timer entry
            entry->period = 0x7d000;          // Timer period
            entry->id = *(int*)((char*)this + 0xc); // Common ID
            entry->flags = 0;
            entry->state = 0;
            entry->unknown = 0;
            entry->context = this;
            entry->callbackIndex = i + 2;     // Callback index (2-based)

            // Register the timer with the callback
            registerTimerEntry(&entry->period, timerCallbackFunction);

            entry++; // Move to next entry (stride 0x30 bytes)
        }
    }
}