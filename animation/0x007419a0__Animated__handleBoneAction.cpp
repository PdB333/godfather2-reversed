// FUNC_NAME: Animated::handleBoneAction
// Address: 0x007419a0
// Role: Dispatches bone manipulation operations (scale, reset, randomize) on animated characters

#include <cstdint>

// Forward declarations of callees
extern void setBoneScale(int boneIndex, float scale, uint8_t flag);
extern void setBoneScaleAt(int targetPtr, float scale, uint8_t flag);
extern void resetBoneTransform(int boneStructPtr, uint8_t flag);
extern void applyBoneTransform(int boneIndex, uint8_t flag);
extern int nextRandom(int seed);      // pseudo‑random sequence
extern void setBoneOffset(int dest, int offset);
extern uint8_t defaultBoneOpHandler(uint param2, float param3, uint param4, int op, uint param6);

class Animated {
public:
    uint8_t handleBoneAction(uint param2, float value, uint param4, int operation, uint param6) __thiscall {
        uint8_t result = 0;

        // +0x48: some flag/count
        // +0x50: current bone index (or pointer to bone)
        // +0x58: scale multiplier (float)
        // +0x5C: bone transform container
        // +0x70: another bone action target
        int* boneData = *(int**)(this + 0x50);          // +0x50
        float scaleMul = *(float*)(this + 0x58);       // +0x58
        int flag = *(int*)(this + 0x48);               // +0x48

        switch (operation - 10) {
        case 0: // operation 10: scale bone by (value * internal scale)
            if (boneData != nullptr && boneData != (int*)0x48) {
                int boneIndex = (boneData == nullptr) ? 0 : (int)(boneData - (int*)0x48);
                // +0x58 holds a scale multiplier for the bone
                setBoneScale(boneIndex, scaleMul * value, 0);
            }
            return 0;

        case 1: // operation 11: scale the bone at +0x70
            setBoneScaleAt((int)(this + 0x70), scaleMul * value, 0);
            return 0;

        case 2: // operation 12: reset bone transform
            resetBoneTransform((int)(this + 0x5C), 0);
            return 0;

        case 3: // operation 13: apply bone transform if valid
            if (boneData != nullptr && boneData != (int*)0x48) {
                int boneIndex = (boneData == nullptr) ? 0 : (int)(boneData - (int*)0x48);
                if (*(int*)(this + 0x48) != 0) {  // flag check
                    // bone exists, apply the transform
                    applyBoneTransform(boneIndex, 0);
                } else {
                    // fallback: still apply
                    applyBoneTransform(boneIndex, 0);
                }
            }
            return 0;

        case 4: // operation 14: set bone to random offset
            {
                int rand1 = nextRandom(0);
                int offset = rand1 + 0x20;
                int rand2 = nextRandom(offset);
                setBoneOffset(rand2 + 0x30, offset);
            }
            return 0;

        case 5: // operation 15: no action
            break;

        default: // unrecognized operation -> delegate to default handler
            result = defaultBoneOpHandler(param2, value, param4, operation, param6);
            break;
        }

        return result;
    }
};