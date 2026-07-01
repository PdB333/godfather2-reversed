// Xbox PDB: EARS_Apt_UIHudMinimap_TimerInit
// FUNC_NAME: MinimapTimer::setVisible
// Address: 0x00943c90
// Role: Sets visibility of minimap timer UI elements and resets timer state

// ---------------------------------------------------------------------------
// Global string pointers to UI element names (defined elsewhere in the game)
// ---------------------------------------------------------------------------
extern const char* PTR_s_timer_track_right_00e567d8;   // "timer_track_right"
extern const char* PTR_s_timer_track_left_00e567dc;    // "timer_track_left"
extern const char* PTR_s_timer_mask_right_00e567e0;    // "timer_mask_right"
extern const char* PTR_s_timer_right_00e567e4;         // "timer_right"
extern const char* PTR_s_timer_mask_left_00e567e8;     // "timer_mask_left"
extern const char* PTR_s_timer_left_00e567ec;          // "timer_left"
extern const char* PTR_s_timer_bg_right_00e567f0;      // "timer_bg_right"
extern const char* PTR_s_timer_bg_left_00e567f4;       // "timer_bg_left"

// ---------------------------------------------------------------------------
// Internal UI functions (names are inferred, actual symbols unknown)
// ---------------------------------------------------------------------------
// Sets a property on the UI object at the given path to a numeric value.
void __cdecl UI_setProperty(const char* path, int value);  // = FUN_0059ee00
// Sets a sub-element's property (e.g., "_visible") to a string value.
void __cdecl UI_setElementProperty(const char* path, const char* element, const char* property);  // = FUN_00941220

// ---------------------------------------------------------------------------
// Member function of MinimapTimer class
// ---------------------------------------------------------------------------
class MinimapTimer {
public:
    // Sets all timer sub-elements to non-visible and resets the timer state.
    void __thiscall setVisible();
};

void __thiscall MinimapTimer::setVisible()
{
    char path[256];
    // Build base path for minimap timer
    __snprintf(path, 0x100, "mmap/minimap_timer.%s", "_visible");

    // For each timer UI element, first set a numeric property (0 likely means hidden),
    // then set the "_visible" property (string value) to the same effect.
    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_track_right_00e567d8, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_track_left_00e567dc, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_mask_right_00e567e0, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_right_00e567e4, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_mask_left_00e567e8, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_left_00e567ec, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_bg_right_00e567f0, "_visible");

    UI_setProperty(path, 0);
    UI_setElementProperty(path, PTR_s_timer_bg_left_00e567f4, "_visible");

    // Reset internal timer state (offset 0xFC)
    *(uint16_t*)(this_ + 0xFC) = 0;
}