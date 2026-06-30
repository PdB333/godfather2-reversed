// FUNC_NAME: Modulator::update
// Function address: 0x004ece90
// Role: Updates the modulator's current value and applies it to the audio parameter based on input data (pitch, flags, etc.)

#include <cstdint>

// External global variables (constants)
extern float DAT_00e2b1a4;   // likely frame delta time
extern float DAT_00e2ee80;   // unknown constant
extern float DAT_00e44578;   // float constant (e.g., 2.0 or similar)
extern float DAT_00e44564;   // float constant (e.g., 0.0 or 1.0)
extern float DAT_00e44584;   // float constant (e.g., 0.0)
extern float DAT_00e2b334;   // float constant (multiplier)
extern int DAT_012234a0;     // pointer to global structure (e.g., AudioSystem)
extern int DAT_01205504;     // global this pointer (set during update)
extern int DAT_01227870;     // flags (bit 0 for GUID initialization)
extern int DAT_01227860;     // some string or handle
extern int DAT_0120588c;     // integer (frame rate denominator)
extern int DAT_01205898;     // integer (frame rate denominator)

// Forward declarations of called functions
void __stdcall FUN_00488a10(uint soundId);  // init sound?
void __cdecl FUN_004ecd50(void* pData, float value); // unknown update helper
void __cdecl FUN_00488210(int param); // unknown helper
void __cdecl FUN_004d9500(const char* guid); // set/get GUID?
char __cdecl FUN_00420950(void* param); // check something
void __cdecl FUN_0048a3b0(float a1, float a2, float a3, float a4, float a5, uint a6, uint a7, uint a8, void* ptr, uint a10, int a11, int a12, int a13, void* a14, uint a15, char a16); // main apply function (likely setSoundParameter)

// Class layout for Modulator
class Modulator {
public:
    // vtable at +0x00 (not used in this function)
    void* m_pUnknown;          // +0x04
    float m_fVecX;            // +0x10
    float m_fVecY;            // +0x14
    float m_fVecZ;            // +0x18
    float m_fVecW;            // +0x1c
    void* m_pHandle;          // +0x20
    ModulatorData* m_pData;   // +0x24
    float m_fField28;         // +0x28 (copied from global)
    float m_fField2C;         // +0x2c (copied from global)
    float m_fCurrentValue;    // +0x30
    float m_fField34;         // +0x34
    float m_fAccumulator;     // +0x38
    char m_bField3C;          // +0x3c (byte used in apply call)
};

// Class for the data object at m_pData
class ModulatorData {
public:
    // layout inferred from offsets:
    // +0x00: unknown
    // +0x04: unknown (used in FUN_00488a10 call)
    // +0x10: float m_fMaxModulation (or base value)
    // +0x2c: ushort m_uFlags
    // +0x2f: byte m_bMask (bit 0: extra flags, bit1, bit2)
    // +0x40: float m_fThreshold1
    // +0x4c: float m_fMinValue
    // +0x50: float m_fRate
    // +0x54: int m_iTime
    uint m_uUnknown00;
    uint m_uUnknown04; // used as argument to FUN_00488a10
    // ... padding ...
    float m_fBase;              // +0x10
    // ... padding ...
    ushort m_uFlags;            // +0x2c
    // some bytes ...
    byte m_bMask;               // +0x2f
    float m_fThreshold;         // +0x40
    float m_fMinValue;          // +0x4c
    float m_fRate;              // +0x50
    int m_iTime;                // +0x54
};

// Reconstructed function
void __fastcall Modulator::update(void* thisPtr) {
    Modulator* self = (Modulator*)thisPtr;
    ModulatorData* data;
    float fBase, fCurrent, fRate, fMin, fThreshold;
    float fDelta, fMod, fTarget, fAccumTemp;
    float fTemp1, fTemp2, fTemp3;
    bool bExtraFlag;
    int iTime;
    uint uFlags;
    byte bMask;
    float fRatio, fScale;
    float* pVector;

    // Use global struct
    int audioSystem = DAT_012234a0; // assume this is a pointer to some global audio system struct

    // If m_pHandle is null, return
    if (self->m_pHandle == 0) {
        self->m_pHandle = 0; // redundant but keep
        return;
    }

    // Initialize sound? Pass sound ID from data
    FUN_00488a10(self->m_pData->m_uUnknown04);

    fDelta = DAT_00e2b1a4; // likely frame delta time
    DAT_01205504 = (int)self; // store global pointer

    // Check if a function pointer (or vtable entry?) at self+0x54 is equal to some address (LAB_004ee6c0)
    // Using a common pattern: maybe check if a callback has been initialized
    if (*(void**)((int)self + 0x54) != (void*)0x004ee6c0) {
        *(void**)((int)self + 0x54) = (void*)0x004ee6c0;
        // Copy constants from global
        *(float*)((int)self + 0x28) = DAT_00e2e24c;
        *(float*)((int)self + 0x2c) = DAT_00e2e250;
    }

    data = self->m_pData;
    uFlags = data->m_uFlags;

    // If another flag (0x200) is set, change base delta
    if ((uFlags & 0x200) != 0) {
        fDelta = DAT_00e44764;
    }

    fCurrent = self->m_fCurrentValue;

    // Compute modulation ratio
    fBase = data->m_fBase / fDelta; // fBase is at data+0x10
    fTemp1 = 0.0f;
    fTemp2 = 0.0f;

    // Compute something from audioSystem (offset 0x1c and 0x2c)
    // The extraout_ECX is the audioSystem pointer (returned by FUN_00488a10? but we assume it's same)
    if (*(int*)(audioSystem + 0x1c) != 0) {
        fTemp2 = (float)*(int*)(*(int*)(audioSystem + 0x1c) + 0x18) * *(float*)(audioSystem + 0x2c);
    }

    fMod = (fCurrent / fTemp2) * fBase; // fMod is the computed modulation amount

    // Determine local_6c and local_64 based on flags
    int local_6c = 0;
    if ((uFlags & 1) != 0) {
        local_6c = 1;
    } else if ((uFlags & 2) != 0) {
        local_6c = 2;
    }

    int local_64 = 0;
    if ((uFlags & 8) != 0) {
        local_64 = 1;
    } else if ((uFlags & 0x10) != 0) {
        local_64 = 2;
    }

    // Compute a scaled value
    float scaledValue = fBase * DAT_00e2ee80;
    pVector = (float*)(-(int)((uFlags & 0x80) != 0) & (int)&scaledValue); // conditionally assign pointer

    // Some bit operations on local_54
    uint local_54 = (uint)(data->m_uFlags >> 6) & 0xffffff01; // unclear

    float local_70 = scaledValue;
    float local_44 = scaledValue; // duplicate

    // Call helper
    FUN_004ecd50(data, fCurrent);

    // Now the main block: if data->m_fMinValue != 0.0 and fMin < data->m_fThreshold and fMin < local_70
    fMin = data->m_fMinValue;
    fThreshold = data->m_fThreshold;
    if ((fMin != 0.0f) && (0.0f < fMin) && (0.0f < local_70)) {
        // Compute something
        fTemp1 = local_70;
        FUN_00488210(audioSystem + 0x1c);
        data = self->m_pData;
        fTemp1 = fTemp1 * fMod;

        fRate = data->m_fRate;
        fTemp2 = fRate * (local_70 / fThreshold); // local_70 is same as scaledValue? but used as fThreshold?
        bMask = data->m_bMask;
        // Determine bExtraFlag
        bool bExtraFlag = false;
        if ((fTemp2 < fTemp1) && ((bMask & 1) != 0)) {
            bExtraFlag = true;
        }

        // Complicated condition: if (fTemp2 < fTemp1) OR bExtraFlag OR ( (~(bMask>>1) & 1) != 0)
        if ((fTemp2 < fTemp1) || bExtraFlag || ((~(bMask >> 1) & 1) != 0)) {
            fTemp3 = fTemp1;
            FUN_00488210(audioSystem + 0x1c);
            data = self->m_pData;

            fAccumTemp = self->m_fAccumulator;
            iTime = data->m_iTime;
            fTarget = (float)iTime;
            if (iTime < 0) {
                fTarget = fTarget + DAT_00e44578; // likely 2.0f or something
            }

            float ratio2 = data->m_fRate / fThreshold;
            float fInputAccum = self->m_fField34 + self->m_fAccumulator;
            self->m_fAccumulator = fInputAccum; // store back

            float computed = fTarget * fTemp3 * fMod + fTemp3; // fTemp1 is same as fTemp3
            float local_3c = 0.0f;
            float* pLocal_58 = &local_3c; // pointer to stack variable

            float temp = 0.0f;
            if (!bExtraFlag) {
                temp = (data->m_fMinValue / fThreshold) * fInputAccum;
            }

            fRate = data->m_fMinValue; // reuse fRate as fMin
            float fModRatio = computed / local_70; // local_70 is scaledValue? actually it's the old fTemp1?
            if (fRate < 0.0f) {
                temp = fModRatio + temp;
            }

            // Conditional assignment
            if ((fRate <= 0.0f) || (temp * local_70 <= computed)) {
                local_3c = temp;
                if ((fRate < 0.0f) && (temp * local_70 < 0.0f)) {
                    local_3c = temp * local_70 + fModRatio;
                    self->m_fAccumulator = DAT_00e44564 - (temp / fRate) * local_70 * fThreshold;
                }
            } else {
                self->m_fAccumulator = ((temp - fModRatio) / fRate) * fThreshold;
                local_3c = temp - fModRatio;
            }

            // Copy some value
            *(uint*)((int)self + 0x28) = *(uint*)((int)self + 0x28); // no-op? Actually it's just accessing
        } else {
            // If condition fails, set local_6c to 1 if bMask bit2 is set
            if ((bMask & 4) != 0) {
                local_6c = 1;
            }
            local_70 = fTemp2; // update local_70
        }
    }

    // After the block, check pVector pointer (if flags had 0x80)
    if ((pVector != nullptr) && (pVector[0] != 0.0f || pVector[1] != 0.0f)) {
        // Check a GUID flag
        if ((DAT_01227870 & 1) == 0) {
            DAT_01227870 |= 1;
            FUN_004d9500("{66EB9CC0-9CC0-66EB-C09C-EB66C09CEB66}");
        }

        // Another condition: self->m_pUnknown != 0 and check something
        if ((self->m_pUnknown != 0) &&
            (FUN_00420950(&DAT_01227860) != '\0')) {
            float scale = fBase * DAT_00e2b334; // fBase was m_pData->m_fBase / fDelta
            // Save current vector
            float vecX = self->m_fVecX;
            float vecY = self->m_fVecY;
            float vecZ = self->m_fVecZ;
            float vecW = self->m_fVecW;

            setVector(self, 0.0f); // set m_fVecX..W to 0,0,0,DAT_00e44584
            self->m_fVecX = 0.0f;
            self->m_fVecY = 0.0f;
            self->m_fVecZ = 0.0f;
            self->m_fVecW = DAT_00e44584;

            // Set pVector values
            pVector[0] = scale;
            pVector[1] = scale;

            // Call main apply function with computed parameters
            FUN_0048a3b0(
                scale,                     // a1
                DAT_00e2b1a4 - scale,      // a2 (delta - scale)
                local_70,                  // a3 (maybe threshold)
                fCurrent,                  // a4
                fMod,                      // a5
                self->m_pHandle,           // a6
                local_6c,                  // a7
                local_64,                  // a8
                nullptr,                   // ptr (pVector was used but set to null)
                local_54,                  // a10
                0, 0, 0,                   // unused
                pLocal_58,                 // a14 (pointer to local_3c)
                *(uint*)((int)self + 0x2c), // a15
                self->m_bField3C           // a16 (byte)
            );

            // Restore vector
            self->m_fVecX = vecX;
            self->m_fVecY = vecY;
            self->m_fVecZ = vecZ;
            self->m_fVecW = vecW;

            // Reset pVector
            pVector = nullptr;
        }
    }

    // Unconditional call to apply function (with zero/set to default)
    FUN_0048a3b0(
        0.0f,                    // a1
        1.0f,                    // a2 (0x3f800000)
        local_70,                // a3
        fCurrent,                // a4
        fMod,                    // a5
        self->m_pHandle,         // a6
        local_6c,                // a7
        local_64,                // a8
        pVector,                 // ptr (likely null)
        local_54,                // a10
        0, 0, 0,                 // unused
        pLocal_58,               // a14
        *(uint*)((int)self + 0x2c),
        self->m_bField3C
    );

    // Reset some fields in audioSystem
    fDelta = DAT_00e2b1a4;
    if (*(int*)(audioSystem + 0x54) != 0) {
        uint uDiv1 = DAT_0120588c;
        uint uDiv2 = DAT_01205898;
        *(int*)(audioSystem + 0x54) = 0;
        *(float*)(audioSystem + 0x28) = fDelta / (float)uDiv1;
        *(float*)(audioSystem + 0x2c) = fDelta / (float)uDiv2;
    }

    self->m_pHandle = 0; // clear handle
    return;
}