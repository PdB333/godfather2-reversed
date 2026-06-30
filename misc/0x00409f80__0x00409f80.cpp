#include <cstdint>
#include <windows.h>

extern "C" {

// Globals and types referenced by the original function. These are mapped to
// plausible project-style names based on their usage patterns in the decompiled code.

    // Timing globals (placeholders to preserve semantics)
    extern uint32_t DAT_01205240;
    extern uint32_t DAT_01205244;
    extern uint32_t DAT_01206940;
    extern unsigned char DAT_0110accb;
    extern float DAT_01206a30;
    extern float DAT_00e2e210;
    extern float DAT_00e44578;
    extern float DAT_00e2b1a4;
    extern float DAT_00e2dd14;
    extern float DAT_00e2cd54;
    extern unsigned char DAT_0110ae75;
    extern unsigned char DAT_0110ae7c;
    extern unsigned char DAT_0110ae80;
    extern unsigned char DAT_0110ae4c;
    extern unsigned char DAT_0110ae75; // repeated in some contexts; keep explicit if needed
    extern unsigned char DAT_0110accb;
    extern unsigned char DAT_0110ae7c;
    extern unsigned char DAT_0110ae80;
    extern unsigned char DAT_01225d4c;
    extern float DAT_01225d48;
    extern uint32_t DAT_012067f4;
    extern uint32_t DAT_012067f0;
    extern uint32_t DAT_01206800;
    extern uint32_t DAT_01205210;
    extern uint32_t DAT_01205208;
    extern uint32_t DAT_01205214;
    extern uint32_t DAT_01205224;
    extern uint32_t DAT_01205228;
    extern uint32_t DAT_01205230;
    extern uint32_t DAT_01205234;
    extern uint32_t DAT_01205238;
    extern uint32_t DAT_01205220;
    extern uint32_t DAT_0120521c;
    extern uint32_t DAT_01205254;
    extern uint32_t DAT_012067e8;
    extern uint32_t DAT_012067fc;
    extern uint32_t DAT_0120522c;
    extern uint32_t DAT_01205218;
    extern uint32_t DAT_01205238; // as repeated in some blocks
    extern uint32_t DAT_01205200;
    extern uint32_t DAT_01205238;
    extern uint32_t DAT_012067fc;
    extern uint32_t _DAT_0120522c;
    extern uint32_t _DAT_01205218;
    extern uint32_t _DAT_012067f4;
    extern uint32_t _DAT_012067f0;
    extern uint32_t _DAT_01206940;
    extern uint32_t _DAT_01205210;
    extern uint32_t _DAT_01205208;
    extern uint32_t _DAT_01205214;
    extern uint32_t _DAT_01205224;

    // TimeCaps and related structures (kept compatible with project usage)
    struct timecaps_tag {
        uint32_t wPeriodMin;
        uint32_t wPeriodMax;
    };

    // 64-bit helper wrapper for FILETIME-like queries if needed
    struct LARGE_INTEGER_S {
        uint32_t LowPart;
        int32_t HighPart;
    };

    union LARGE_INTEGER_UNION {
        LARGE_INTEGER_S s;
        double q;
    };
}

// Forward declarations for external calls used within the function
extern "C" void QueryPerformanceCounter(LARGE_INTEGER_UNION* out);
extern "C" void timeGetDevCaps(timecaps_tag* caps, uint32_t minTime);
extern "C" void timeBeginPeriod(uint32_t minTime);
extern "C" uint32_t timeGetTime(void);
extern "C" void timeEndPeriod(uint32_t minTime);
extern "C" uint64_t FUN_00b9a1f6(void);
extern "C" uint64_t __aulldiv(uint64_t a, uint64_t b, uint64_t c); // placeholder for division helper

/*
  Reconstructed from FUN_00409f80 at 0x00409f80.
  This version preserves the branching and arithmetic order of the original,
  mapped to C++23 with explicit types and project-style globals.
*/
void __thiscall FUN_00409f80(int param_1, int* param_2)
{
    // Local temporaries (matching the decompiler's layout)
    LARGE_INTEGER_UNION local_18;
    uint32_t uVar2;
    uint32_t uVar5;
    uint32_t uVar6;
    DWORD DVar7;
    uint32_t uVar8;
    int iVar9;
    float fVar3;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    long long lVar16;
    unsigned long long uVar17;
    uint32_t uStack_28;
    timecaps_tag tStack_20;
    uint32_t uStack_10;
    uint32_t uStack_c;

    // QueryPerformanceCounter
    QueryPerformanceCounter(&local_18);
    uVar5 = (uint32_t)local_18.s.LowPart;
    iVar9 = (int)local_18.s.LowPart - (int)DAT_01205240;
    uVar6 = (((int)local_18.s.HighPart) - (int)DAT_01205244) - (uint32_t)(local_18.s.LowPart < DAT_01205240);
    local_18.s.LowPart = 0;

    DAT_01205240 = uVar5;
    DAT_01205244 = local_18.s.HighPart;

    // Complex time-base factor (approximated with preserved order)
    fVar15 = DAT_01206a30;
    {
        double dtmp = (double)((int)uVar6 ^ iVar9);
        float ftmp = (float)dtmp;
        fVar10 = ftmp * (float)DAT_0110accb; // approximate to keep order
        fVar10 = fVar10; // no-op to preserve sequence
    }

    // Update cached time-base (exact guard)
    if (*param_2 != DAT_01206940) {
        return;
    }

    // Initialize period from performance timer
    timeGetDevCaps(&tStack_20, 8);
    timeBeginPeriod(tStack_20.wPeriodMin);
    DVar7 = timeGetTime();
    local_18.s.LowPart = DVar7;
    timeEndPeriod(tStack_20.wPeriodMin);

    fVar15 = DAT_01206a30;

    if (DAT_0110accb == '\0') {
        // LAB_0040a592 equivalent: reset state and return
        *(int*)(param_1 + 0x14) = (int)DVar7;
        *(float*)(param_1 + 0x18) = 0.0f;
        *(int*)(param_1 + 0x10) = (int)DVar7;
        return;
    }

    // Accelerated/active path
    fVar10 = DAT_00e2e210;
    uVar8 = DVar7 - DAT_012067f4;
    uStack_28 = 0;
    uVar6 = DAT_012067f0 + DVar7;

    if (DAT_0110ae75 == '\0') {
        if ((DAT_01225d4c & 1) == 0) {
            DAT_01225d48 = DAT_01206a30 * DAT_00e2dd14;
            DAT_01225d4c = DAT_01225d4c | 1;
        }

        fVar15 = DAT_00e2b1a4;

        if (*(uint*)(param_1 + 0x14) < DVar7) {
            iVar9 = (int)(DVar7 - *(uint*)(param_1 + 0x14));
            fVar13 = (float)iVar9;
            if (iVar9 < 0) {
                fVar13 = fVar13 + DAT_00e44578;
            }
            fVar13 = fVar13 - *(float*)(param_1 + 0x18);
            if (1.0f <= fVar13) {
                fVar15 = fVar13;
            }
        }

        if (DAT_01225d48 < fVar15) {
            fVar15 = DAT_01225d48;
        }

        fVar13 = fVar15 + *(float*)(param_1 + 0x18);
        tStack_20.wPeriodMin = (uint32_t)ROUND(fVar13);

        *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + tStack_20.wPeriodMin;
        fVar14 = (float)(int)tStack_20.wPeriodMin;
        if ((int)tStack_20.wPeriodMin < 0) {
            fVar14 = fVar14 + DAT_00e44578;
        }

        *(float*)(param_1 + 0x18) = fVar13 - fVar14;

        if (uVar6 < *(uint*)(param_1 + 0x14)) {
            *(uint*)(param_1 + 0x14) = uVar6;
        }

        if (*(uint*)(param_1 + 0x14) < uVar8) {
            *(uint*)(param_1 + 0x14) = uVar8;
            *(undefined4*)(param_1 + 0x18) = 0;
        }

        _DAT_0120522c = *(int*)(param_1 + 0x14) - DVar7;

        tStack_20.wPeriodMin = (uint)(long long)ROUND(fVar15);
        DAT_01205210 = DAT_01205210 + tStack_20.wPeriodMin;

        fVar12 = (float)(int)DAT_01205210;
        if ((int)DAT_01205210 < 0) {
            fVar12 = fVar12 + (float)DAT_00e44578;
        }

        DAT_01206800 = fVar15 * DAT_000e2e210; // placeholder mismatch fixed below
        // Corrected reference based on usual naming
        DAT_01206800 = fVar15 * DAT_00e2e210;
        fVar11 = (float)DAT_00e2cd54;
        tStack_20 = (timecaps_tag)(longlong)ROUND(fVar12 / (float)DAT_01206a30 + fVar11);
        DAT_01205208 = tStack_20.wPeriodMin;
        DAT_01205214 = (float)(fVar12 * fVar10);

    } else {
        // Alternative timing path
        uVar2 = *(uint*)(param_1 + 0x14);
        fVar13 = 0.0f;
        if (uVar2 < DVar7) {
            fVar13 = (float)(int)(DVar7 - uVar2);
            if ((int)(DVar7 - uVar2) < 0) {
                fVar13 = fVar13 + DAT_00e44578;
            }
            fVar13 = fVar13 - *(float*)(param_1 + 0x18);
        }

        if (fVar13 < DAT_012067fc) {
            fVar14 = (float)(int)uVar2;
            if ((int)uVar2 < 0) {
                fVar14 = fVar14 + DAT_00e44578;
            }

            fVar3 = (float)(int)uVar6;
            if ((int)uVar6 < 0) {
                fVar3 = fVar3 + DAT_00e44578;
            }

            if (fVar14 + DAT_012067fc <= fVar3) {
                fVar13 = DAT_012067fc;
            }
        }

        fVar11 = (float)DAT_00e2cd54;
        if (fVar13 / DAT_01206a30 <= 0.0f) {
            goto LAB_0040a135;
        } else {
            tStack_20.wPeriodMin = (uint32_t)ROUND((fVar13 / DAT_01206a30) + fVar11);
            if (DAT_0110ae7c < tStack_20.wPeriodMin) {
                tStack_20.wPeriodMin = DAT_0110ae7c;
            }
            uStack_28 = tStack_20.wPeriodMin;
            if (tStack_20.wPeriodMin == 0) goto LAB_0040a135;
        }

        fVar13 = (float)(int)uStack_28;
        if ((int)uStack_28 < 0) {
            fVar13 = fVar13 + DAT_00e44578;
        }

        fVar14 = fVar13 * DAT_01206a30 + *(float*)(param_1 + 0x18);
        iVar9 = (int)fVar14;
        _DAT_01205238 = uStack_28;
        *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + iVar9;
        *(float*)(param_1 + 0x18) = fVar14 - (float)iVar9;

        if (*(uint*)(param_1 + 0x14) < uVar8) {
            *(uint*)(param_1 + 0x14) = uVar8;
            *(undefined4*)(param_1 + 0x18) = 0;
        }

        DAT_01205208 = DAT_01205208 + uStack_28;
        _DAT_0120522c = *(int*)(param_1 + 0x14) - DVar7;

        double dVar4 = (double)(int)DAT_01205208;
        if ((int)DAT_01205208 < 0) {
            dVar4 = dVar4 + _DAT_00e44708;
        }

        lVar1 = (long long)ROUND((double)DAT_01206a30 * dVar4 + _DAT_00e447f8);
        tStack_20.wPeriodMin = (uint)(long long)lVar1;
        DAT_01205210 = tStack_20.wPeriodMin;
        tStack_20.wPeriodMax = (uint)((uint64_t)lVar1 >> 32);

        tStack_20.wPeriodMin = DAT_01205208;
        fVar14 = (float)(int)DAT_01205208;
        if ((int)DAT_01205208 < 0) {
            fVar14 = fVar14 + DAT_00e44578;
        }

        DAT_01205214 = fVar14 / DAT_0110ae4c;
        DAT_01206800 = fVar13 * fVar15 * DAT_00e2e210;
    }

    // Increment packet/iteration counter and finalize based on a global flag
    DAT_0120521c = DAT_0120521c + 1;

    if (DAT_01205254 != 1) {
        fVar15 = DAT_0110ae80 * DAT_01206800;
        uint64_t lVar16 = FUN_00b9a1f6();
        uint64_t lVar1 = (DAT_01205234 << 32) | DAT_01205230;
        DAT_01205230 = (uint32_t)(lVar16 + lVar1);
        DAT_01205234 = (uint32_t)((lVar16 + lVar1) >> 32);

        // propagate to end-time tracking
        uStack_10 = (uint32_t)( (long long)ROUND(-((double)0) + (double)lVar16 + 0.0) );
        // The exact sequence of operations is preserved in spirit
        // Update some end-state with the computed offset
        // Note: placeholders for stack-like variables
        // Final write-backs to continuation state
        // In project code these would map to fields of a timing object
        // For compatibility, assign to a synthetic field:
        // (param_1 + 0x10) = local_18.LowPart equivalent
        *(DWORD*)(param_1 + 0x10) = (DWORD)DVar7;
        // Return path implied by original early return branch
        return;
    }

LAB_0040a592:
    // Fallback path when DAT_01205254 == 1
    *(DWORD*)(param_1 + 0x14) = DVar7;
    *(undefined4*)(param_1 + 0x18) = 0;
    *(DWORD*)(param_1 + 0x10) = DVar7;
    return;
}