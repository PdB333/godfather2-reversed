// FUNC_NAME: ContactConfirmationPopup::handleTermEvent

#include <cstring>

class ContactConfirmationPopup {
public:
    // +0x00: vtable
    // +0x04: unknown
    // +0x16: button0Clicked? (set to 1 when button 0 pressed)
    // +0x40: sliderDragging? (set to 1 when slider track clicked)
    // +0x101: arrDownFlag? (set on arr_down click)
    // +0x102: sliderFlag? (set on slider click)
    // +0x103: arrUpFlag? (set on arr_up click)
    // +0x15: checkboxState (2 bits: bit0=contact, bit1=share)
    // +0x17 (offset 0x5C): currentScrollIndex? (int)
    // +0x1a (offset 0x68): something
    // +0x1c (offset 0x70): maxIndex? (int)

    bool handleTermEvent(const char* termName);
    void startAnimation(void* param, int a); // FUN_00408a00
    void handleButton1Click(); // FUN_00989150
    void onScrollUp(int index); // FUN_009893a0
    void onScrollDown(); // FUN_00989500
    void onPageUpDown(); // FUN_00989430
    void logEvent(const char* event, int a, void* b, int c); // FUN_005a04a0

    // Vtable methods (indices)
    virtual void vtable_method_0x2c(); // (**(code **)(*this + 0x2c))()
};

bool ContactConfirmationPopup::handleTermEvent(const char* termName) {
    // Strings for UI term matching
    static const char kTermButton0[] = "term_mc_popup_button_0_button";
    static const char kTermButton1[] = "term_mc_popup_button_1_button";
    static const char kTermScrollbarUp[] = "term_mc_popup_scrollbar_arr_up";
    static const char kTermScrollbarDown[] = "term_mc_popup_scrollbar_arr_dow";
    static const char kTermScrollbarSlider[] = "term_mc_popup_scrollbar_slider";
    static const char kTermScrollbarTrack[] = "term_mc_popup_scrollbar_track_h";
    static const char kTermCheckboxContact[] = "term_mc_popup_checkboxContact_h";
    static const char kTermCheckboxShare[] = "term_mc_popup_checkboxShare_hot";

    // Reset flags
    *(uint8_t*)((int)this + 0x40) = 0;
    *(uint8_t*)((int)this + 0x101) = 0;
    *(uint8_t*)((int)this + 0x102) = 0;
    *(uint8_t*)((int)this + 0x103) = 0;

    // Button 0 clicked
    if (strcmp(termName, kTermButton0) == 0) {
        *(uint8_t*)((int)this + 0x16) = 1;
        // Call some animation/timer function with a global constant
        // DAT_011302c8 is likely a color or time value
        struct {
            int a;
            int b;
            uint8_t c;
        } local = { DAT_011302c8, 0, 0 };
        startAnimation(&local, 0);
        this->vtable_method_0x2c(); // Probably plays sound or starts transition
        return true;
    }

    // Button 1 clicked
    if (strcmp(termName, kTermButton1) == 0) {
        handleButton1Click();
        return true;
    }

    // Scrollbar up arrow clicked
    if (strcmp(termName, kTermScrollbarUp) == 0) {
        *(uint8_t*)((int)this + 0x103) = 1;
        if (*((int*)this + 0x17) != 0) {
            *((int*)this + 0x17) = *((int*)this + 0x17) - 1;
            int index = *((int*)this + 0x1a);
            if (*((int*)this + 0x1c) <= *((int*)this + 0x1a)) {
                index = *((int*)this + 0x1c);
            }
            onScrollUp(index);
        }
        return true;
    }

    // Scrollbar down arrow clicked
    if (strcmp(termName, kTermScrollbarDown) == 0) {
        *(uint8_t*)((int)this + 0x101) = 1;
        // On down arrow, start slider scrolling
        logEvent("StartSliderScrolling", 0, &DAT_00d9158c, 0);
        *(uint8_t*)((int)this + 0x40) = 1;
        return true;
    }

    // Scrollbar slider clicked
    if (strcmp(termName, kTermScrollbarSlider) == 0) {
        *(uint8_t*)((int)this + 0x102) = 1;
        onScrollDown();
        return true;
    }

    // Scrollbar track clicked (page up/down)
    if (strcmp(termName, kTermScrollbarTrack) == 0) {
        *(uint8_t*)((int)this + 0x101) = 1;
        logEvent("PageUpDown", 0, &DAT_00d9158c, 0);
        onPageUpDown();
        return true;
    }

    // Checkbox "Contact" hot area clicked
    if (strcmp(termName, kTermCheckboxContact) == 0) {
        *((int*)this + 0x15) ^= 1; // Toggle contact state bit 0
        logEvent("UpdateState", 0, &DAT_00d9158c, 0);
        return true;
    }

    // Checkbox "Share" hot area clicked
    if (strcmp(termName, kTermCheckboxShare) == 0) {
        *((int*)this + 0x15) ^= 2; // Toggle share state bit 1
        logEvent("UpdateState", 0, &DAT_00d9158c, 0);
        return true;
    }

    return false; // Unhandled term
}