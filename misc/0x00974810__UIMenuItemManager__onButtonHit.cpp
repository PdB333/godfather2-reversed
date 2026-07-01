// FUNC_NAME: UIMenuItemManager::onButtonHit

// Function address: 0x00974810
// Role: Determines if a given button name (e.g., from event) matches either the hardcoded "button_2" (back/cancel?) or the menu item corresponding to current index.
// On match, triggers associated action (sound activation or menu item press).

extern void* getMenuRoot(); // FUN_00466860
extern void activateButton(void* root); // FUN_005bf350
extern void formatPath(char* buffer, const char* format, int arg); // FUN_00973f60
extern void activateMenuItem(); // FUN_009747a0

// Custom string compare (compares two bytes per iteration, essentially strcmp)
inline int customStrcmp(const char* a, const char* b) {
    while (true) {
        if (*a != *b) {
            return (*a < *b) ? -1 : 1;
        }
        if (*a == '\0') break;
        a++;
        b++;
    }
    return 0;
}

int __thiscall UIMenuItemManager::onButtonHit(int this, const char* buttonName) {
    // Check if the button is the hardcoded "button_2" (second button? perhaps back/cancel)
    static const char* kButton2Path = "/onsl/buttons/button_2/button";
    bool match = true;
    const char* pSrc = kButton2Path;
    const char* pDst = buttonName;
    int count = 30; // max compare length
    while (count > 0) {
        if (*pSrc != *pDst) {
            match = false;
            break;
        }
        if (*pSrc == '\0') {
            break;
        }
        pSrc++;
        pDst++;
        count--;
    }
    if (match) {
        // Found the button_2: get the menu root and activate it (maybe play sound/animation)
        void* root = getMenuRoot();
        activateButton(root);
        return 1;
    }

    // Build the expected path for the current menu item (index stored at this+0x60)
    char expectedPath[100];
    formatPath(expectedPath, "/onsl/pause_mc/menu_items_anim/menu_stub/menu_%d/shared_menu_item/item", *(int*)(this + 0x60));

    // Compare using our custom string compare
    if (customStrcmp(expectedPath, buttonName) == 0) {
        // Button name matches the current menu item
        activateMenuItem();
        return 1;
    }

    return 0; // No match
}