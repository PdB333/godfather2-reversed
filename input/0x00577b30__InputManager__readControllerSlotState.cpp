// FUNC_NAME: InputManager::readControllerSlotState
// Address: 0x00577b30
// Reads raw input from a controller slot and fills out the controller state structure.

#include <cstdint>

struct InputState {
    uint32_t data[16];  // 64 bytes of input data
};

// From decompiled context: these are likely constants for uninitialized input values.
static const uint32_t kDefaultInputValue = DAT_00e2b1a4;  // global value, assumed 0xFFFFFFFF

// Forward declarations
void processRawInput(uint32_t scaledInput);  // FUN_00414c90
void resetControllerState(InputState* outState);  // FUN_00412d90

/**
 * Reads a controller slot's raw input byte and converts it into a full InputState.
 * @param outState        Output: 16-element uint32 array representing controller state.
 * @param slotIndex       Index of the controller slot (0-15).
 * @param manager         Pointer to the InputManager instance.
 * @return                1 if valid input was processed, 0 if slot is invalid/disconnected.
 */
int32_t __fastcall InputManager::readControllerSlotState(
    InputState* outState, uint32_t slotIndex, InputManager* manager)
{
    // Access a compressed input byte array at manager+0xB4
    // +0xB4: uint8* compressedInputBytes (one byte per slot)
    uint8_t* compressedInput = reinterpret_cast<uint8_t*>(*(int*)(reinterpret_cast<uint8_t*>(manager) + 0xB4));
    // +0xB8: pointer to array of full controller state structures (each 0x40 bytes)
    uint8_t* controllerStateArray = reinterpret_cast<uint8_t*>(*(int*)(reinterpret_cast<uint8_t*>(manager) + 0xB8));
    // +0x10: flags (bit 3 = ignore input? 0 = allowed)
    uint32_t flags = *(uint32_t*)(reinterpret_cast<uint8_t*>(manager) + 0x10);

    // Check if compressed input data exists and this slot has a valid byte
    if (compressedInput != nullptr) {
        uint8_t rawByte = compressedInput[slotIndex];
        if (rawByte != 0xFF) {  // 0xFF indicates disconnected or invalid slot
            // Check if input is enabled (bit 3 cleared)
            if ((flags & (1 << 3)) == 0) {
                if (controllerStateArray != nullptr) {
                    // Decode raw byte into full controller state structure at offset (rawByte * 0x40)
                    processRawInput(rawByte * 0x40 + reinterpret_cast<uint32_t>(controllerStateArray));
                    return 1;
                } else {
                    // No full state structure; initialize default state
                    resetControllerState(outState);
                    return 0;
                }
            }
        }
    }

    // Default: fill outState with constant values (no valid input)
    outState->data[0]  = kDefaultInputValue;
    outState->data[1]  = 0;
    outState->data[2]  = 0;
    outState->data[3]  = 0;
    outState->data[4]  = 0;
    outState->data[5]  = kDefaultInputValue;
    outState->data[6]  = 0;
    outState->data[7]  = 0;
    outState->data[8]  = 0;
    outState->data[9]  = 0;
    outState->data[10] = kDefaultInputValue;
    outState->data[11] = 0;
    outState->data[12] = 0;
    outState->data[13] = 0;
    outState->data[14] = 0;
    outState->data[15] = kDefaultInputValue;
    return 0;
}