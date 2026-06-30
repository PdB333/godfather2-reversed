// FUNC_NAME: SimManager::setCurrentSimulator
// Address: 0x005368e0
// Role: Stores a pointer to the current simulator/object, then dispatches state-dependent actions.
//       Likely called when a new simulator becomes active (e.g., during gameplay mode transitions).

#include <cstdint>

// Global variables (declared static or in unknown translation unit)
static void* s_currentSimulator;          // 0x0121a310
static void* s_defaultManager;            // 0x012058e8
static void* s_defaultState;              // 0x0121a1f0 (address of default state block)
static uint32_t s_currentState;           // 0x0121a204 (some state enum)
static uint32_t s_idleState;              // 0x0121a36c (value representing idle state)
static uint32_t s_flag;                   // 0x0121a32c (nonzero triggers immediate action)
static uint32_t s_activeState;            // 0x012198f8 (value representing active state)
static void* s_activeData;                // 0x01219910 (data associated with active state)

// Functions called internally
void FUN_006063b0(void);                  // startIdleAction or similar
void FUN_0060b2f0(uint32_t state, void* data); // startActiveAction(state, data)

void SimManager::setCurrentSimulator(void* simulator)
{
    s_currentSimulator = simulator;

    // Check if we are operating under the default manager instance
    if (s_defaultManager == &s_defaultState)
    {
        if (s_currentState == s_idleState)
        {
            if (s_flag != 0)
            {
                FUN_006063b0(); // likely triggers idle behaviour
                return;
            }
        }
        else if (s_currentState == s_activeState)
        {
            FUN_0060b2f0(s_currentState, s_activeData); // transitions to active state
        }
    }
    // else: ignore non-default manager or unimplemented path
}