// Reconstructed from Ghidra export: 0x0040f950
// Input subsystem helper that broadcasts window focus transitions.
//
// The function caches the last focus state so repeated notifications are ignored.
// When the state changes, it fires one of two framework messages:
//   - iMsgWindowHasLostInputFocus
//   - iMsgWindowHasGainedInputFocus
//
// Those message handles are populated during the input manager bootstrap and are
// forwarded into the generic event dispatcher with a small stack packet.

#include <cstdint>

namespace EARS::Framework
{
    // Ghidra globals:
    //   DAT_0110acca -> cached input-focus state
    //   DAT_01206a08 -> message handle for "window lost input focus"
    //   DAT_01206a18 -> message handle for "window gained input focus"
    extern std::uint8_t g_lastInputFocusState;
    extern std::uint32_t g_windowLostInputFocusMessage;
    extern std::uint32_t g_windowGainedInputFocusMessage;

    struct InputFocusDispatchPacket
    {
        std::uint32_t messageHandle;
        std::uint32_t reserved;
        std::uint8_t recursionGuard;
        std::uint8_t padding[3];
    };

    extern "C" std::uint32_t __cdecl FUN_00408a00(std::uint32_t* packet, std::uint8_t dispatchFlags);

    // Ghidra: FUN_0040f950
    void __cdecl BroadcastWindowInputFocusChange(std::uint8_t hasInputFocus)
    {
        // Nothing to do if the engine is already in the requested state.
        if (hasInputFocus == g_lastInputFocusState) {
            return;
        }

        g_lastInputFocusState = hasInputFocus;

        // Losing focus notifies the input stack that it should stop processing
        // keyboard / mouse input for the game window.
        if (hasInputFocus == 0) {
            if (g_windowLostInputFocusMessage != 0) {
                InputFocusDispatchPacket packet{};
                packet.messageHandle = g_windowLostInputFocusMessage;
                FUN_00408a00(reinterpret_cast<std::uint32_t*>(&packet), 0);
            }
            return;
        }

        // Regaining focus notifies listeners that the window can accept input again.
        if (g_windowGainedInputFocusMessage != 0) {
            InputFocusDispatchPacket packet{};
            packet.messageHandle = g_windowGainedInputFocusMessage;
            FUN_00408a00(reinterpret_cast<std::uint32_t*>(&packet), 0);
        }
    }
} // namespace EARS::Framework
