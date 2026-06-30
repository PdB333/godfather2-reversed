// FUNC_NAME: CNetworkManager::flushDirtyState
// Address: 0x006102c0
// Flushes two dirty state channels (e.g., reliable data and events).
// For each index in a dirty range, compares the current value with the last sent value,
// and if different, updates the last sent and notifies the network manager via virtual method at vtable+0xE4.
// Then resets the dirty range (low=0xFF, high=0).

#include <cstdint>

extern void* g_pNetworkManager;               // DAT_01205750 – singleton NetworkManager pointer
extern uint32_t g_dirtyLow[2];                // DAT_00f15988 – low index for each channel
extern uint32_t g_dirtyHigh[2];               // DAT_012058d0 – high index for each channel
extern int32_t g_currentValues[];             // DAT_011f39d8 – current state values
extern int32_t g_lastSentValues[];            // DAT_011f3dd8 – last sent state values

void CNetworkManager::flushDirtyState()
{
    // Process two channels (offset 0 and 4 bytes into the arrays)
    for (uint32_t channel = 0; channel < 2; ++channel)
    {
        uint32_t low  = g_dirtyLow[channel];
        uint32_t high = g_dirtyHigh[channel];

        // If the range is valid (low <= high), iterate through it
        if (low <= high)
        {
            for (uint32_t idx = low; idx <= high; ++idx)
            {
                int32_t curValue  = g_currentValues[idx];
                int32_t lastValue = g_lastSentValues[idx];

                // If the value changed, update and notify the network manager
                if (curValue != lastValue)
                {
                    g_lastSentValues[idx] = curValue;

                    // Virtual call: (*(this->vtable + 0xE4))(this, index, newValue)
                    void* vtable = *(void**)g_pNetworkManager;
                    typedef void (__thiscall* NotifyFunc)(void* _this, uint32_t index, int32_t value);
                    NotifyFunc notify = (NotifyFunc)(*((uintptr_t*)vtable + (0xE4 / sizeof(uintptr_t))));
                    notify(g_pNetworkManager, idx, curValue);
                }
            }
        }

        // Clear the dirty range for this channel
        g_dirtyHigh[channel] = 0;
        g_dirtyLow[channel]  = 0xFF;  // 0xFF ensures low > high until a real range is set
    }
}