// FUNC_NAME: DamageComponent::updateDamageResistances
// Address: 0x005dd660
// Called from FUN_005dc9b0 (likely owner update)
// Processes 5 damage modifier layers (starting at +0x38, each 0x68 bytes)
// Combines multipliers to compute final shield/health resistances (stored at +0x284, +0x288, +0x28c, +0x290, +0x294)
// Uses a global random data table (DAT_01223504) for a per-frame random check

class DamageComponent {
public:
    // Member offsets (relative to this)
    // +0x00: unknown
    // +0x0C: float layerActiveFlag[?]  // actually per-layer, see loop
    // +0x20: char layerIsActive[5]
    // +0x21: char layerFlag1[5]
    // +0x22: char layerFlag2[5]
    // +0x23: char layerFlag3[5]
    // +0x38: per-layer data start (first group)
    // Each group size = 0x68 (26 floats)
    // Within group: +0x0C = float disableMarker (compared to -NAN)
    //                +0x20 = char isMultiply? (used to branch)
    //                +0x21..+0x23 = additional flags
    //                +0x38 = float multiplierX
    //                +0x3C = float multiplierY
    //                +0x4C = float extraMultiplier (only used in one branch)
    // +0x214: int currentModeIndex? (if -1 then uses default values)
    // +0x240: float baseMultiplierA
    // +0x244: float baseMultiplierB (used as default)
    // +0x254: float baseMultiplierC? (used for +0x294)
    // +0x27C: float scaleFactorA
    // +0x284: float resultResistanceA (final)
    // +0x288: float resultResistanceB
    // +0x28C: float resultResistanceC
    // +0x290: float resultResistanceD
    // +0x294: uint resultCap (clamped to <=96000)
    // +0x298: char useDefaultFlag (if true, resets some values to default)

    void updateDamageResistances() {
        char cVar1;
        int iVar2;
        float* pfVar3;
        float fTemp;
        uint randomValue;

        iVar2 = DAT_01223504; // Global pointer to random data table (byte + int array)
        randomValue = 0;
        cVar1 = FUN_005e73f0(&randomValue, 0); // Some RNG or hash function, writes to randomValue
        if ((cVar1 != '\0') && ((randomValue ^ 0xad103100) < (uint)*(byte *)(iVar2 + 0x1c))) {
            // If random check passes, update an offset from the table
            *(undefined4 *)(this + 700) =
                *(undefined4 *)(*(int *)(iVar2 + 4 + ((randomValue ^ 0xad103100) & 0xff) * 4) + 0x68);
        }

        fTemp = 0.0f;
        if (*(int *)(this + 0x214) == -1) {
            // No special mode: use default globals for the two base resistances
            *(float*)(this + 0x284) = DAT_00e2e780; // global default A
            *(float*)(this + 0x288) = DAT_00e2b1a4; // global default B
        } else {
            // Use custom mode: call helper that might update internal state
            FUN_005dd340(); // likely "recalculateBaseValues" or similar
            if (*(char *)(this + 0x298) == '\0') {
                // Not using default flag: compute from stored values
                *(float*)(this + 0x288) = *(float*)(this + 0x244);
                *(float*)(this + 0x284) = *(float*)(this + 0x29c) * *(float*)(this + 0x27c) * *(float*)(this + 0x240);
            } else {
                // Using default flag: reset A to zero, B from stored
                *(float*)(this + 0x284) = 0.0f;
                *(float*)(this + 0x288) = *(float*)(this + 0x244);
            }
        }

        // Initialize working copies from current resistances
        *(float*)(this + 0x28c) = *(float*)(this + 0x284);
        *(float*)(this + 0x294) = *(float*)(this + 0x254);
        pfVar3 = (float*)(this + 0x38);
        *(float*)(this + 0x290) = *(float*)(this + 0x288);

        iVar2 = 5; // loop over 5 layers
        do {
            // Check if this layer's disable marker is not -NAN (i.e., layer is active)
            // pfVar3[-0xb] is at this+0x0C (since pfVar3 points to this+0x38, -44 bytes = this+0x0C)
            if (*(float*)(pfVar3 - 0xb) != -NAN) {
                cVar1 = FUN_005dd340(); // Re-evaluate layer state? Returns bool
                if (cVar1 != '\0') {
                    if (*(char *)(pfVar3 - 6) == '\0') {
                        // Standard multiplication branch
                        // pfVar3[0] is at this+0x38, pfVar3[1] at this+0x3C
                        *(float*)(this + 0x284) = *pfVar3 * *(float*)(this + 0x284);
                        *(float*)(this + 0x28c) = *(float*)(this + 0x28c) * *pfVar3;
                        *(float*)(this + 0x288) = *(float*)(this + 0x288) * pfVar3[1];
                        *(float*)(this + 0x290) = *(float*)(this + 0x290) * pfVar3[1];
                    } else {
                        // Alternative multiplication (non-standard)
                        *(float*)(this + 0x28c) = *(float*)(this + 0x28c) * *pfVar3;
                        *(float*)(this + 0x290) = pfVar3[1] * *(float*)(this + 0x290);
                        *(float*)(this + 0x294) = pfVar3[5]; // Extra multiplier for cap
                    }
                    // Additional flags at this+0x23, this+0x22, this+0x21
                    if (*(char *)((int)pfVar3 + -0x15) != '\0') {
                        if (*(char *)((int)pfVar3 + -0x16) == '\0') {
                            if (*(char *)((int)pfVar3 + -0x17) != '\0') {
                                *(float*)(this + 0x288) = 0.0f; // Zero out B resistance
                            }
                        } else {
                            // Mark this layer as disabled (set marker to -NAN)
                            *(float*)(pfVar3 - 0xb) = -NAN;
                        }
                    }
                }
            }
            pfVar3 = pfVar3 + 0x1a; // Advance to next layer (26 floats = 0x68 bytes)
            iVar2 = iVar2 + -1;
        } while (iVar2 != 0);

        // Clamp all final resistances to zero if they are negative
        if (*(float*)(this + 0x284) <= 0.0f && 0.0f != *(float*)(this + 0x284)) {
            *(float*)(this + 0x284) = 0.0f;
        }
        if (*(float*)(this + 0x288) <= 0.0f && 0.0f != *(float*)(this + 0x288)) {
            *(float*)(this + 0x288) = 0.0f;
        }
        if (*(float*)(this + 0x28c) <= 0.0f && 0.0f != *(float*)(this + 0x28c)) {
            *(float*)(this + 0x28c) = 0.0f;
        }
        if (*(float*)(this + 0x290) <= 0.0f && 0.0f != *(float*)(this + 0x290)) {
            *(float*)(this + 0x290) = 0.0f;
        }

        // Cap the uint at +0x294 to 96000 (0x17700)
        if (96000 < *(uint *)(this + 0x294)) {
            *(uint*)(this + 0x294) = 96000;
        }

        return; // return value 0x17701 is not returned; function returns void but returns int 0x17701? Original returns 0x17701, maybe caller uses it
    }
};