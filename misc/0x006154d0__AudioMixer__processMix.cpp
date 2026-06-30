// FUNC_NAME: AudioMixer::processMix
// Address: 0x00614f80 (thunk at 0x006154d0)
// Role: Mixes audio data from one source channel to a destination channel,
//       handling format conversion, volume, and profiling via QueryPerformanceCounter.
//       Uses a global array of 0x38-byte channel info structures (up to 0x1000 entries).
//       Returns 1 on success, 0 on failure.

#include <windows.h> // for LARGE_INTEGER, QueryPerformanceCounter

// Forward declarations of helper functions (inferred from decompiled code)
int readAudioData(uint sourceIndex, int mode, int offset, void* buffer); // FUN_00606fd0
void releaseAudioBuffer(void* buffer); // FUN_006071a0
int convertFrequency(short freq); // FUN_0061a960
int allocateAudioBuffer(int size); // FUN_00614d20
void applyVolume(int bufferHandle, short left, short right, short surround, int volume, int something, int param3); // FUN_0061d150
void copyAudioData(int destHandle, int destFreq, int srcFormat, int srcHandle, int srcFreq, short left, short right); // FUN_00614da0
void releaseAudioBuffer(int handle); // FUN_00614ed0

// Global data
extern byte gAudioChannelInfoArray[0x1000 * 0x38]; // DAT_011a0f28
extern void** gAllocatorVtable; // DAT_01205868 (allocator vtable: [0]=allocate, [4]=deallocate)
extern uint _DAT_01205940; // low part of profiling counter
extern uint _DAT_01205944; // high part of profiling counter

// Constants for audio format IDs
const int FORMAT_PCM16 = 0x1e;
const int FORMAT_PCM24 = 0x1f;
const int FORMAT_FLOAT32 = 0x20;
const int FORMAT_MP3 = 0x21;
const int FORMAT_AAC = 0x22;
const int FORMAT_OGG = 0x23;

// Structure for a single audio channel info entry (0x38 bytes)
struct AudioChannelInfo {
    byte channelCount;   // +0x00: number of channels (e.g., 1=mono, 2=stereo)
    byte something;      // +0x01: unknown (used as loop limit)
    byte padding[0x36];  // rest of structure
};

// Helper to allocate memory via global allocator
inline void* allocateMemory(uint size) {
    return (*(void* (*)(uint))gAllocatorVtable[0])(size);
}

// Helper to deallocate memory via global allocator
inline void deallocateMemory(void* ptr) {
    (*(void (*)(void*))gAllocatorVtable[1])(ptr);
}

// Main mixing function
int AudioMixer::processMix(uint sourceIndex, uint destIndex, int param3) {
    LARGE_INTEGER startTime, endTime;
    byte bVar1;
    bool bVar2, bVar3, bVar4, bVar5, bVar13;
    short sVar6;
    byte* puVar7;
    int iVar8, iVar9, iVar10;
    int uVar11, uVar12;
    bool bStack_d5;
    int iStack_d4;
    int uStack_d0;
    int iStack_c8;
    int iStack_cc;
    LARGE_INTEGER LStack_c0;
    uint uStack_b8;
    int iStack_b4;
    byte auStack_b0[2]; // buffer for source data
    short sStack_ae, sStack_ac;
    int iStack_a8; // source format ID
    uint uStack_a4; // flags
    int uStack_90; // unknown
    int iStack_88; // source frequency
    int uStack_84; // source buffer handle
    int uStack_6c; // destination buffer handle
    LARGE_INTEGER LStack_68;
    int uStack_5c, uStack_58, uStack_54; // allocator parameters
    byte auStack_50[2]; // buffer for destination data
    int uStack_4e; // packed short (left+right)
    int iStack_48; // destination format ID
    uint uStack_44; // destination flags
    int iStack_28; // destination frequency
    int uStack_24; // destination buffer handle
    int uStack_c; // temporary

    // Start profiling
    QueryPerformanceCounter(&LStack_68);
    uStack_b8 = LStack_68.s.LowPart;
    iStack_b4 = LStack_68.s.HighPart;

    // Validate destination index
    if (destIndex >= 0x1000) {
        return 0;
    }

    AudioChannelInfo* destInfo = (AudioChannelInfo*)&gAudioChannelInfoArray[destIndex * 0x38];
    if (destInfo == nullptr || destInfo->channelCount <= 1) {
        return 0;
    }

    bVar1 = destInfo->something; // number of iterations (channels to process)

    // Get source channel info
    AudioChannelInfo* srcInfo = nullptr;
    if (sourceIndex < 0x1000) {
        srcInfo = (AudioChannelInfo*)&gAudioChannelInfoArray[sourceIndex * 0x38];
    }
    int srcChannelCount = (srcInfo != nullptr) ? srcInfo->something : 0;

    bVar13 = false;
    uStack_d0 = 0;
    iStack_c8 = 0;
    iStack_cc = 0;

    if (srcChannelCount == 0) {
        goto profiling_end;
    }

    do {
        int iVar10 = iStack_c8;
        int uVar12 = uStack_d0;

        // Read source audio data
        iVar8 = readAudioData(sourceIndex, 10, iStack_cc, auStack_b0);
        if (iVar8 == 0) {
            return 0;
        }

        int iVar9 = bVar1 - 1;
        int iVar8 = iStack_cc;
        if ((iStack_cc < iVar9) || (iVar8 = iVar9, iStack_cc <= iVar9)) {
            // Need to read destination data
            if (bVar13) {
                deallocateMemory((void*)uStack_d0);
                uStack_d0 = 0;
                bVar13 = false;
            }
            iVar10 = readAudioData(destIndex, 9, iVar8, auStack_50);
            if (iVar10 == 0) {
                releaseAudioBuffer(auStack_b0);
                return 0;
            }
            int uVar12 = uStack_c;
            int iVar10 = iStack_28;
            bVar2 = false;
            bVar4 = bVar13;
        } else {
            // Read destination data from previous offset
            iVar8 = readAudioData(sourceIndex, 9, iStack_cc - 1, auStack_50);
            if (iVar8 == 0) {
                releaseAudioBuffer(auStack_b0);
                return 0;
            }
            uStack_44 = uStack_a4 & 0xffffffef;
            iStack_48 = 3; // default format?
            uStack_d0 = 0;
            iStack_c8 = 0;
            bVar4 = false;
            bVar2 = bVar13;
        }

        int uVar11 = uVar12;
        if ((uStack_44 & 0x10) != 0) {
            // Allocate buffer for destination
            uStack_5c = 2;
            uStack_58 = 0x10;
            uStack_54 = 0;
            uVar11 = (int)allocateMemory(0x10); // size?
            if (bVar2) {
                deallocateMemory((void*)uVar12);
            }
            bVar2 = true;
            int iVar10 = iStack_28;
        }

        short sVar6 = sStack_ae;
        if (((short)uStack_4e != sStack_ae) || (uStack_4e._2_2_ != sStack_ac)) {
            // Format conversion needed
            if (((iStack_a8 == 0x1e) || (iStack_a8 == 0x1f) || (iStack_a8 == 0x20) ||
                 (iStack_a8 == 0x21) || (iStack_a8 == 0x22) || (iStack_a8 == 0x23))) {
                iStack_d4 = convertFrequency(sStack_ae);
                uVar12 = convertFrequency(sVar6);
            } else {
                iStack_d4 = iStack_88;
                uVar12 = uStack_84;
            }
            uVar12 = allocateAudioBuffer(uVar12);
            if (((iStack_48 == 3) || (iStack_48 == 2)) && (param3 != 0)) {
                applyVolume(uVar12, CONCAT22(sStack_ac, sStack_ae), CONCAT22(uStack_aa, sStack_ac),
                            uVar11, uStack_4e, iVar10, param3);
            }
            if (bVar2) {
                deallocateMemory((void*)uVar11);
            }
            bVar2 = true;
            int iVar10 = iStack_d4;
        }

        int iVar8 = iStack_a8;
        bool bVar5 = true;
        bool bVar3 = bVar2;
        bVar13 = bVar4;
        if ((int)(uint)bVar1 < (int)srcChannelCount) {
            bVar3 = false;
            uStack_d0 = uVar12;
            iStack_c8 = iVar10;
            bVar13 = bVar2;
        }

        iStack_d4 = uVar12;
        bStack_d5 = bVar3;

        if (((iStack_a8 != iStack_48) &&
             (((((iStack_a8 == 0x1e || iStack_a8 == 0x1f) || iStack_a8 == 0x20) ||
                ((iStack_a8 == 0x21 || iStack_a8 == 0x22)) || iStack_a8 == 0x23))) &&
            (((iStack_48 != 0x1e && iStack_48 != 0x1f) &&
              ((iStack_48 != 0x20 && ((iStack_48 != 0x21 && iStack_48 != 0x22) && iStack_48 != 0x23)))))) {
            bStack_d5 = (uStack_a4 & 0x10) == 0;
            if (bStack_d5) {
                iStack_d4 = uStack_6c;
            } else {
                iStack_d4 = allocateAudioBuffer(uStack_84);
            }
            bStack_d5 = !bStack_d5;
            copyAudioData(iStack_d4, iStack_88, iVar8, uVar12, iVar10,
                          CONCAT22(sStack_ac, sStack_ae), CONCAT22(uStack_aa, sStack_ac));
            int iVar10 = iStack_88;
            bVar5 = bStack_d5;
            if (bVar3) {
                deallocateMemory((void*)uVar12);
                int iVar10 = iStack_88;
            }
        }

        if ((uStack_a4 & 0x10) == 0) {
            if (bVar5) {
                releaseAudioBuffer(uStack_6c, iStack_88, iVar10, uStack_90);
            }
            uVar12 = iStack_d4;
            if (bStack_d5) {
                deallocateMemory((void*)uVar12);
            }
        } else {
            if (iVar10 != iStack_88) {
                uVar12 = allocateAudioBuffer(uStack_84);
                releaseAudioBuffer(uVar12, iStack_88, iVar10, uStack_90);
                if (bStack_d5) {
                    deallocateMemory((void*)iStack_d4);
                }
                deallocateMemory((void*)uVar12);
            }
        }

        releaseAudioBuffer(auStack_50);
        releaseAudioBuffer(auStack_b0);
        iStack_cc = iStack_cc + 1;
    } while (iStack_cc < srcChannelCount);

    if (bVar13) {
        deallocateMemory((void*)uStack_d0);
    }

profiling_end:
    // End profiling and accumulate time
    QueryPerformanceCounter(&LStack_c0);
    bool carry = CARRY4(_DAT_01205940, LStack_c0.s.LowPart - uStack_b8);
    _DAT_01205940 = _DAT_01205940 + (LStack_c0.s.LowPart - uStack_b8);
    _DAT_01205944 = _DAT_01205944 +
                    ((LStack_c0.s.HighPart - iStack_b4) - (uint)(LStack_c0.s.LowPart < uStack_b8)) +
                    (uint)carry;
    return 1;
}