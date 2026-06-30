// FUNC_NAME: GameState::getCurrentMoodColor
// Address: 0x006e4730
// Role: Returns a color constant based on the current game mood/action state.
// The function checks if the current player has an active action (via pointer at this+0x100),
// retrieves a singleton manager (likely SoundManager or AudioManager),
// calls a virtual method to get the current action state, and maps the action type (0-8) to a color value.

#include <cstdint>

extern int* DAT_01131018; // Pointer to singleton manager
extern uint32_t _DAT_00d5780c; // Color constant for action type 0
extern uint32_t DAT_00d5eee4; // Color constant for action type 1
extern uint32_t DAT_00e445ac; // Color constant for action type 2
extern uint32_t DAT_00d5ddec; // Color constant for action type 3
extern uint32_t DAT_00d5779c; // Color constant for action type 4
extern uint32_t DAT_00e44634; // Color constant for action type 5
extern uint32_t DAT_00e445fc; // Color constant for action type 6
extern uint32_t DAT_00e448a4; // Color constant for action type 7

// Forward declaration for the singleton retriever
void* __thiscall getManagerSingleton(int* managerPtr);

void __thiscall GameState::getCurrentMoodColor(GameState* this, uint32_t* outColor)
{
    // Check if a valid action pointer exists at offset 0x100
    if (*(uint32_t*)((uint8_t*)this + 0x100) != 0)
    {
        // Get the singleton manager (e.g., SoundManager or AudioDataManager)
        void* manager = getManagerSingleton(DAT_01131018);
        if (manager != nullptr)
        {
            // Call virtual function at vtable+0x34 to get current action state object
            // vtable is at beginning of manager object
            void* actionState = (*(void* (__thiscall**)(void*))(*(uint32_t*)manager + 0x34))(manager);
            if (actionState != nullptr)
            {
                // Read action type from offset 0x38 of the action state
                int32_t actionType = *(int32_t*)((uint8_t*)actionState + 0x38);
                switch (actionType)
                {
                case 0:
                    *outColor = _DAT_00d5780c;
                    return;
                case 1:
                    *outColor = DAT_00d5eee4;
                    return;
                case 2:
                    *outColor = DAT_00e445ac;
                    return;
                case 3:
                    *outColor = DAT_00d5ddec;
                    return;
                case 4:
                    *outColor = DAT_00d5779c;
                    return;
                case 5:
                    *outColor = DAT_00e44634;
                    return;
                case 6:
                    *outColor = DAT_00e445fc;
                    return;
                case 7:
                    *outColor = DAT_00e448a4;
                    return;
                }
            }
        }
    }
    // Default: return 0 (no color)
    *outColor = 0;
}