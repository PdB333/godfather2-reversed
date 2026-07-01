// FUNC_NAME: ScrollBar::processSkinElementName
bool __thiscall ScrollBar::processSkinElementName(const wchar_t* skinElementName) {
    // Offsets:
    // +0x100: bool m_bSliderActive
    // +0x101: bool m_bTrackActive
    // +0x102: bool m_bArrowDownActive
    // +0x103: bool m_bArrowUpActive
    // +0x68: int m_scrollPosition
    // +0x70: int m_maxScroll

    extern const wchar_t* g_strScrollbarSlider;
    extern const wchar_t* g_strScrollbarTrackH;
    extern const wchar_t* g_strScrollbarArrowUp;
    extern const wchar_t* g_strScrollbarArrowDown;

    if (!*(char*)(this + 0x100)) {
        // Slider not active
        if (!*(char*)(this + 0x101)) {
            // Track not active – check arrows
            if (*(char*)(this + 0x103)) {
                if (wcscmp(g_strScrollbarArrowUp, skinElementName) == 0) {
                    onArrowUpClicked(); // FUN_009894e0
                    return true;
                }
            }
            if (*(char*)(this + 0x102)) {
                if (wcscmp(g_strScrollbarArrowDown, skinElementName) == 0) {
                    onArrowDownClicked(); // FUN_00989500
                    return true;
                }
            }
            return false;
        } else {
            // Track active – compare with slider string
            if (wcscmp(g_strScrollbarSlider, skinElementName) != 0) {
                *(char*)(this + 0x101) = 0; // turn off track
                return true;
            }
            *(char*)(this + 0x101) = 1; // keep track on
            PublishEvent("PageUpDown", 0, &unknownData, 0); // FUN_005a04a0
            int position = *(int*)(this + 0x68);
            int maxScroll = *(int*)(this + 0x70);
            if (maxScroll <= position) position = maxScroll;
            setScrollPosition(position); // FUN_009893a0
            return true;
        }
    } else {
        // Slider active
        const wchar_t* currentStr = g_strScrollbarSlider;
        if (wcscmp(currentStr, skinElementName) != 0) {
            currentStr = g_strScrollbarTrackH;
            if (wcscmp(currentStr, skinElementName) != 0) {
                *(char*)(this + 0x100) = 0; // turn off slider
                return true;
            }
        }
        PublishEvent("UpdateSliderScrolling", 0, &unknownData, 0); // FUN_005a04a0
        int position = *(int*)(this + 0x68);
        int maxScroll = *(int*)(this + 0x70);
        if (maxScroll <= position) position = maxScroll;
        setScrollPosition(position); // FUN_009893a0
        return true;
    }
}