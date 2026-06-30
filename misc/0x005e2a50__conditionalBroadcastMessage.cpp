// FUNC_NAME: conditionalBroadcastMessage
// Address: 0x005e2a50
// Role: Conditionally broadcasts a message if the game dispatcher is enabled.
// The global g_pGameDispatcher (DAT_0122350c) is a singleton with a flag at +0x1744 (m_bEnabled).
// If flag is nonzero, calls broadcastMessage with given params and sender -1 (broadcast to all).

#include <cstdint>

// Forward declaration for broadcastMessage function (defined elsewhere)
void broadcastMessage(GameDispatcher* pDispatcher, int param1, int param2, int param3, int sender);

// Global singleton pointer to the game dispatcher
extern GameDispatcher* g_pGameDispatcher;

void conditionalBroadcastMessage(int param1, int param2, int param3)
{
    // Check if the dispatcher's enabled flag (offset +0x1744) is set.
    // This cast reads the byte at that offset; we assume it's a bool or char flag.
    if (*reinterpret_cast<volatile char*>(reinterpret_cast<uintptr_t>(g_pGameDispatcher) + 0x1744) != 0)
    {
        // Call broadcastMessage with sender = -1 (likely means no specific sender / all listeners).
        broadcastMessage(g_pGameDispatcher, param1, param2, param3, -1);
    }
}