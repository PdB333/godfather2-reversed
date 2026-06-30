// FUNC_NAME: AnimationComponent::updateAnimationLayer

#include <cstdint>

class AnimationComponent {
public:
    // Structure for animation slot (0x74 bytes each)
    struct AnimSlot {
        uint32_t* animData;      // +0x00 pointer to animation data
        float someFloat;         // +0x04
        uint8_t flags;           // +0x07 bit 0: active, bit 1: locked
        float startTime;         // +0x08
        float duration;          // +0x0C
        float endTime;           // +0x14
        float blendWeight;       // +0x3C
        uint32_t field_40;
        uint32_t field_44;
        uint32_t field_48;
        uint32_t field_4C;
        uint32_t field_50;
        uint32_t field_54;
        uint32_t field_58;
        uint32_t field_5C;
        uint32_t field_60;
        uint32_t field_64;
        uint32_t field_68;
        uint32_t field_6C;
        uint32_t field_70;
    };

    // Other members known: +0x603c AnimSlot* slotArray;
    // But we'll use offsets from 'this' directly.

    int updateAnimationLayer(int** context, int param3, int eaxParam);
};

// 0x005e61a0
// This function updates a single animation layer slot, handles blending and state transitions.
// context[5] = current slot index, context[7] = blend helper pointer.
int AnimationComponent::updateAnimationLayer(int** context, int param3, int eaxParam) {
    int result = 0;
    AnimSlot* slotArray = *(AnimSlot**)(this + 0x603c); // +0x603c: pointer to array of AnimSlot

    if (slotArray != nullptr && (int)context[5] < 0x200) {
        int slotIndex = (int)context[5];
        AnimSlot* currentSlot = &slotArray[slotIndex]; // slot size 0x74 bytes

        if (currentSlot != nullptr && currentSlot->animData != nullptr) {
            float unknownAccum = 0.0f;
            float outputWeight = 0.0f; // local_18 initially DAT_00e2b1a4 (some constant, likely 0.0)

            if ((currentSlot->flags & 1) != 0) {
                // Animation active
                int someIndex = 0;
                float timeValue = 0.0f;

                // eaxParam might be a blend layer index or flag
                if (eaxParam != 0) {
                    if (currentSlot + 0xf == nullptr) {
                        someIndex = 0;
                    } else {
                        // FUN_005e5900: probably finds index into a float array within the slot
                        someIndex = FUN_005e5900((float*)(currentSlot + 0xf));
                    }
                    unknownAccum = ((float*)currentSlot)[someIndex + 0xf];
                }

                float local_30 = unknownAccum;

                // Another condition with eaxParam
                if (eaxParam != 0) {
                    // param3 is used as an offset into some data
                    int dataIndex = param3 + someIndex * 0x30;
                    if ((*(uint8_t*)(dataIndex + 0x2c) & 1) != 0) {
                        // If context[7] is null, allocate/initialize blend helper
                        if (context[7] == nullptr) {
                            // FUN_00414c60: allocate memory, pass context and data+0x10, store result in local_20
                            FUN_00414c60(context, dataIndex + 0x10, &local_20);
                            context = &local_20; // reassign context pointer
                        }
                        // FUN_004bcfb0: returns a float (blend weight, timer?)
                        float fVar8 = (float)FUN_004bcfb0(context);
                        local_30 = fVar8;
                    }
                }

                outputWeight = local_30 - currentSlot->startTime; // * (float*)(iVar1 + 8)

                if (outputWeight < 0.0f) {
                    bool bVar3 = true; // negative weight
                    float modifiedWeight = outputWeight;

                    if (eaxParam < 2 && currentSlot != (AnimSlot*)(-12)) { // weird check, maybe avoid nullptr
                        // FUN_005e5980: some update function
                        FUN_005e5980(eaxParam);
                        modifiedWeight = unknownAccum;
                    }

                    outputWeight = 0.0f; // DAT_00e2b1a4 (probably 0.0)

                    // Check bit 1 of flags
                    if ((currentSlot->flags & 2) == 0) {
                        // Store DAT_00e2b1a4 into slot field +0x54 (piVar7[0x15])
                        ((float*)currentSlot)[0x15] = 0.0f; // DAT_00e2b1a4
                    } else {
                        // FUN_005e5c60: update blend weights
                        FUN_005e5c60(currentSlot + 0xf, ((float*)currentSlot)[0x14], *(float*)(currentSlot->animData + 0x3c), currentSlot + 0x15);
                        outputWeight = modifiedWeight;
                    }
                } else {
                    // outputWeight >= 0
                }

                // Store updated time
                ((float*)currentSlot)[0x14] = local_30;

                // Check for animation play condition
                if (bVar3 || (currentSlot->field_50 != 0 && *(float*)(currentSlot->field_50 + 0x50) < 0.0f)) {
                    // FUN_005e5b00: trigger animation play
                    FUN_005e5b00(*(float*)(currentSlot->animData + 0xc), // duration?
                                  *(float*)(currentSlot->animData + 8),   // startTime?
                                  *(float*)(currentSlot->animData + 0x14)); // endTime?
                } else {
                    outputWeight = 0.0f;
                }
            }

            // Bit twiddling for some state flags in slot
            uint8_t byteVal = *(uint8_t*)((int)currentSlot + 0x5a);
            uint16_t flagMask = (byteVal & 3) * 2;
            uint16_t newFlags = (uint16_t)result & 0xff01 | flagMask;
            // This is writing to something, but not clear. Possibly result overwritten by local_14.
            result = CONCAT31((int8_t)flagMask, result); // simplified

            // Additional flag processing (see original)
            if ((int8_t)flagMask == 2) {
                newFlags = (newFlags & 0xfff9) | 0x80;
            }

            // Call finalization function
            int local_20 = (int)currentSlot;
            int local_1c = (int)currentSlot->animData + 0x20; // some offset
            FUN_005f1f80(&local_20, &local_1c); // Note: actual signature may differ

            result = 1;
        }
    }
    return result;
}