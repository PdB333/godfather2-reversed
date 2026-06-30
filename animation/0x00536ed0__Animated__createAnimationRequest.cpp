// FUNC_NAME: Animated::createAnimationRequest
// Function address: 0x00536ed0
// Role: Allocates and initializes an animation request object, using the current animation set and optional index list.

// Reconstructed C++ based on Ghidra decompilation of The Godfather 2 (EA EARS engine).

#include <cstdint>

// Forward declarations for callees (not defined here)
int allocateAnimationRequest(); // FUN_00536d50: allocates a new AnimationRequest object, returns pointer or handle
void processIndexList(uint32_t* list); // FUN_00536c60: processes an index list structure
void initializeAnimationRequest(void* animSet, int param1, int param2, uint32_t* list); // FUN_00536e00

// Class representing an animation set (e.g., list of animations)
struct AnimationSet {
    /* +0x08 */ int32_t m_indexCount;       // number of indices in the default list
    /* +0x18 */ int32_t m_animCount;        // number of animations in the array
    /* +0x1c */ void* m_animations;         // pointer to array of AnimationEntry (each 0x18 bytes)
};

// Returned animation request object (structure unknown, only field at +4 is used here)
struct AnimationRequest {
    /* +0x04 */ Animated* m_owner;          // pointer to the owning Animated object
};

// The class that owns this method
class Animated {
public:
    // Fields used in this method
    /* +0x70 */ AnimationSet* m_animationSet;
    /* +0x76 */ int16_t m_currentAnimIndex;   // current animation index, validated against m_animCount

    // Method
    int createAnimationRequest(int32_t param1, uint32_t* param2);
};

int Animated::createAnimationRequest(int32_t param1, uint32_t* param2)
{
    int16_t sVar1;
    int32_t iVar2;     // pointer to new AnimationRequest
    int32_t iVar3;
    int32_t iVar4;     // validated animation set pointer
    uint32_t local_8c; // dummy for default case
    int16_t* local_88; // pointer to index buffer
    int32_t local_84;  // number of indices
    int16_t local_80[64]; // local buffer for default indices

    iVar4 = *(int32_t*)(this + 0x70); // this->m_animationSet

    // Validate animation set and current index
    if (((iVar4 == 0) || (*(int32_t*)(iVar4 + 0x18) < 1)) || (*(int32_t*)(iVar4 + 0x1c) == 0) ||
        ((sVar1 = *(int16_t*)(this + 0x76), sVar1 < 0) ||
         (*(int32_t*)(iVar4 + 0x18) <= (int32_t)sVar1))) {
        iVar4 = 0; // invalid set
    } else {
        iVar4 = *(int32_t*)(iVar4 + 0x1c) + sVar1 * 0x18; // pointer to the current animation entry
    }

    iVar2 = allocateAnimationRequest(); // get a new AnimationRequest object
    if (iVar2 != 0) {
        if (param1 < 0) {
            param1 = 0; // clamp negative param1 to 0
        }
        // Set the owner field of the request
        *(int32_t*)(iVar2 + 4) = reinterpret_cast<int32_t>(this); // request->m_owner = this

        if (param2 == nullptr) {
            // No explicit index list provided; build a default list of indices 0..count-1
            local_88 = local_80;
            local_84 = *(int32_t*)(iVar4 + 8); // animSet->m_indexCount
            local_8c = 0;
            if (local_84 > 0x3f) {
                local_84 = 0x40; // cap at 64
            }
            iVar3 = 0;
            if (local_84 > 0) {
                do {
                    local_88[iVar3] = (int16_t)iVar3; // fill with consecutive indices
                    iVar3 = iVar3 + 1;
                } while (iVar3 < local_84);
            }
            param2 = &local_8c; // use local dummy as list pointer (note: in original code, it's &local_8c)
        } else {
            // Non-null list: store pointer to index buffer in the list structure (offset +4?)
            // pList[1] stores the buffer pointer
            param2[1] = reinterpret_cast<uint32_t>(local_80); // actually local_80 buffer? careful: original code writes param2[1] = local_80, but local_80 is stack array. That seems wrong. In decompiled code, it's "param_2[1] = local_80;". That would be writing the stack address, which is dubious. Possibly a decompilation error; the buffer is likely param2+? We'll keep as-is for fidelity.
            processIndexList(param2);
        }
        // Initialize the request with the animation set entry, param1 (twice), and the list
        initializeAnimationRequest(reinterpret_cast<void*>(iVar4), param1, param1, param2);
        return iVar2; // return the handle/pointer to the request
    }
    return 0; // allocation failed
}