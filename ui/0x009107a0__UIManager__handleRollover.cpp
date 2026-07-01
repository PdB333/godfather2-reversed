// FUNC_NAME: UIManager::handleRollover
// Address: 0x009107a0
// This function handles rollover (hover) events for UI elements.
// It checks if the given path string matches any known button or selection paths,
// and triggers the appropriate rollover event (RollOverButton, RollOverAdvancedButton, RollOverSelection).
// It also stores the matched index at this+0x2f4.

#include <cstdint>

// Forward declarations of external functions (from EARS engine)
void formatString(char* buffer, int bufferSize, const char* format, ...);
void setRolloverState(void* state, int value); // FUN_00408a00
void sendUIEvent(const char* eventName, int arg1, const char* arg2, int arg3, const char* path); // FUN_005a04a0
void formatPath(char* buffer, const char* format, int index); // FUN_00910160
void formatPath2(const char** path, const char* format, int index); // FUN_00910180

// Global state (likely a singleton)
extern uint8_t* g_uiState; // DAT_0112982c
extern void* g_rolloverState1; // DAT_011301c0
extern void* g_rolloverState2; // DAT_011302b0

class UIManager {
public:
    // Offset 0x2f4: stores the index of the last matched rollover item
    int m_rolloverIndex; // +0x2f4

    bool handleRollover(const char* path);
};

bool UIManager::handleRollover(const char* path) {
    // Early exit if global flag at g_uiState+0x48 is set
    if (*(char*)(g_uiState + 0x48) != '\0') {
        return false;
    }

    bool found = false;
    int index = 0;

    // First loop: check button paths "/appm/buttons/button_%d/button" for indices 0..5
    while (index <= 5 && !found) {
        char buffer[64];
        formatString(buffer, 0x40, "/appm/buttons/button_%d/button", index);

        // Compare buffer with path (custom strcmp-like loop)
        const uint8_t* p1 = (const uint8_t*)buffer;
        const uint8_t* p2 = (const uint8_t*)path;
        int cmpResult;
        while (true) {
            uint8_t c1 = *p1;
            uint8_t c2 = *p2;
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            c1 = p1[1];
            c2 = p2[1];
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            p1 += 2;
            p2 += 2;
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
        }

        if (cmpResult == 0) {
            // Match found: trigger RollOverButton event
            setRolloverState(&g_rolloverState1, 0);
            formatString(buffer, 0x40, "/appm/buttons/button_%d/button", index); // Redundant?
            sendUIEvent("RollOverButton", 0, "/appm/buttons/button_%d/button", 1, buffer);
            found = true;
        }
        index++;
    }

    // If not found, proceed to second loop for menu items (indices 0..7)
    index = 0;
    while (true) {
        if (found || index > 7) {
            return found;
        }

        // Check item hotspot path
        char buffer[64];
        formatPath(buffer, "/appm/mcMain/menu_mc/item%d/item_hspt", index);
        const uint8_t* p1 = (const uint8_t*)buffer;
        const uint8_t* p2 = (const uint8_t*)path;
        int cmpResult;
        while (true) {
            uint8_t c1 = *p1;
            uint8_t c2 = *p2;
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            c1 = p1[1];
            c2 = p2[1];
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            p1 += 2;
            p2 += 2;
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
        }

        if (cmpResult == 0) {
            // Match item hotspot: check sub-types (colorpicker, selector, etc.)
            int subIndex = 0;
            bool subFound = false;
            while (!subFound && subIndex <= 7) {
                // Check color_%d paths
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/color_%d", index, subIndex);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                    break;
                }
                subIndex++;
            }

            if (!subFound) {
                // Check colorpicker_hspt
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/colorpicker_hspt", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                }
            }

            if (!subFound) {
                // Check colorpicker_left
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/colorpicker_left", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                }
            }

            if (!subFound) {
                // Check colorpicker_right
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/colorpicker_right", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                }
            }

            if (!subFound) {
                // Check selector_hspt
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/selector_hspt", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                }
            }

            if (!subFound) {
                // Check selector_left
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/selector_left", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                }
            }

            if (!subFound) {
                // Check selector_right
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/type_mc/type/selector_right", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    subFound = true;
                }
            }

            if (!subFound) {
                // Check advancedIcon button path
                formatPath(buffer, "/appm/mcMain/menu_mc/item%d/advancedIcon/button_0/button", index);
                p1 = (const uint8_t*)buffer;
                p2 = (const uint8_t*)path;
                while (true) {
                    uint8_t c1 = *p1;
                    uint8_t c2 = *p2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    c1 = p1[1];
                    c2 = p2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    p1 += 2;
                    p2 += 2;
                    if (c1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                }
                if (cmpResult == 0) {
                    // Trigger RollOverAdvancedButton event
                    setRolloverState(&g_rolloverState2, 0);
                    sendUIEvent("RollOverAdvancedButton", 0, "/appm/mcMain/menu_mc/item%d/advancedIcon/button_0/button", 0, buffer);
                    found = true;
                }
            }

            // If none of the sub-paths matched, fall through to RollOverSelection
            if (!found) {
                formatPath2(&path, "/appm/mcMain/menu_mc/item%d/item_hspt", index);
                sendUIEvent("RollOverSelection", 0, "/appm/mcMain/menu_mc/item%d/item_hspt", 1, path);
                this->m_rolloverIndex = index; // Store index at +0x2f4
                found = true;
            }
        }

        index++;
    }
}