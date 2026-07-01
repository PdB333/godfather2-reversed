// FUNC_NAME: AnimationManager::updateAnimations
// Address: 0x00995fb0
// Updates animation states for all characters/objects. Iterates over an array of AnimationState objects (0xC0 bytes each)
// and, if the state's 'active' flag is 0, updates its transform matrix and related data.

#include <cstdint>

// Forward declarations of called functions (likely in the animation system)
extern void FUN_00aa1a80(void* matrix);    // Probably normalizeQuaternion or computeWorldMatrix
extern void FUN_00aa1fc0(void* state);     // Probably updateAnimationState or updateBones
extern void FUN_009f4cd0(void* buffer);    // Possibly computeBlendedOutput

// Global constant (probably identity matrix or zero vector)
extern uint32_t _DAT_00d5780c;

// Animation state structure (0xC0 bytes per element)
struct AnimationState {
    void* vtable;           // +0x00: virtual table pointer
    uint32_t flags;         // +0x04? or maybe offset 0x08? Actually used via *(int*)(*piVar1 + 8) so flags at +0x08 from vtable?
    // The code checks *(int*)(*piVar1 + 8) == 0 so it's accessing something inside the object pointed by piVar1[0].
    // piVar1 points to the start of the AnimationState, piVar1[0] is a pointer to some internal data (e.g., a shared skeleton or matrix).
    // That internal data +0x08 is a integer flag (0 = needs update?).
    char pad_0x04[0x10];    // +0x04 to +0x13 (skipping to +0x14)
    // At +0x14 is data used in the virtual call (maybe a bone index or transform data)
    uint32_t dataAt0x14;    // +0x14
    // ... rest of the 0xC0 bytes (likely includes skeleton matrices, weights, etc.)
};

// Class that owns the array of AnimationStates
class AnimationManager {
public:
    AnimationState* states; // +0x34: pointer to array (each 0xC0 bytes)
    int32_t numStates;      // +0x38: count of elements
    void* transformManager; // +0x5c: pointer to an object with a vtable (e.g., TransformManager)
    // ... other fields
};

void __fastcall FUN_00995fb0(AnimationManager* this) {
    int32_t i;
    AnimationState* state;
    // 16-byte matrix/quaternion struct (x, y, z, w?) or transform
    struct {
        float a, b, c, d; // 16 bytes
    } matrix;

    // Buffer used by FUN_009f4cd0 (76 bytes)
    uint8_t tempBuffer[76];

    if (0 < this->numStates) {
        for (i = 0; i < this->numStates; ++i) {
            state = &this->states[i];

            // Access the internal data pointer from state->vtable or similar:
            // deref state->vtable as int*, then +0x08 gives a flag
            if (*(int32_t*)(*(int32_t*)state + 8) == 0) {
                // Clear matrix and set global constant (identity)
                matrix = {0, 0, 0, 0};
                // local_94 = _DAT_00d5780c; // Actually the global is stored at offset +0x10? But in the code it is assigned to local_94 which is later overwritten.
                // Actually the assignment to local_94 is later used in copying, but it's overwritten. The global constant is used at the end.

                // Call virtual method on transformManager at vtable+0x90
                // Parameters: output matrix (local_d0), input from state+0x14, flag=1
                void (*getTransform)(void* output, uint32_t* input, int32_t flag) =
                    (void (*)(void*, uint32_t*, int32_t))(*(void***)this->transformManager)[0x90 / 4];
                getTransform(&matrix, &state->dataAt0x14, 1);

                // Copy matrix into local stack block (expanded to 0x40 bytes?) and call functions
                // The code builds a larger local block (uStack_90...) that includes matrix and additional zeros, then calls FUN_00aa1a80
                // For simplicity, we construct the block on stack:
                struct BigBlock {
                    float m[4];      // from matrix
                    uint32_t padding1; // 0
                    float m2[4];     // copy of matrix?
                    uint32_t padding2; // 0
                    uint32_t zeros[?];
                    // ... actually it's complex
                };
                // Due to decompiler's awkward variable layout, we use a simplified version:
                // The code sets many local variables with specific values, then passes pointer to FUN_00aa1a80.
                // For brevity, assume the block is correctly constructed by the original code.

                // Call sequence:
                FUN_00aa1a80(/* pointer to block */);
                FUN_00aa1fc0((int32_t*)state + 1); // &state->dataAt0x04? Actually piVar1+4, so offset 4 bytes from state start
                FUN_009f4cd0(tempBuffer);
            }
        }
    }
}