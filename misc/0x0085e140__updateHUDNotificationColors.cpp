// FUNC_NAME: updateHUDNotificationColors

#include <cstdint>

// Forward declarations of external functions
extern bool checkGlobalFlag(uint32_t* flagPtr); // FUN_0079e920
extern bool checkGlobalFlag2(uint32_t* flagPtr); // FUN_0079e970
extern uint32_t getSomethingById(uint32_t id); // FUN_00798f50
extern bool checkStringValidity(uint32_t str); // FUN_0040fa60
extern void startCutsceneCamera(); // FUN_0087b5b0
extern void endCutsceneCamera(); // FUN_0087bde0
extern void skipCutscene(bool allowSkip); // FUN_0087d560
extern void playNotificationSound(uint32_t color); // FUN_00549a50
extern void stopNotificationSound(uint32_t color); // FUN_00549a70
extern void showScreenElement(void* elementDesc, int param); // FUN_00408a00
extern void freeMemoryIfNeeded(int* ptr); // FUN_004daf90
extern void setupSomething(int* obj); // FUN_007393b0

// Global constants
extern const uint32_t DAT_00d5780c; // Default notification color (e.g., green/positive)
extern const float DAT_00d577a0;    // Comparison threshold for progress
extern uint32_t* DAT_0112deec;       // Flag for feature A
extern uint32_t* DAT_0112def0;       // Flag for feature B
extern uint32_t* DAT_0112dee4;       // Flag for feature C
extern uint32_t* DAT_0112dee8;       // Flag for feature D
extern uint32_t* DAT_0112df08;       // Flag for cutscene-related element
extern uint32_t* DAT_0112df10;       // Flag for screen element X
extern uint32_t* DAT_0112df14;       // Flag for screen element Y
extern uint32_t* DAT_0112df18;       // Flag for screen element Z
extern uint32_t* DAT_0112adc8;       // Screen element description for cutscene
extern uint32_t* DAT_0112df84;       // Screen element description X
extern uint32_t* DAT_0112df64;       // Screen element description Y
extern uint32_t* DAT_0112df90;       // Screen element description Z

// The function likely belongs to a HUD class; param_1 is 'this'
void __thiscall updateHUDNotificationColors(int thisPtr, uint32_t notificationId, uint32_t* outColors) {
    int iVar1;
    bool bVar2;
    uint32_t uVar3;
    uint32_t local_24; // First output color candidate
    uint32_t local_20; // Second output color candidate
    // Stack buffer for screen element description
    struct {
        uint32_t* elementDesc; // +0x00
        void* extra;           // +0x04
        uint8_t flag1;         // +0x08
        void* padding;         // +0x0c
        uint8_t flag2;         // +0x10
    } screenElement;
    int local_c[2]; // Temporary allocation tracking

    local_24 = 0;
    local_20 = 0;

    // Check if notificationId is valid
    bVar2 = checkStringValidity(notificationId);
    if (bVar2) {
        // Check various game feature flags and set colors accordingly
        bVar2 = checkGlobalFlag(DAT_0112deec);
        if (bVar2) {
            local_20 = DAT_00d5780c; // Default positive color
        }

        bVar2 = checkGlobalFlag(DAT_0112def0);
        if (bVar2) {
            local_24 = DAT_00d5780c;
        }

        bVar2 = checkGlobalFlag(DAT_0112dee4);
        if (bVar2) {
            local_20 = DAT_00d5780c;
        }

        bVar2 = checkGlobalFlag(DAT_0112dee8);
        if (bVar2) {
            local_24 = DAT_00d5780c;
        }

        // Special case: check if a specific objective (ID 0x36) is active
        uVar3 = getSomethingById(0x36);
        bVar2 = checkGlobalFlag(uVar3);
        if (bVar2) {
            if (*(float*)&outColors[2] == DAT_00d577a0) {
                local_24 = DAT_00d5780c; // Set positive if progress matches threshold
            } else {
                local_20 = DAT_00d5780c; // Otherwise set negative
            }
        }

        // Check if cutscene-related element should be shown
        bVar2 = checkGlobalFlag2(DAT_0112df08);
        if (bVar2) {
            iVar1 = *(int*)(thisPtr + 4); // Retrieve some object pointer from 'this'
            startCutsceneCamera();
            endCutsceneCamera();
            // Check bit 0x15 of field at offset 0xc88 in that object
            if ((*(uint32_t*)(iVar1 + 0xc88) >> 0x15 & 1) == 0) {
                // Not in a cutscene? Show screen element
                screenElement.extra = (void*)0; // Additional data
                local_c[0] = 0;
                local_c[1] = 0;
                setupSomething(iVar1);
                screenElement.elementDesc = DAT_0112adc8;
                screenElement.flag1 = 0;
                screenElement.flag2 = 0;
                showScreenElement(&screenElement, 0);
                if (local_c[0] != 0) {
                    freeMemoryIfNeeded(local_c);
                }
            } else {
                // In cutscene - allow skip if certain condition met
                skipCutscene(*(int*)(iVar1 + 0xa0c) == 0);
            }
        }

        // Check and show other screen elements based on flags
        bVar2 = checkGlobalFlag2(DAT_0112df10);
        if (bVar2) {
            screenElement.elementDesc = DAT_0112df84;
            screenElement.extra = 0;
            screenElement.flag1 = 0;
            showScreenElement(&screenElement, 0);
        }

        bVar2 = checkGlobalFlag2(DAT_0112df14);
        if (bVar2) {
            screenElement.elementDesc = DAT_0112df64;
            screenElement.extra = 0;
            screenElement.flag1 = 0;
            showScreenElement(&screenElement, 0);
        }

        bVar2 = checkGlobalFlag2(DAT_0112df18);
        if (bVar2) {
            screenElement.elementDesc = DAT_0112df90;
            screenElement.extra = 0;
            screenElement.flag1 = 0;
            showScreenElement(&screenElement, 0);
        }

        // Compare progress to decide which sound/color to apply
        if (*(float*)&outColors[2] == DAT_00d577a0) {
            playNotificationSound(local_20);
            uVar3 = local_24;
            goto LAB_0085e421;
        }
    }

    playNotificationSound(local_24);
    uVar3 = 0;
LAB_0085e421:
    stopNotificationSound(uVar3);
    // Write output colors
    outColors[0] = local_20;
    outColors[1] = local_24;
    return;
}