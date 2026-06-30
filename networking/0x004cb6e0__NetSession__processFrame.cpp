// FUNC_NAME: NetSession::processFrame
// Function at 0x004cb6e0: Processes a frame/update for a network session.
// Uses a global reentrancy counter (0x01205a30) and calls a virtual method at vtable+0xc.
// Then checks for shutdown/error via FUN_00655250. Returns 1 on success (or non-zero from check), else 0.
// This is a __thiscall method on a class with a vtable pointer at offset 0.

#include <winsock2.h> // for htonl (or equivalent network functions)

// Global reentrancy guard (likely a reference count for a shared resource)
static int32_t g_reentrancyCounter = 0; // _DAT_01205a30

// Forward declaration of the check function (address 0x00655250)
int32_t __cdecl FUN_00655250(); // e.g., isSessionShuttingDown()

class NetSession {
public:
    // Virtual table pointer at offset 0 (implied)
    // Methods:
    // vtable[0] - unknown
    // vtable[1] - unknown
    // vtable[2] - unknown
    // vtable[3] - onProcess()  (offset +0xC)

    // Reconstructed method
    uint32_t __thiscall processFrame() {
        // Increment reentrancy guard
        g_reentrancyCounter++;

        // No-op network byte order call (likely placeholder or debug leftover)
        htonl(0);

        // Call virtual method at vtable offset 0xC (index 3)
        // This is the main processing virtual, e.g., onProcess()
        (this->vtable[3])();

        // Check global condition (e.g., if session should end or error occurred)
        int32_t checkResult = FUN_00655250();

        // Decrement reentrancy guard
        g_reentrancyCounter--;

        // Return 1 if check succeeded, else 0
        return (checkResult != 0) ? 1 : 0;
    }
};