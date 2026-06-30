// FUNC_NAME: TNLConnection::TNLConnection
// Function at 0x00561790: Constructor for TNLConnection (Torque Network Library connection object)
// Initializes connection state, buffer sizes, and performs startup delays.
// TLS access retrieves global game instance pointer for logging or state.

#include <windows.h> // for TlsGetValue, LPVOID

// External functions (from game engine)
extern void sleepOrYield();                // FUN_00aa6480 - brief sleep/yield (e.g., 1ms)
extern void waitForTimeout(int, int);      // FUN_00aad0e0 - wait with timeout? (0, 1000) = 1 second?
extern void initConnectionSubsystem();     // FUN_005618d0 - additional initialization

// TLS index (global) to retrieve game instance
extern DWORD gTlsGameInstanceIndex;        // DAT_01139810

// TNLConnection class layout (x86, offsets in bytes from this)
// +0x000: vtable pointer
// +0x004: version (4)
// +0x008: state (0)
// +0x00C: maxPacketSize (0x2800 = 10240)
// +0x130: gameInstance (from TLS offset 0x34)
// +0x140: flags (0x80000000)
// +0x144: someCounter (0)
// +0x148: someCounter2 (0)
// +0x14C: someFlags (0x80000000)
// +0x150: bufferSize (0x800 = 2048)

class TNLConnection {
public:
    // Constructor - fastcall convention: this in ECX, vtable in EAX
    void* __fastcall constructor(void* vtable) {
        // Store vtable pointer (hidden parameter)
        this->vtable = vtable;

        // Perform 6 iterations of a short sleep/yield (possibly to settle system)
        for (int i = 0; i < 6; ++i) {
            sleepOrYield();
        }

        // Wait twice for 1 second each (e.g., for device enumeration, network init)
        waitForTimeout(0, 1000);
        waitForTimeout(0, 1000);

        // Initialize connection fields
        this->flags = 0x80000000;           // +0x140: bit31 set (maybe active or delayed)
        this->counter1 = 0;                 // +0x144
        this->counter2 = 0;                 // +0x148
        this->someFlags = 0x80000000;       // +0x14C: another flag field
        this->version = 4;                  // +0x004: protocol version
        this->state = 0;                    // +0x008: initial state
        this->maxPacketSize = 0x2800;       // +0x00C: 10240 bytes (common for UDP/EA)
        this->bufferSize = 0x800;           // +0x150: 2048 bytes (e.g., send buffer)

        // Retrieve game instance pointer from Thread-Local Storage
        LPVOID tlsData = TlsGetValue(gTlsGameInstanceIndex);
        this->gameInstance = *(void**)((char*)tlsData + 0x34); // +0x130: game manager pointer

        // Call secondary initialization routine
        initConnectionSubsystem();

        return this;
    }

private:
    // Fields initialized in order of appearance in decompiled code
    void* vtable;                  // +0x000
    int   version;                 // +0x004
    int   state;                   // +0x008
    int   maxPacketSize;           // +0x00C
    // ... other fields ...
    void* gameInstance;            // +0x130
    int   flags;                   // +0x140
    int   counter1;                // +0x144
    int   counter2;                // +0x148
    int   someFlags;               // +0x14C
    int   bufferSize;              // +0x150
    // 0x154 total initialized area
};
// End of reconstructed function