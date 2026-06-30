// FUNC_NAME: SoundMixer::processMixChannels
// Address: 0x00614f80
// Role: Mixes two audio streams (param1 and param2) with sub-channels, applying effects and crossfading.
// Uses global array gSoundEntries[4096] (0x38 bytes each) for source data.
// Profiling via QueryPerformanceCounter.

#define MAX_SOUND_ENTRIES 0x1000 // 4096
#define SOUND_ENTRY_SIZE 0x38

// Forward declarations of helper functions (from other decompiled units)
int getSoundData(uint entryIndex, int subIndex, int channelIndex, void* buffer);
int getSoundDataShort(uint entryIndex, int subIndex, void* buffer);
int convertFrequency(short freq);
void* allocateAudioBuffer(void* owner, int size, int alignment);
void releaseAudioBuffer(void* buffer, int unused);
void applyEffect(void* buffer, short param2, short param3, void* sourceBuf, short param5, int param6, int param7);
void mixBuffer(void* output, int input, int format, void* otherOutput, int otherInput, short param6, short param7);
void releaseMixBuffer(void* buffer, int param2, int param3, int param4);
void freeSoundBuffer(void* buffer);

// Global profiling accumulators
extern LARGE_INTEGER gProfileAccumulator; // DAT_01205940 (low) and DAT_01205944 (high)

// Global sound entries table
extern byte gSoundEntries[MAX_SOUND_ENTRIES * SOUND_ENTRY_SIZE]; // DAT_011a0f28

// Global allocator interface (vtable pointer)
extern void** gAllocator; // DAT_01205868

int processMixChannels(uint source1Index, uint source2Index, int extraParam)
{
    byte bVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    bool bVar5;
    short sVar6;
    byte* puVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    undefined4 uVar11;
    undefined4 uVar12;
    bool bVar13;
    bool bStack_d5;
    int iStack_d4;
    undefined4 uStack_d0;
    int iStack_cc;
    int iStack_c8;
    LARGE_INTEGER LStack_c0;
    uint uStack_b8;
    int iStack_b4;
    undefined1 auStack_b0[2];
    short sStack_ae;
    short sStack_ac;
    undefined2 uStack_aa;
    int iStack_a8;
    uint uStack_a4;
    undefined4 uStack_90;
    int iStack_88;
    undefined4 uStack_84;
    undefined4 uStack_6c;
    LARGE_INTEGER local_68;
    undefined4 uStack_5c;
    undefined4 uStack_58;
    undefined4 uStack_54;
    undefined1 auStack_50[2];
    undefined4 uStack_4e;
    int iStack_48;
    uint uStack_44;
    int iStack_28;
    undefined4 uStack_24;
    undefined4 uStack_c;

    // Start profiling
    QueryPerformanceCounter(&local_68);
    uStack_b8 = local_68.s.LowPart;
    iStack_b4 = local_68.s.HighPart;

    if (source2Index >= MAX_SOUND_ENTRIES) {
        return 0;
    }

    byte* entry2 = &gSoundEntries[source2Index * SOUND_ENTRY_SIZE];
    if (entry2 == nullptr) {
        return 0;
    }

    // Check if entry2 has more than 1 channel/sub-stream
    if (entry2[0] <= 1) { // byte at offset 0 is count? Actually it's compared to 1.
        return 0;
    }

    bVar1 = entry2[1]; // sub-channel count for source2

    byte* entry1;
    if (source1Index < MAX_SOUND_ENTRIES) {
        entry1 = &gSoundEntries[source1Index * SOUND_ENTRY_SIZE];
    } else {
        entry1 = nullptr;
    }

    LStack_c0.s.LowPart = entry1[1]; // sub-channel count for source1
    bVar13 = false;
    uStack_d0 = 0;
    iStack_c8 = 0;
    iStack_cc = 0;

    if (LStack_c0.s.LowPart == 0) {
        goto skipLoop;
    }

    do {
        // Get data from source1 for the current sub-channel
        iVar10 = iStack_c8;
        uVar12 = uStack_d0;
        iVar8 = getSoundData(source1Index, 10, iStack_cc, auStack_b0); // 10 likely a format/type
        if (iVar8 == 0) {
            return 0;
        }

        iVar9 = bVar1 - 1;
        iVar8 = iStack_cc;
        if ((iStack_cc < iVar9) || (iVar8 = iVar9, iStack_cc <= iVar9)) {
            // Use data from source2 (crossfade region or secondary stream)
            if (bVar13) {
                // Release old buffer
                (*(void (**)(void*, int))(*gAllocator + 4))(uStack_d0, 0);
                uStack_d0 = 0;
                bVar13 = false;
            }
            iVar10 = getSoundDataShort(source2Index, 9, iVar8, auStack_50);
            if (iVar10 == 0) {
                freeSoundBuffer(auStack_b0);
                return 0;
            }
            uVar12 = uStack_c;
            iVar10 = iStack_28;
            bVar2 = false;
            bVar4 = bVar13;
        } else {
            // Use data from source1 again (loop back or mirror)
            iVar8 = getSoundDataShort(source1Index, 9, iStack_cc + -1, auStack_50);
            if (iVar8 == 0) {
                freeSoundBuffer(auStack_b0);
                return 0;
            }
            uStack_44 = uStack_a4 & 0xffffffef;
            iStack_48 = 3;
            uStack_d0 = 0;
            iStack_c8 = 0;
            bVar4 = false;
            bVar2 = bVar13;
        }

        uVar11 = uVar12;
        if ((uStack_44 & 0x10) != 0) {
            // Allocate buffer if needed
            uStack_5c = 2;
            uStack_58 = 0x10;
            uStack_54 = 0;
            uVar11 = (*(void* (*)(void*, void*))(*gAllocator))(uStack_24, &uStack_5c);
            if (bVar2) {
                (*(void (**)(void*, int))(*gAllocator + 4))(uVar12, 0);
            }
            bVar2 = true;
            iVar10 = iStack_28;
        }

        sVar6 = sStack_ae;
        // Check if format/identity changed
        if ((uStack_4e != sStack_ae) || (uStack_4e._2_2_ != sStack_ac)) {
            if ((iStack_a8 == 0x1e) || (iStack_a8 == 0x1f) || (iStack_a8 == 0x20) ||
                (iStack_a8 == 0x21) || (iStack_a8 == 0x22) || (iStack_a8 == 0x23)) {
                iStack_d4 = convertFrequency(sStack_ae);
                uVar12 = convertFrequency(sVar6);
            } else {
                iStack_d4 = iStack_88;
                uVar12 = uStack_84;
            }
            uVar12 = allocateAudioBuffer(uVar12);
            if (((iStack_48 == 3) || (iStack_48 == 2)) && (extraParam != 0)) {
                applyEffect(uVar12,
                           (short)(sStack_ac), (short)(sStack_ae),
                           (short)(uStack_aa), (short)(sStack_ac), // note: CONCAT22 usage
                           uVar11, uStack_4e, iVar10, extraParam);
            }
            if (bVar2) {
                (*(void (**)(void*, int))(*gAllocator + 4))(uVar11, 0);
            }
            bVar2 = true;
            iVar10 = iStack_d4;
        }

        iVar8 = iStack_a8;
        bVar5 = true;
        bVar3 = bVar2;
        bVar13 = bVar4;

        if ((int)(uint)bVar1 < (int)LStack_c0.s.LowPart) {
            bVar3 = false;
            uStack_d0 = uVar12;
            iStack_c8 = iVar10;
            bVar13 = bVar2;
        }

        iStack_d4 = uVar12;
        bStack_d5 = bVar3;

        // If sub-channel format changed and was previously non-mixable, perform mixing
        if ((iStack_a8 != iStack_48) &&
            (((((iStack_a8 == 0x1e) || (iStack_a8 == 0x1f) || (iStack_a8 == 0x20) ||
                (iStack_a8 == 0x21) || (iStack_a8 == 0x22) || (iStack_a8 == 0x23)) &&
              ((iStack_48 != 0x1e) && (iStack_48 != 0x1f) && (iStack_48 != 0x20) &&
               (iStack_48 != 0x21) && (iStack_48 != 0x22) && (iStack_48 != 0x23))))) {
            bStack_d5 = (uStack_a4 & 0x10) == 0;
            if (bStack_d5) {
                iStack_d4 = uStack_6c;
            } else {
                iStack_d4 = allocateAudioBuffer(uStack_84);
            }
            bStack_d5 = !bStack_d5;
            mixBuffer(iStack_d4, iStack_88, iVar8, uVar12, iVar10,
                     (short)(sStack_ac), (short)(sStack_ae),
                     (short)(uStack_aa), (short)(sStack_ac));
            iVar10 = iStack_88;
            bVar5 = bStack_d5;
            if (bVar3) {
                (*(void (**)(void*, int))(*gAllocator + 4))(uVar12, 0);
                iVar10 = iStack_88;
            }
        }

        if ((uStack_a4 & 0x10) == 0) {
            if (bVar5) {
                releaseMixBuffer(uStack_6c, iStack_88, iVar10, uStack_90);
            }
            uVar12 = iStack_d4;
            if (bStack_d5) goto LAB_0061540a;
        } else {
            if (iVar10 == iStack_88) goto LAB_00615403;
            uVar12 = allocateAudioBuffer(uStack_84);
            releaseMixBuffer(uVar12, iStack_88, iVar10, uStack_90);
            if (bStack_d5) {
                (*(void (**)(void*, int))(*gAllocator + 4))(iStack_d4, 0);
            }
LAB_0061540a:
            (*(void (**)(void*, int))(*gAllocator + 4))(uVar12, 0);
        }

LAB_00615403:
        freeSoundBuffer(auStack_50);
        freeSoundBuffer(auStack_b0);
        iStack_cc = iStack_cc + 1;
    } while (iStack_cc < (int)LStack_c0.s.LowPart);

    if (bVar13) {
        (*(void (**)(void*, int))(*gAllocator + 4))(uStack_d0, 0);
    }

skipLoop:
    // End profiling
    QueryPerformanceCounter(&LStack_c0);
    bool carry = (LStack_c0.s.LowPart < uStack_b8);
    uint diffLow = LStack_c0.s.LowPart - uStack_b8;
    uint diffHigh = (LStack_c0.s.HighPart - iStack_b4) - (carry ? 1 : 0);

    // Accumulate time
    gProfileAccumulator.s.LowPart += diffLow;
    gProfileAccumulator.s.HighPart += diffHigh + (uint)carry;

    return 1;
}