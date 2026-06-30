// FUNC_NAME: NetSession::processUpdateWithLock
// Address: 0x004cb6e0
// Role: Calls a virtual update method (vtable+0xc) while holding a reentrancy lock, then checks a condition via FUN_00655250

#include <cstdint>

// Global reentrancy counter (0x01205a30)
extern int32_t g_reentrancyLock;

// Forward declaration of helper function at 0x00655250 (likely checks some state)
extern "C" int32_t __cdecl checkSomething(void); // placeholder name

int32_t __thiscall NetSession::processUpdateWithLock(void) {
    g_reentrancyLock++; // Enter reentrancy guard

    // Possibly a network byte order conversion that does nothing
    htonl(0);

    // Call virtual at vtable offset 0xc (index 3) – likely 'processUpdate' or 'handleMessage'
    (*(void (__thiscall**)(void*))(*(uint32_t*)this + 0xc))(this);

    int32_t result = checkSomething();

    g_reentrancyLock--; // Exit reentrancy guard

    return (result != 0) ? 1 : 0;
}