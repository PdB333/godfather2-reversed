// FUNC_NAME: applyCharacterInputState

#include <cstdint>

// Global state accessor - returns pointer to current character state object
extern void* getCharacterState();

// Global scale factor for converting float to integer (probably fixed-point)
extern float g_scaleFactor;

// Global max speed threshold (float)
extern float g_maxSpeedThreshold;

// Input structure (expected offsets from param_2)
struct CharacterInput {
    uint8_t unknown0[2];    // +0x00
    uint8_t flags;          // +0x02
    // Flags: bit2 = grounded?, bit3 = running?
    uint8_t unknown3[0x15]; // +0x03 to +0x17
    float velocityX;        // +0x18
    float velocityY;        // +0x1c
    float positionX;        // +0x20
    float positionY;        // +0x24
    float speed;            // +0x28
    float sprintSpeed;      // +0x2c (only applied if <= threshold)
    float rotationQuatA;    // +0x30
    float rotationQuatB;    // +0x34
    float rotationQuatC;    // +0x38
    float rotationQuatD;    // +0x3c
};

// Character state structure (offsets from pointer returned by getCharacterState())
struct CharacterState {
    uint8_t pad0[5];
    bool isGrounded;        // +0x05
    uint8_t pad6[6];        // +0x06 to +0x0b
    float positionX;        // +0x0c
    uint8_t pad10[12];      // +0x10 to +0x1b
    float positionY;        // +0x1c
    uint8_t pad20[0x29 - 0x20]; // +0x20 to +0x28
    bool isRunning;         // +0x29
    uint8_t pad2a[6];       // +0x2a to +0x2f
    float velocityX;        // +0x30
    float velocityY;        // +0x34
    float rotationQuatA;    // +0x38
    uint8_t pad3c[0x1c];    // +0x3c to +0x57
    float rotationQuatB;    // +0x58
    float rotationQuatC;    // +0x5c
    int32_t speedQuantized; // +0x60 (speed * g_scaleFactor)
    int32_t sprintSpeedQuantized; // +0x64 (sprintSpeed * g_scaleFactor, if within threshold)
    // Note: rotationQuatD not present? It was copied to +0x54 maybe?
    uint8_t pad58[0x54 - 0x58]; // adjustment for rotationQuatD at +0x54
    float rotationQuatD;    // +0x54 (actually overwritten at +0x54 from input+0x30)
    // Fix: +0x54 is rotationQuatD, +0x58 is rotationQuatB, +0x5c is rotationQuatC
    // But order in input: A,B,C,D -> state: D?, A, B, C? Need to reexamine.
    // From code:
    // *(undefined4 *)(iVar2 + 0x54) = *(undefined4 *)(param_2 + 0x30); // input.quatA -> state.quatD? 
    // *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(param_2 + 0x34); // input.quatB -> state.quatA
    // *(undefined4 *)(iVar2 + 0x58) = *(undefined4 *)(param_2 + 0x38); // input.quatC -> state.quatB
    // *(undefined4 *)(iVar2 + 0x5c) = *(undefined4 *)(param_2 + 0x3c); // input.quatD -> state.quatC
    // So state stores: quatD at +0x54, quatA at +0x38, quatB at +0x58, quatC at +0x5c.
    // Thus we can define separate fields.
};

// Returns true on success
bool __cdecl applyCharacterInputState(void* unused, CharacterInput* input) {
    CharacterState* state = static_cast<CharacterState*>(getCharacterState());
    if (!input) {
        // Return value is extraout_DL - assumed to be false (0)
        return false;
    }

    // Copy rotation quaternion components (mapping: input A,B,C,D -> state D,A,B,C)
    state->rotationQuatD = input->rotationQuatA;   // +0x54 = input+0x30
    state->velocityX = input->rotationQuatB;        // +0x30? Wait careful.
    // The code copies:
    // *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(param_2 + 0x18); // input.velocityX -> state.velocityX
    // Correct velocity assignments:
    state->velocityX = input->velocityX;   // +0x30 = input+0x18
    state->velocityY = input->velocityY;   // +0x34 = input+0x1c
    state->rotationQuatA = input->rotationQuatB; // +0x38 = input+0x34
    state->positionX = input->positionX;   // +0x0c = input+0x20
    state->positionY = input->positionY;   // +0x1c = input+0x24
    // Flags:
    state->isGrounded = (input->flags & 0x04) == 0x04; // bit2
    state->isRunning   = (input->flags & 0x08) == 0x08; // bit3
    // Rotations from input:
    state->rotationQuatB = input->rotationQuatC; // +0x58 = input+0x38
    state->rotationQuatC = input->rotationQuatD; // +0x5c = input+0x3c
    // Speed quantization:
    state->speedQuantized = static_cast<int>(input->speed * g_scaleFactor);
    // Sprint speed only if within threshold:
    if (input->sprintSpeed <= g_maxSpeedThreshold) {
        state->sprintSpeedQuantized = static_cast<int>(input->sprintSpeed * g_scaleFactor);
    }
    return true;
}