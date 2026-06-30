// FUNC_NAME: NetSession::constructor
// Function at 0x006a7b40
// Initializes a NetSession singleton with an interface object (likely IConnection/NetInterface)
// Manages network session settings, player counts, and vtable setup

#include <cstdint>

// Forward declarations
extern void BaseClassConstructor(); // FUN_0049c610
extern void SetMaxPlayers(uint32_t maxPlayers, uint32_t config); // FUN_006a79f0
extern void RegisterClass(void* classDesc, uint32_t flags); // FUN_0049c6e0

// Global variables (from data segment)
extern uint32_t gSessionConfig; // DAT_00d5c454 - configuration parameter for player count
extern NetSession* g_pNetSession; // DAT_01129984 - singleton pointer
extern void* gSessionData; // DAT_00d5d860 - class description for registration

// VTable addresses (from binary)
extern void* VTable_NetSession_Base; // PTR_LAB_00d5d868
extern void* VTable_NetSession_Sub1; // PTR_LAB_00d5d85c
extern void* VTable_NetSession_Sub2; // PTR_LAB_00d5d864

class NetSession {
public:
    // Offsets in this object (in 4-byte units):
    // +0x00: vtable pointer (VTable_NetSession_Base)
    // +0x04: unknown
    // +0x08: vtable pointer (VTable_NetSession_Sub1 then overwritten by Sub2)
    // +0x0C: interface object pointer (pInterface)
    // +0x28: some counter (offset 10)
    // +0x2C: some counter (offset 0xB)
    // +0x434: some flag (offset 0x10D)
    // +0x438: some flag (offset 0x10E)

    uint32_t* __thiscall constructor(uint32_t* pInterface);
};

uint32_t* __thiscall NetSession::constructor(uint32_t* pInterface) {
    uint32_t config;

    // Call base class constructor
    BaseClassConstructor();

    // Read configuration value for player limit
    config = gSessionConfig;

    // Set first secondary vtable (likely for inherited interface)
    this[2] = (uint32_t*)&VTable_NetSession_Sub1;

    // Store singleton reference
    g_pNetSession = (NetSession*)this;

    // Store interface object pointer (e.g., NetInterface or IConnection)
    this[3] = (uint32_t*)pInterface;

    // Set primary vtable
    this[0] = (uint32_t*)&VTable_NetSession_Base;

    // Override with another secondary vtable (likely overrides the first)
    this[2] = (uint32_t*)&VTable_NetSession_Sub2;

    // Initialize player count (6 = max players, config = some parameter)
    SetMaxPlayers(6, config);

    // Call the third virtual method on the interface object
    // (offset 8 = third entry in vtable, e.g., Initialize or Connect)
    ((void (*)(void))(*((int**)pInterface)[2]))();

    // Zero out various internal counters/flags
    this[0x10E] = 0; // offset 0x438
    this[0x10D] = 0; // offset 0x434
    this[10] = 0;    // offset 0x28
    this[0xB] = 0;   // offset 0x2C

    // Register the session class with the engine
    RegisterClass(&gSessionData, 1);

    return this;
}