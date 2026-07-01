// FUNC_NAME: CrewWeaponsWindow::handleMouseMove
// Address: 0x00967ab0
// This function handles mouse movement over crew member or weapon slots in the CrewWeaponsWindow UI.
// It checks if the provided HSpt path matches any slot's path, and if so, triggers UI commands and sounds.

// Assumed class layout:
// +0x00: vtable?
// +0x04: m_type (0 = left/crew members, non-zero = right/weapons)
// +0x10: m_crewCount (number of crew member slots)
// +0x14: m_weaponCount (number of weapon slots)

// External functions (adjust names as needed):
// void formatString(char* buffer, int size, const char* fmt, ...); // 0x005c4630
// void sendUICommand(const char* command, int arg1, void* context, int arg3, const char* path); // 0x005a04a0
// void updateUI(); // 0x009676f0
// void refreshCrewList(); // 0x009679c0
// void refreshWeaponsList(); // 0x00967a60
// void playUISound(SoundID* sound, int unknown); // 0x00408a00

// Global constants:
// extern const char* FORMAT_INDEX; // 0x00e3266c (likely "%d")
// extern SoundID SOUND_CLICK; // 0x011304d8 (sound to play on click/move)

char CrewWeaponsWindow::handleMouseMove(int this, const char* path) {
    char handled = 0;
    char formattedPath[96];
    int index = 0;

    if (*(int*)(this + 4) == 0) {
        // LEFT SIDE: Crew member slots
        while (index < *(int*)(this + 0x10)) {
            formatString(formattedPath, sizeof(formattedPath),
                         "/onli/mcMain/content_top_mc/crewWeaponsWindow/leftPlaceHolder/crewMember%d/hspt",
                         index);
            if (strcmp(formattedPath, path) == 0) {
                // Match found – format index string and trigger command
                formatString(formattedPath, sizeof(formattedPath), FORMAT_INDEX, index);
                sendUICommand("MouseCrewMembersMoveV", 0, UI_CONTEXT, 1, formattedPath);
                updateUI();
                refreshCrewList();
                sendUICommand("ShowWeaponsList", 0, UI_CONTEXT, 0, nullptr); // hide weapons list?
                // Play click sound
                SoundID sound = SOUND_CLICK;
                playUISound(&sound, 0);
                handled = 1;
            }
            index++;
            if (handled) {
                return handled;
            }
        }
    } else {
        // RIGHT SIDE: Weapon slots
        do {
            if (index >= *(int*)(this + 0x14)) {
                return handled;
            }
            formatString(formattedPath, sizeof(formattedPath),
                         "/onli/mcMain/content_top_mc/crewWeaponsWindow/rightPlaceHolder/weapon%d/hspt",
                         index);
            if (strcmp(formattedPath, path) == 0) {
                // Match found – format index string and trigger command
                formatString(formattedPath, sizeof(formattedPath), FORMAT_INDEX, index);
                sendUICommand("MouseWeaponsMoveV", 0, UI_CONTEXT, 1, formattedPath);
                refreshWeaponsList();
                updateUI();
                SoundID sound = SOUND_CLICK;
                playUISound(&sound, 0);
                handled = 1;
            }
            index++;
        } while (handled == 0);
    }
    return handled;
}