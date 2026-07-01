// Xbox PDB: EARS_Apt_UIHud_UpdateTutorial
// FUNC_NAME: TutorialUI::updateTutorialHint
// Address: 0x0093a600
// Manages tutorial hint button visibility and auto-hide timer.
// Uses bitfield at +0x5c: bit16 = visible, bit15 = animating, bit14 = timerActive.
// Timer at +0xcc counts down by global step (DAT_01206804).
// When timer expires, either hides without animation or shows "HideButton" UI element.

#include <cstdint>

// Forward declarations of external functions
extern bool checkTutorialCondition(int);               // FUN_00911f40
extern void showTutorialButton(int subIndex, int unk1, int unk2); // FUN_0093b530
extern void hideTutorialWithoutAnimation(int);         // FUN_00939ba0
extern void showTutorialHideButton(const char* cmd, int param, const char* str); // FUN_005a04a0
extern int DAT_01206804; // Frame delta or constant for timer decrement

int __fastcall TutorialUI::updateTutorialHint() {
    uint32_t flags = *(uint32_t*)((char*)this + 0x5c);

    // If hint is visible (bit16) and not animating (bit15 clear)
    if (((flags >> 0x10) & 1) != 0 && ((flags >> 0x0f) & 1) == 0) {
        // Check if tutorial condition still holds (e.g., player still in tutorial zone)
        if (checkTutorialCondition(0) && *(int*)((char*)this + 0x60) == 0) {
            // Hide the hint: clear visible flag
            *(uint32_t*)((char*)this + 0x5c) = flags & 0xfffeffff;
            // Show the "HideButton" UI element for this hint
            showTutorialButton(*(int*)((char*)this + 200), 1, 0);
            return 0; // Hiding was performed
        }
    }

    flags = *(uint32_t*)((char*)this + 0x5c);
    // If hint is not visible and no timer active, do nothing special
    if (((flags >> 0x10) & 1) == 0 && ((flags >> 0x0e) & 1) == 0) {
        return 1; // No action needed
    }

    // Handle active auto-hide timer (bit14)
    if (((flags >> 0x0e) & 1) != 0) {
        // Decrement timer by global step
        *(int*)((char*)this + 0xcc) -= DAT_01206804;
        if (*(int*)((char*)this + 0xcc) < 1) {
            // Timer expired
            if (((flags >> 0x0f) & 1) == 0) {
                // No animation flag – hide immediately
                hideTutorialWithoutAnimation(0);
            } else {
                // Animation flag set – use UI command to show hide button
                showTutorialHideButton("ShowTutorialHideButton", 0, &DAT_00d8a64c);
            }
            // Check additional flag at +0x5e bit0 – if clear, pending return 1
            if ((*(uint8_t*)((char*)this + 0x5e) & 1) == 0) {
                return 1;
            }
        }
    }
    return 0; // Default return (maybe keep current state)
}