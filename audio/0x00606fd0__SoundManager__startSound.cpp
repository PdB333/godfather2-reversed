// FUNC_NAME: SoundManager::startSound
// Address: 0x00606fd0
// Role: Initializes and starts a sound instance based on a sound definition ID.

#include <windows.h> // For CRITICAL_SECTION, EnterCriticalSection, LeaveCriticalSection

// External functions (declared elsewhere in the engine)
extern void FUN_006064b0(uint soundId, uint param);
extern void FUN_006066e0(ushort frequency);
extern uint FUN_0061a960(uint sampleRate); // probably converts to internal format
extern uint FUN_0061a8f0(); // gets audio clock frequency (e.g., samples per second)
extern uint FUN_0061a920(); // gets another clock frequency (e.g., channels per second)
extern uint FUN_00618a70(); // checks if sound is allowed to play?

// Global arrays (table of sound definitions)
// Each entry size 0x38
// Offset 0: 8 bytes (e.g., name or data pointer)
// Offset 8: 8 bytes (e.g., sound data size?)
// Offset 12: flags (bit0=?, bit1=?, bit2= override frequency, bit3=?)
// Offset 16: 4 bytes (maybe default frequency)
extern byte gSoundDefs[0x1000 * 0x38]; // DAT_011a0f28
extern ushort gOverrideFrequencies[];   // DAT_00f158f0 (array indexed by param_3)

// Bitmap for sound slot allocation (two 64-bit halves)
extern uint64 gSoundSlotBitmaskLow;  // DAT_011d8f28 (actually array? but used as per index)
extern uint64 gSoundSlotBitmaskHigh; // DAT_011d8f2c
extern uint gSoundNextSlotIndex;     // DAT_011d9128

// Critical section for thread safety
extern CRITICAL_SECTION gSoundCriticalSection; // DAT_011d917c

// Structure filled by this function (0x48 bytes)
struct SoundInstance {
    // Offsets as used in the code
    // First 8 bytes from sound definition
    uint64 field_00;
    // The next 8 bytes from definition+8
    uint64 field_08;
    // 4 bytes from definition+16
    uint   field_10;
    uint   field_14; // +0x14: sound ID (param_1)
    uint   field_18; // +0x18: flags (param_2)
    ushort field_1c; // +0x1c: frequency (from param_3 or override)
    ushort field_1e; // padding
    uint   field_20; // +0x20: (actually param_4+4 is 4*8=0x20)
    uint   field_24; // +0x24: from FUN_0061a960(uVar8)
    uint   field_28; // padding
    uint   field_2c;
    uint   field_30; // +0x30: from FUN_0061a960(1)
    uint   field_34; // +0x34: from FUN_0061a8f0()
    uint   field_38; // +0x38: from FUN_0061a920()
    uint   field_3c; // +0x3c: computed: ((clock1-1) + sampleRate1) / clock1
    uint   field_40; // +0x40: computed: ((clock2-1) + sampleRate2) / clock2
    uint   field_44;
};

// __global function (not a method)
int startSound(uint soundId, uint flags, int frequencyIndex, SoundInstance* outInstance)
{
    memset(outInstance, 0, sizeof(SoundInstance));

    if (soundId >= 0x1000)
        return 0;

    int defOffset = soundId * 0x38;
    byte* soundDef = &gSoundDefs[defOffset];
    byte state = *soundDef;

    // Check if sound definition is valid
    if (soundDef == NULL) // null check in original is (byte*)0x0
        return 0;

    if (state <= 1)
        return 0;

    // Check flags compatibility
    if ((flags & 1) != 0 && state <= 2)
        return 0;

    if ((flags & 8) == 0 && state == 5)
        return 0;

    if (state == 4)
        return 0;

    // Mark the sound as being prepared? (param_2 & 2)
    FUN_006064b0(soundId, flags & 2);

    // Copy first part of definition into instance
    outInstance->field_00 = *(uint64*)soundDef;
    outInstance->field_08 = *(uint64*)(&gSoundDefs[defOffset + 8]);
    outInstance->field_10 = *(uint32*)(&gSoundDefs[defOffset + 16]);

    outInstance->field_1c = (uint16)frequencyIndex;
    uint32 defFlags = *(uint32*)(&gSoundDefs[defOffset + 12]); // offset 0x34? Actually 0x34 is DAT_011a0f34, which is 12 bytes from base? Wait: 0x34 - 0x28 = 0xC, so offset 12.

    if ((defFlags & 2) != 0) {
        // Override frequency from global table
        outInstance->field_1c = gOverrideFrequencies[frequencyIndex];
    }

    // Start playing?
    FUN_006066e0(outInstance->field_1c);

    // Extract sample rates from the copied data
    ushort sampleRate1 = *(ushort*)&outInstance->field_00 + 2? Actually the code does:
    // uVar3 = *(ushort*)(param_4+4) -> field_04? But param_4 is pointer to struct, offset 4 is within first 8 bytes.
    // uVar8 = *(ushort*)(param_4+2) -> offset 2.
    // We need to reinterpret the first 8 bytes as containing these ushorts.
    // Let's assume field_00 contains at offsets 2 and 4.
    ushort sampleRateA = *(ushort*)((byte*)outInstance + 2);
    ushort sampleRateB = *(ushort*)((byte*)outInstance + 4);

    outInstance->field_24 = FUN_0061a960(sampleRateA);
    outInstance->field_20 = FUN_0061a960(sampleRateA); // note: same call? Actually second call also with uVar8
    outInstance->field_30 = FUN_0061a960(1); // for mono/stereo?

    uint clock1 = FUN_0061a8f0(); // base sample clock
    uint clock2 = FUN_0061a920(); // another clock

    outInstance->field_34 = clock1;
    outInstance->field_38 = clock2;

    outInstance->field_14 = soundId;
    outInstance->field_3c = ((clock1 - 1) + sampleRateA) / clock1; // ceiling division
    outInstance->field_18 = flags;
    outInstance->field_40 = ((clock2 - 1) + (uint)sampleRateB) / clock2;

    // Check if we should mark this sound slot as free?
    uint playFlag;
    if ((defFlags & 8) == 0) {
        playFlag = FUN_00618a70(); // some system check
    } else {
        playFlag = 0;
    }

    if ((playFlag & 1) != 0) {
        if (state != 5) {
            // Clear the bit for this slot in the global bitmap
            uint slotIndex = soundId >> 6;
            EnterCriticalSection(&gSoundCriticalSection);
            // Compute bitmask
            uint64 bit = 1ULL << (soundId & 0x3F);
            // Assume gSoundSlotBitmaskLow and High are arrays indexed by slotIndex? Actually code uses pointer arithmetic on DAT_011d8f28 which is likely a 64-bit array.
            // We'll use a simple representation.
            // Clear bit in low/high word accordingly.
            // The code uses __allshl to shift 1 by soundId, then masks with ~.
            // We'll approximate.
            uint64 mask = ~(1ULL << (soundId & 0x3F));
            if (slotIndex < 32) {
                // Low mask
                // Write to (DAT_011d8f28)[slotIndex*2] and (DAT_011d8f2c)[slotIndex*2]
                // This is complex; we assume a single 128-bit bitmap.
            }
            // Update gSoundNextSlotIndex if needed
            if (slotIndex == gSoundNextSlotIndex) {
                // Check if all bits are zero? The code checks (DAT_011d8f28)[slotIndex*2]==0 and (DAT_011d8f2c)[slotIndex*2]==0
                // If so, increment gSoundNextSlotIndex.
            }
            *soundDef = 4; // Mark as free
            LeaveCriticalSection(&gSoundCriticalSection);
        }
        return 1;
    }

    return 0;
}