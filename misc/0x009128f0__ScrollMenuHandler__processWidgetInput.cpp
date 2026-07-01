// FUNC_NAME: ScrollMenuHandler::processWidgetInput
// Address: 0x009128f0
// Role: Handles scroll menu input by comparing the touched widget name against known scroll button strings (Finances/Generic). Dispatches actions like scroll up/down, page up/down, and start scrolling. Manages internal state flags.

typedef unsigned short wchar_t; // assumed UCS-2 16-bit chars
typedef unsigned char byte; // for return
typedef int BOOL;

// Forward declarations of external functions (EARS system calls)
extern void UIEventDispatcher(const char* action, int param2, void* context, int param4); // FUN_005a04a0
extern void PostUIAction(const char* action, int param2); // FUN_00402050
extern void PlaySound(const char* soundName, int param2); // FUN_00408a00 (maybe)

// Global data (symbolic addresses)
extern wchar_t* PTR_s__book_mcMain_content_mc_scrollba_00e54c04; // "FinancesScrollMenuUp" widget path?
extern wchar_t* PTR_s__book_mcMain_content_mc_scrollba_00e54c08; // "FinancesScrollMenuDown"
extern wchar_t* PTR_s__book_mcMain_content_mc_scrollba_00e54c0c; // "FinancesPageUpDown"
extern wchar_t* PTR_s__book_mcMain_content_mc_scrollba_00e54c10; // "StartScrolling" ???
extern wchar_t* PTR_s__book_mcMain_mcScrollbar_arr_up__00e54c1c; // "GenericScrollMenuUp"
extern wchar_t* PTR_s__book_mcMain_mcScrollbar_arr_dow_00e54c20; // "GenericScrollMenuDown"
extern wchar_t* PTR_s__book_mcMain_mcScrollbar_slider__00e54c24; // "GenericPageUpDown"
extern wchar_t* PTR_s__book_mcMain_mcScrollbar_track_h_00e54c28; // "StartScrolling"
extern int DAT_011301c0; // Some global state (maybe current sound context)
extern void* DAT_00d84448; // global context object

class ScrollMenuHandler {
public:
    // +0x54: scroll type (0 = Finances, non-zero = Generic, but <3 for scrollbar parts)
    int scrollType; 
    // +0x7c: flag indicating scrolling is active
    BOOL scrollingActive;

    // Returns 1 if handled, 0 if not
    byte processWidgetInput(const wchar_t* widgetName);
};

byte ScrollMenuHandler::processWidgetInput(const wchar_t* widgetName) {
    byte handled = 0;

    if (this->scrollType == 0) {
        // Finances scroll menu
        const wchar_t* upStr = PTR_s__book_mcMain_content_mc_scrollba_00e54c04;
        const wchar_t* downStr = PTR_s__book_mcMain_content_mc_scrollba_00e54c08;
        const wchar_t* pageUpDownStr = PTR_s__book_mcMain_content_mc_scrollba_00e54c0c;

        // Compare widgetName to up string
        if (wcscmp(widgetName, upStr) == 0) {
            // Up button
            UIEventDispatcher("FinancesScrollMenuUp", 0, &DAT_00d84448, 0);
            int soundId = DAT_011301c0;
            // Play slide sound? (FUN_00408a00)
            int local[3]; // buffer for sound?
            local[0] = soundId;
            local[1] = 0;
            local[2] = 0;
            PlaySound((const char*)local, 0); // assuming takes pointer to struct
            DAT_011301c0 = local[0]; // update global
            handled = 1;
        } else if (wcscmp(widgetName, downStr) == 0) {
            UIEventDispatcher("FinancesScrollMenuDown", 0, &DAT_00d84448, 0);
            int soundId = DAT_011301c0;
            int local[3] = { soundId, 0, 0 };
            PlaySound((const char*)local, 0);
            DAT_011301c0 = local[0];
            handled = 1;
        } else if (wcscmp(widgetName, pageUpDownStr) == 0) {
            UIEventDispatcher("FinancesPageUpDown", 0, &DAT_00d84448, 0);
            int soundId = DAT_011301c0;
            int local[3] = { soundId, 0, 0 };
            PlaySound((const char*)local, 0);
            DAT_011301c0 = local[0];
            handled = 1;
        } else {
            // Not recognized, ignore
            handled = 0;
        }
    } else {
        // Generic scroll menu (scrollbar parts)
        if ((this->scrollType - 1) < 3) {
            const wchar_t* upStr = PTR_s__book_mcMain_mcScrollbar_arr_up__00e54c1c;
            const wchar_t* downStr = PTR_s__book_mcMain_mcScrollbar_arr_dow_00e54c20;
            const wchar_t* sliderStr = PTR_s__book_mcMain_mcScrollbar_slider__00e54c24;
            const wchar_t* trackStr = PTR_s__book_mcMain_mcScrollbar_track_h_00e54c28;

            const char* actionName = nullptr;

            if (wcscmp(widgetName, upStr) == 0) {
                actionName = "GenericScrollMenuUp";
            } else if (wcscmp(widgetName, downStr) == 0) {
                actionName = "GenericScrollMenuDown";
            } else if (wcscmp(widgetName, sliderStr) == 0) {
                // Slider -> page up/down (or maybe start drag)
                // Actually this is "GenericPageUpDown"? The code moves to next checks.
                actionName = "GenericPageUpDown";
            } else if (wcscmp(widgetName, trackStr) == 0) {
                actionName = "StartScrolling";
            } else {
                // None matched
                return 0;
            }

            UIEventDispatcher(actionName, 0, &DAT_00d84448, 0);
            if (actionName == "GenericScrollMenuUp" || actionName == "GenericScrollMenuDown") {
                PostUIAction("GenericScrollMenuUp/Down", 0); // Actually the code calls FUN_00402050 for these two
                // Note: In the decompiled code, for these two cases it calls FUN_00402050 after UIEventDispatcher.
                // We'll abstract it as a separate sound/post action.
            } else if (actionName == "StartScrolling") {
                this->scrollingActive = 1;
            }
            return 1; // handled
        }
        // If scrollType-1 >= 3, fall through to return 0
    }
    return handled;
}