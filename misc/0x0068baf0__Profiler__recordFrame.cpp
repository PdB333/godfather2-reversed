// FUNC_NAME: Profiler::recordFrame
// Function address: 0x0068baf0
// Records a profiling frame marker. Increments global frame counter, writes serialized event data (vtable pointers and counter) to a profile buffer. Optionally records label strings from global pointers.

#include <cstdint>

// Global profiling state
extern uint32_t g_frameCounter;                  // DAT_01129a8c
extern uint8_t* g_profileBuffer;                 // DAT_01206880 - base of profile buffer structure
extern const char* g_profileLabel1;              // DAT_0120ecb0
extern const char* g_profileLabel2;              // DAT_0120ecb8

// Profile buffer structure (at g_profileBuffer)
struct ProfileBuffer {
    uint8_t pad0[0x14];                          // +0x00 - unknown
    uint8_t** currentPtr;                        // +0x14 - pointer to current write position
};

// Forward declarations of helper functions (from elsewhere)
void Profiler_beginScope(int a, int b);          // FUN_0040cce0
int Profiler_checkScope(int a, int b);           // FUN_0040cd20 - returns non-zero if profiling active
void Profiler_writeFrameData();                  // FUN_00485600
void Profiler_registerLabel(const char* str, int mode); // FUN_00408a00
void Profiler_endScope(int mode);                // FUN_0040cd50
void Profiler_flushScope();                      // FUN_004869a0
void Profiler_cleanupA();                        // FUN_00485180
void Profiler_cleanupB();                        // FUN_00485280
void Profiler_cleanupC();                        // FUN_0040e1b0

// Static vtable pointers for serialized events (point to serializer functions)
extern void* g_vtableFrameStart;                 // PTR_LAB_00e501f0
extern void* g_vtableFrameEnd;                   // PTR_LAB_00e501a0

void Profiler::recordFrame(char isNewFrame)
{
    // Increment global frame counter
    g_frameCounter++;

    // Begin profiling scope (type 0, subsection 1)
    Profiler_beginScope(0, 1);

    // Check if profiling is currently active
    int profilingActive = Profiler_checkScope(1, 0);

    // Write initial frame data (possibly header)
    Profiler_writeFrameData();

    // Access the profile buffer's current write pointer
    ProfileBuffer* buffer = reinterpret_cast<ProfileBuffer*>(g_profileBuffer);
    uint8_t** writePtr = buffer->currentPtr;

    // Write frame start event (vtable and counter)
    *writePtr = reinterpret_cast<uint8_t*>(&g_vtableFrameStart);
    writePtr++;
    *writePtr = reinterpret_cast<uint8_t*>(g_frameCounter);
    writePtr++;

    // Write frame end event vtable (value to be written later?)
    *writePtr = reinterpret_cast<uint8_t*>(&g_vtableFrameEnd);
    writePtr++;

    // Update the buffer's current pointer
    buffer->currentPtr = writePtr;

    // If this is a new frame, register the first label
    if (isNewFrame != 0) {
        uint32_t local[3] = { reinterpret_cast<uint32_t>(g_profileLabel1), 0, 0 };
        Profiler_registerLabel(reinterpret_cast<const char*>(&local), 0);
    }

    // If profiling was active on entry, end the previous scope (type 1)
    if (profilingActive != 0) {
        Profiler_flushScope();
        Profiler_endScope(1);  // End scope with mode 1
    }

    // If this is a new frame, register the second label
    if (isNewFrame != 0) {
        uint32_t local[3] = { reinterpret_cast<uint32_t>(g_profileLabel2), 0, 0 };
        Profiler_registerLabel(reinterpret_cast<const char*>(&local), 0);
    }

    // Final cleanup sequence
    Profiler_cleanupA();
    Profiler_cleanupB();
    Profiler_cleanupC();

    return;
}