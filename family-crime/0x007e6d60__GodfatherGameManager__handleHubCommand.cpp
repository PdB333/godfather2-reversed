// FUNC_NAME: GodfatherGameManager::handleHubCommand
// Address: 0x007e6d60
// Handles hub/map UI commands (0x31-0x42) from input or menu.
// Uses m_playerState = *(int*)(this + 0x58) as pointer to PlayerData.
// m_hubCommandId (this+0x278) and m_hubReturnValue (this+0x274) store state.
// Global g_hubReturnOffset = DAT_00e5341c.

#include <cstdint>

// Forward declarations of called functions.
bool isOnline();                                    // 0x00481620
int getPlayerState();                               // 0x007e56b0 (returns 0/1/2)
void openHubPanel();                                // 0x007e6cc0
void closeHubPanel();                               // 0x007e5cc0
void setHubWeaponFlag(bool flag);                   // 0x007e68a0
bool isHubWeaponAllowed();                          // 0x006252f0
void showUIPanel(int panelId);                      // 0x007f63e0
void hideUIPanel(int panelId);                      // 0x007f6420
void playSound(int soundId, int volume);            // 0x0079f100
void setMenuTransition(int transition, int param);  // 0x006901b0
void clearMenuTransition(int transition);          // 0x006901e0
bool isMenuTransitionActive(int transition);        // 0x00690150
int getCurrentPlayer();                             // 0x00800a90 (returns Player*)
void setPlayerHubState(uint32_t state);             // 0x0093b000
void clearPlayerHubState();                         // 0x0093b080
void showPlayerAction(uint32_t action, bool flag);  // 0x00702e90
void toggleMinimap(bool show);                      // 0x007ab6b0
void refreshHubData();                              // 0x007e5670
void startHubMode(int mode);                        // 0x007e4f00
bool isInHubMode();                                 // 0x007ab1f0 (returns hubMode pointer)
void setHUBActiveFlag(uint flag1, uint flag2);      // 0x007f4530
bool handleBaseCommand(int arg1, int arg2, int arg3, int cmd, int* data); // 0x007abec0
void deleteHUDObject(int* objPtr);                  // 0x004daf90

// Constants for command IDs.
enum HubCommand : int {
    HUB_CMD_OPEN_FAVORITE    = 0x31, // '1'
    HUB_CMD_FAVORITE_ACTION  = 0x32, // '2'
    HUB_CMD_SET_STATE1       = 0x33, // '3'
    HUB_CMD_CLOSE_HUB_PANEL  = 0x34, // '4'
    HUB_CMD_OPEN_FAMILY_MENU = 0x35, // '5'
    HUB_CMD_SHOW_HUD         = 0x36, // '6'
    HUB_CMD_HIDE_HUD         = 0x37, // '7'
    HUB_CMD_SHOW_HUD_BAR     = 0x38, // '8'
    HUB_CMD_HIDE_HUD_BAR     = 0x39, // '9'
    HUB_CMD_TOGGLE_MINIMAP   = 0x3a, // ':'
    HUB_CMD_START_MODE       = 0x3b, // ';'
    HUB_CMD_TOGGLE_MAP       = 0x3c, // '<'
    HUB_CMD_SET_MAP_FOCUS    = 0x3d, // '='
    HUB_CMD_REFRESH          = 0x3e, // '>'
    HUB_CMD_OPEN_DON_MENU    = 0x3f, // '?'
    HUB_CMD_CLOSE_DON_MENU   = 0x40, // '@'
    HUB_CMD_SET_STATE2       = 0x41, // 'A'
    HUB_CMD_CLOSE_HUB        = 0x42  // 'B'
};

// Constants for UI panels.
const int PANEL_HUB      = 9;
const int PANEL_HUD_BAR  = 0x42;

// Magic hash used in favorite action.
const int FAVORITE_HASH  = 0x3afd3141;

// returns: true if command was fully handled, false otherwise
bool __thiscall GodfatherGameManager::handleHubCommand(int param_2, int param_3, int param_4, HubCommand cmd, int* param_6) {
    // Offsets used:
    // +0x58 : pointer to PlayerData (m_playerData)
    // +0x274: m_hubReturnOffset (global offset added)
    // +0x278: m_hubCommandId (stores param_2 when needed)
    // +0x8e0: bitflags (bit 10 = isDonMenuOpen?)
    // +0xff8 : unknown byte, possibly hubState
    // +0x1aa : hub mode type (0 = minimap, 1 = full map)
    // +0x31a8: pointer to some dynamic object (maybe a panel)
    // +0x2528: pointer to another dynamic object (maybe HUD bar)
    extern int g_hubReturnOffset; // DAT_00e5341c

    int* playerData = *(int**)(this + 0x58); // +0x58
    int state = getPlayerState(playerData);  // 0x007e56b0 (maybe 0=free, 1=menu, 2=hub)
    bool handled = false;

    switch(cmd) {
    case HUB_CMD_OPEN_FAVORITE: // 0x31
        if (isOnline()) {
            openHubPanel(); // 0x007e6cc0
            handled = true;
        }
        break;

    case HUB_CMD_FAVORITE_ACTION: // 0x32
        if (isOnline()) {
            if (param_6 != nullptr && *param_6 == FAVORITE_HASH) {
                bool allowed = isHubWeaponAllowed(); // 0x006252f0
                setHubWeaponFlag(allowed); // 0x007e68a0
            } else {
                setHubWeaponFlag(false);
            }
            handled = true;
        }
        break;

    case HUB_CMD_SET_STATE1: // 0x33
        if (state == 2) {
            *(int*)(this + 0x278) = param_2; // m_hubCommandId
            handled = true;
        }
        break;

    case HUB_CMD_CLOSE_HUB_PANEL: // 0x34
        closeHubPanel(); // 0x007cb1f0 (maybe close fullscreen panel)
        if (*(int*)(playerData + 0x31a8) != 0) {
            deleteHUDObject((int*)(playerData + 0x31a8));
            *(int*)(playerData + 0x31a8) = 0;
        }
        hideUIPanel(PANEL_HUB); // 0x007f6420(9)
        handled = true;
        break;

    case HUB_CMD_OPEN_FAMILY_MENU: // 0x35
        playSound(0x24, 0); // 0x0079f100
        *(int*)(this + 0x278) = param_2; // m_hubCommandId
        showUIPanel(PANEL_HUB); // 0x007f63e0(9)
        if ((*(uint*)(playerData + 0x8e0) >> 10 & 1) != 0) { // bit 10: isDonMenuOpen
            int* player = getCurrentPlayer(); // 0x00800a90
            if (player != nullptr) {
                showPlayerAction(*(uint*)(player + 0x35c), true); // 0x00702e90
            }
        }
        handled = true;
        break;

    case HUB_CMD_SHOW_HUD: // 0x36
        showUIPanel(PANEL_HUD_BAR); // 0x007f63e0(0x42)
        setMenuTransition(0x17, 0); // 0x006901b0
        if ((*(uint*)(playerData + 0x8e0) >> 10 & 1) != 0) {
            int* player = getCurrentPlayer();
            if (player != nullptr) {
                showPlayerAction(0, true); // 0x00702e90(0) - maybe hide?
            }
        }
        handled = true;
        break;

    case HUB_CMD_HIDE_HUD: // 0x37
        hideUIPanel(PANEL_HUD_BAR); // 0x007f6420(0x42)
        if (*(int*)(playerData + 0x2528) != 0) {
            deleteHUDObject((int*)(playerData + 0x2528));
            *(int*)(playerData + 0x2528) = 0;
        }
        clearMenuTransition(0x17); // 0x006901e0
        handled = true;
        break;

    case HUB_CMD_SHOW_HUD_BAR: // 0x38
        showUIPanel(PANEL_HUD_BAR); // 0x007f63e0(0x42)
        handled = true;
        break;

    case HUB_CMD_HIDE_HUD_BAR: // 0x39
        hideUIPanel(PANEL_HUD_BAR); // 0x007f6420(0x42)
        if (*(int*)(playerData + 0x2528) != 0) {
            deleteHUDObject((int*)(playerData + 0x2528));
            *(int*)(playerData + 0x2528) = 0;
        }
        handled = true;
        break;

    case HUB_CMD_TOGGLE_MINIMAP: // 0x3a
        toggleMinimap(false); // 0x007ab6b0(0)
        handled = true;
        break;

    case HUB_CMD_START_MODE: // 0x3b
        startHubMode(param_2); // 0x007e4f00
        handled = true;
        break;

    case HUB_CMD_TOGGLE_MAP: // 0x3c
    {
        int* hubMode = isInHubMode(); // 0x007ab1f0
        if (hubMode != nullptr && *(char*)(playerData + 0xff8) == '\0') {
            if (*(char*)(hubMode + 0x1aa) != 0x01) { // not full map
                setHUBActiveFlag(1, 0); // 0x007f4530
                setHUBActiveFlag(0, 1);
                handled = true;
                break;
            }
            int tmp = 1; // fallthrough to case 0x3d with flag=1
            goto handle_map_focus;
        }
        // else fallthrough to case 0x3d with flag=0
        tmp = 0;
    }
    // falls through
    case HUB_CMD_SET_MAP_FOCUS: // 0x3d
    {
        int tmp = (cmd == HUB_CMD_SET_MAP_FOCUS) ? 0 : 1; // re-derived
        if (cmd == HUB_CMD_TOGGLE_MAP) tmp = 0; // but we already have tmp from above, this is messy, but decompiled shows fallthrough with uVar5
        // decompiled: uVar5 set to 0 for case 0x3d, else from case 0x3c it's 1. Actually in decompiled it's:
        // case 0x3c: if condition, then set uVar5=1; else fallthrough with uVar5=0.
        // So we'll just use the already computed tmp.
    }
    handle_map_focus:
        setHUBActiveFlag(tmp, 1); // 0x007f4530
        setHUBActiveFlag(0, 0);
        handled = true;
        break;

    case HUB_CMD_REFRESH: // 0x3e
        refreshHubData(); // 0x007e5670
        handled = true;
        break;

    case HUB_CMD_OPEN_DON_MENU: // 0x3f
        *(int*)(this + 0x278) = param_2; // m_hubCommandId
        setMenuTransition(0x18, 0); // 0x006901b0
        showUIPanel(PANEL_HUD_BAR); // 0x007f63e0(0x42)
        if (isMenuTransitionActive(0x3f)) { // 0x00690150
            setMenuTransition(0x19, 0); // 0x006901b0
        }
        if (isOnline()) {
            int* player = getCurrentPlayer();
            if (player == nullptr) {
                setPlayerHubState(0); // 0x0093b000(0)
            } else {
                setPlayerHubState(*(uint*)(player + 0x510)); // 0x0093b000
            }
        }
        handled = true;
        break;

    case HUB_CMD_CLOSE_DON_MENU: // 0x40
        closeHubPanel(); // 0x007cb1f0
        if (*(int*)(playerData + 0x31a8) != 0) {
            deleteHUDObject((int*)(playerData + 0x31a8));
            *(int*)(playerData + 0x31a8) = 0;
        }
        clearMenuTransition(0x18); // 0x006901e0
        hideUIPanel(PANEL_HUD_BAR); // 0x007f6420(0x42)
        clearMenuTransition(0x19); // 0x006901e0
        if (isOnline()) {
            clearPlayerHubState(); // 0x0093b080
        }
        *(int*)(this + 0x274) = g_hubReturnOffset + param_2; // m_hubReturnOffset = global + param2
        handled = true;
        break;

    case HUB_CMD_SET_STATE2: // 0x41
        if (state == 2) {
            *(int*)(this + 0x278) = param_2;
            handled = true;
        }
        break;

    case HUB_CMD_CLOSE_HUB: // 0x42
        closeHubPanel(); // 0x007e5cc0
        handled = true;
        break;

    default:
        // delegate to base handler
        handled = handleBaseCommand(param_2, param_3, param_4, cmd, param_6); // 0x007abec0
        break;
    }

    return handled;
}