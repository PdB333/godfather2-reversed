//FUNC_NAME: TimerManager::processTimers
// Address: 0x005627a0
// This function processes active timers: decrements a counter and fires a callback when it reaches zero.
// It also allocates a 0x200-byte block (tag 0x2d) and converts a buffer to a return value.

#include <windows.h> // for TlsGetValue

// Forward declarations of called functions (reconstructed names)
void* GetTimerObject();                // FUN_00562880 - returns pointer to current timer object
void EnterCriticalSection();           // FUN_009f9620 - enters a critical section / lock
void TimerUpdate(void* timer, float delta, void* buffer); // FUN_009e44f0 - updates timer state
void* AllocateMemory(size_t size, int tag); // FUN_00aa2680 - memory allocation
unsigned int ConvertBuffer(void* buffer);   // FUN_009f4640 - converts buffer to unsigned int

// Global data references
extern int DAT_00e2b118;   // some constant
extern int DAT_00e2b1a4;   // another constant
extern DWORD DAT_01139810; // TLS index for thread-local storage

unsigned int TimerManager::processTimers() {
    void* timerObj = GetTimerObject();
    EnterCriticalSection();

    int local_34 = DAT_00e2b118;
    int local_40 = DAT_00e2b1a4;

    // Initialize a local structure (possibly for timer update parameters)
    int local_c0 = 0;
    int local_bc = DAT_00e2b1a4;
    int local_b8 = 0;
    int local_b4 = 0;
    void* local_cc = timerObj;

    // Buffer for timer update (4 bytes)
    char buffer[4];
    TimerUpdate(timerObj, 1.0f, buffer); // 0x3f800000 = 1.0f

    // Set flags (type/state indicators)
    char flag1 = 4; // local_20
    char flag2 = 2; // local_1f

    // Retrieve thread-local storage value (likely per-thread timer manager)
    TlsGetValue(DAT_01139810);

    // Allocate a 0x200-byte block with tag 0x2d
    int* allocatedBlock = (int*)AllocateMemory(0x200, 0x2d);
    if (allocatedBlock) {
        allocatedBlock[1] = 0x200; // store size at offset +4
    }

    // Convert the buffer to a return value
    unsigned int result = ConvertBuffer(buffer);

    // Timer logic: check if timer has pending count (short at offset +2)
    if (*(short*)((char*)timerObj + 2) != 0) {
        // Decrement counter at offset +6
        *(short*)((char*)timerObj + 6) = *(short*)((char*)timerObj + 6) - 1;
        if (*(short*)((char*)timerObj + 6) == 0) {
            // Fire callback: vtable entry at offset 0, called with argument 1
            (**(void (__thiscall**)(void*, int))timerObj)(timerObj, 1);
        }
    }

    return result;
}