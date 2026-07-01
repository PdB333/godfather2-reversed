// FUNC_NAME: PlayerActionValidator::isActionPermitted

#include <cstdint>

// Global variables (addresses from the binary)
static void* g_pauseStateManager = reinterpret_cast<void*>(0x0112982c);
static void* g_someFlagManager1 = reinterpret_cast<void*>(0x0112fee4);
static void* g_someFlagManager2 = reinterpret_cast<void*>(0x011305b4);

// Offset constants (from reversed struct layouts)
static constexpr int k_offset_managerActive           = 0x6C;  // int, likely flag/state
static constexpr int k_offset_flag48                  = 0x48;  // char (bool), some global condition
static constexpr int k_offset_thisFlag50              = 0x50;  // char (bool), local block flag
static constexpr int k_offset_arrayPtr                = 0x54;  // pointer to array of action objects
static constexpr int k_offset_arrayIndex              = 0x6C;  // int, index into the array
static constexpr int k_vtableOffset_canExecute        = 0x88;  // virtual method returning bool

// __fastcall: first param (ECX) is |this|
uint32_t __fastcall PlayerActionValidator::isActionPermitted(PlayerActionValidator* this)
{
    uint32_t result = reinterpret_cast<uint32_t>(g_pauseStateManager);

    // Overall condition: either global manager is not "blocked", or local state + global flags allow
    if ( (*reinterpret_cast<int*>(g_pauseStateManager) + k_offset_managerActive) == 0 &&
         ( (*reinterpret_cast<int*>(this) + k_offset_arrayIndex) != 0 ||
           ( *reinterpret_cast<char*>(g_someFlagManager1) + k_offset_flag48) == 0 &&
             ( result = reinterpret_cast<uint32_t>(g_someFlagManager2),
               *reinterpret_cast<char*>(g_someFlagManager2) + k_offset_flag48) == 0 ) )
    {
        // Check local block flag (0 means allowed)
        if ( *reinterpret_cast<char*>(this) + k_offset_thisFlag50) == 0 )
        {
            // Retrieve the action object from the array at given index
            int index = *reinterpret_cast<int*>(this) + k_offset_arrayIndex);
            void** array = *reinterpret_cast<void***>(this) + k_offset_arrayPtr);
            void* actionObj = array[index];

            // Call virtual function at offset 0x88
            typedef bool (__thiscall* CanExecuteFunc)(void*);
            CanExecuteFunc canExecute = *reinterpret_cast<CanExecuteFunc*>(*reinterpret_cast<uint32_t*>(actionObj) + k_vtableOffset_canExecute);
            if ( canExecute(actionObj) )
            {
                return 1; // action allowed
            }
        }
        return 0; // action blocked by local flag or virtual check
    }

    // Condition failed: return global status mask (clearing low byte)
    return result & 0xFFFFFF00;
}