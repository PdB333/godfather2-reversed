// FUNC_NAME: RenderManager::updateDetailSettings
// Address: 0x00531d40
// This function adjusts render detail levels and manages slot-based render list activation.
// It handles two render lists (A and B) and updates quality thresholds for various detail levels.

#include <cstdint>

// Forward declarations of called functions
void setLOD(int level);
void setRenderQuality(int a, int b);
void setSlotActive(int mode, int slotId, int flags);
int getSomeValue();
void setRenderScale(int a, int b, int c, float scaleX, float scaleY);
void updateSomething();
void processRenderNode(int nodePtr);
void processRenderListA();
void processRenderListB(int mode);
void setAspectRatio(int a, int b, int c);
void iterateRenderList(int listHead);
void finishRenderList();

// Global state (addresses inferred from decompiled)
extern int g_renderListA;          // DAT_01194a6c
extern int g_renderListB;          // DAT_01194a68
extern int g_currentSlotA;         // DAT_011f38f0
extern int g_replacementSlotA;     // DAT_01218e58
extern int g_slotActiveFlagA;      // DAT_011f38f4
extern int g_newSlotA;             // DAT_01218e98
extern int g_currentSlotB;         // DAT_011f3910
extern int g_slotFlagB;            // DAT_011f3914
extern int g_renderSlotId;         // DAT_01218eb0
extern int g_anotherSlotId;        // DAT_01218eb8

// Array of slot entries (20 slots, each 8 bytes)
struct SlotEntry {
    int id;
    int flags;
};
extern SlotEntry g_slotEntries[20]; // at DAT_01218e50

// Manager pointer (vtable at +0x94)
extern int* g_pManager;            // DAT_01205750

// Quality thresholds
extern int g_minQuality;           // DAT_012058d0
extern int g_maxQuality;           // DAT_00f15988
extern int g_qualityThreshold1;    // _DAT_011f39f4
extern int g_qualityThreshold2;    // _DAT_011f3a10
extern int g_qualityThreshold3;    // _DAT_011f3a14
extern int g_qualityThreshold4;    // _DAT_011f3a38
extern int g_qualityThreshold5;    // _DAT_011f3a3c
extern int g_qualityThreshold6;    // _DAT_011f3a44

// Mode flag (1 = special mode, 2 = another)
extern int g_modeFlag;             // DAT_00f15a14

void RenderManager::updateDetailSettings()
{
    int nodeListHead;
    int i;
    int slotId, slotFlags;
    bool bFlag;
    int managerPtr;
    char cMode;
    int tmp1, tmp2;

    // Determine mode flags
    if (g_renderListA == 0 && g_renderListB == 0) {
        bFlag = false;
    } else {
        bFlag = true;
        if (g_renderListA != 0 && g_renderListB != 0) {
            cMode = 1;
        } else {
            cMode = 0;
            if (!bFlag) goto LAB_00531ff0;
        }
    }

    // First slot adjustment block
    if (g_currentSlotA == g_replacementSlotA && g_slotActiveFlagA == 0) {
        setLOD(1);
    } else {
        setRenderQuality(g_currentSlotA, g_replacementSlotA);
    }

    // Update slot B with new value from context
    setSlotActive(4, g_currentSlotB, g_slotFlagB);

    // Update slot B state
    tmp1 = g_newSlotA;
    tmp2 = g_slotFlagB;
    g_currentSlotB = g_newSlotA;
    g_slotFlagB = 0;
    setSlotActive(4, tmp1, tmp2);

    // Branch based on mode flag
    if (g_modeFlag == 1 || g_modeFlag == 2) {
        // Special mode: deactivate slots matching currentSlotB (g_newSlotA)
        for (i = 0; i < 20; i++) {
            if (g_slotEntries[i].id == g_currentSlotB) {
                g_slotEntries[i].flags &= ~3;
                break;
            }
        }

        managerPtr = *g_pManager;
        slotId = g_currentSlotA;
        slotFlags = g_slotActiveFlagA;
        g_currentSlotA = 0;
        g_slotActiveFlagA = 0;

        if (slotId != 0 || slotFlags != 0) {
            int vtableEntry = *(int*)(managerPtr + 0x94);
            int someVal = getSomeValue();
            ((void (*)(int*, int, int))vtableEntry)(g_pManager, 0, someVal);
            g_qualityThreshold6 = 1; // DAT_01223538 (probably different global, use meaningful name)
        }
    } else {
        // Normal mode: deactivate slots matching g_newSlotA
        for (i = 0; i < 20; i++) {
            if (g_slotEntries[i].id == g_newSlotA) {
                g_slotEntries[i].flags &= ~3;
                break;
            }
        }

        // Swap slots
        int oldSlotA = g_currentSlotA;
        int oldFlagsA = g_slotActiveFlagA;
        g_currentSlotA = g_newSlotA;
        g_slotActiveFlagA = 0;
        setSlotActive(0, oldSlotA, oldFlagsA);
    }

    // Common post-processing
    setRenderScale(4, 0, 0, 1.0f, 1.0f);
    updateSomething();
    setLOD(2);

    // Second slot adjustment block (similar to first)
    tmp1 = g_renderSlotId;
    tmp2 = g_slotFlagB;
    g_currentSlotB = g_renderSlotId;
    g_slotFlagB = 0;
    setSlotActive(4, tmp1, tmp2);

    if (g_modeFlag != 1 && g_modeFlag != 2) {
        for (i = 0; i < 20; i++) {
            if (g_slotEntries[i].id == g_renderSlotId) {
                g_slotEntries[i].flags &= ~3;
                break;
            }
        }

        int oldSlotA2 = g_currentSlotA;
        int oldFlagsA2 = g_slotActiveFlagA;
        g_currentSlotA = g_renderSlotId;
        g_slotActiveFlagA = 0;
        setSlotActive(0, oldSlotA2, oldFlagsA2);
    }

    setRenderScale(4, 0, 0, 1.0f, 1.0f);
    updateSomething();

    // Third slot update
    for (i = 0; i < 20; i++) {
        if (g_slotEntries[i].id == g_anotherSlotId) {
            g_slotEntries[i].flags &= ~3;
            break;
        }
    }

    int oldSlotA3 = g_currentSlotA;
    int oldFlagsA3 = g_slotActiveFlagA;
    g_currentSlotA = g_anotherSlotId;
    g_slotActiveFlagA = 0;
    setSlotActive(0, oldSlotA3, oldFlagsA3);

LAB_00531ff0:
    // Process render list A
    if (g_renderListA != 0) {
        setRenderScale(0, 0, 0, 1.0f, 0.0f);
        setLOD(1);
        setRenderScale(0, 0, 0, 1.0f, 0.0f);

        // Iterate linked list (next pointer at +0x10)
        for (nodeListHead = g_renderListA; nodeListHead != 0; nodeListHead = *(int*)(nodeListHead + 0x10)) {
            processRenderNode(nodeListHead);
        }
        finishRenderList();

        if (cMode == 0) {
            // Normal path
            for (i = 0; i < 20; i++) {
                if (g_slotEntries[i].id == g_anotherSlotId) {
                    g_slotEntries[i].flags &= ~3;
                    break;
                }
            }

            int oldSlotA4 = g_currentSlotA;
            int oldFlagsA4 = g_slotActiveFlagA;
            g_currentSlotA = g_anotherSlotId;
            g_slotActiveFlagA = 0;
            setSlotActive(0, oldSlotA4, oldFlagsA4);

            tmp1 = g_currentSlotB;
            tmp2 = g_slotFlagB;
            g_currentSlotB = g_renderSlotId;
            g_slotFlagB = 0;
            setSlotActive(4, tmp1, tmp2);

            setRenderScale(0, 0, 0, 1.0f, 1.0f);
        } else {
            // Alternate path (cMode != 0)
            for (i = 0; i < 20; i++) {
                if (g_slotEntries[i].id == g_anotherSlotId) {
                    g_slotEntries[i].flags &= ~3;
                    break;
                }
            }

            int oldSlotA5 = g_currentSlotA;
            int oldFlagsA5 = g_slotActiveFlagA;
            g_currentSlotA = g_anotherSlotId;
            g_slotActiveFlagA = 0;
            setSlotActive(0, oldSlotA5, oldFlagsA5);

            tmp1 = g_currentSlotB;
            tmp2 = g_slotFlagB;
            g_currentSlotB = g_renderSlotId;
            g_slotFlagB = 0;
            setSlotActive(4, tmp1, tmp2);

            setRenderScale(0, 0, 0, 1.0f, 1.0f);
        }
    }

    // Process render list B
    if (g_renderListB != 0) {
        setRenderScale(0, 0, 0, 1.0f, 0.0f);
        setLOD(1);
        setRenderScale(0, 0, 0, 1.0f, 0.0f);

        for (nodeListHead = g_renderListB; nodeListHead != 0; nodeListHead = *(int*)(nodeListHead + 0x10)) {
            processRenderNode(nodeListHead);
        }
        iterateRenderList(cMode);
    }

    // Clamp quality thresholds to minimum values
    if (g_minQuality < 7)   g_minQuality = 7;
    if (g_maxQuality > 7)   g_maxQuality = 7;
    g_qualityThreshold1 = 1; // _DAT_011f39f4

    if (g_minQuality < 14)  g_minQuality = 14;
    if (g_maxQuality > 14)  g_maxQuality = 14;
    g_qualityThreshold2 = 1; // _DAT_011f3a10

    if (g_minQuality < 25)  g_minQuality = 25;
    if (g_maxQuality > 25)  g_maxQuality = 25;
    g_qualityThreshold5 = 7; // _DAT_011f3a3c

    if (g_minQuality < 24)  g_minQuality = 24;
    if (g_maxQuality > 24)  g_maxQuality = 24;
    g_qualityThreshold4 = 0; // _DAT_011f3a38

    if (g_minQuality < 15)  g_minQuality = 15;
    if (g_maxQuality > 15)  g_maxQuality = 15;
    g_qualityThreshold3 = 0; // _DAT_011f3a14

    setAspectRatio(1, 5, 6);

    if (g_minQuality < 27)  g_minQuality = 27;
    g_qualityThreshold6 = 0; // _DAT_011f3a44
    if (g_maxQuality > 26)  g_maxQuality = 27; // originally > 0x1a -> set to 0x1b

    return;
}