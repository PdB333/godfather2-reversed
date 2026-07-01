// FUNC_NAME: MobFaceButtonHandler::checkMobfButtonPath
// Address: 0x009584c0
// Role: Checks if the given UI path string matches mob face button_4 or button_5,
// then sets the corresponding flag in the object at offsets +0x2c0 and +0x2c1.
// Returns true if either button path matched.

class MobFaceButtonHandler {
public:
    // Offsets relative to this:
    // +0x2c0 : uint8_t m_button4Active;  // set to 1 when path matches button_4
    // +0x2c1 : uint8_t m_button5Active;  // set to 1 when path matches button_5

    bool __thiscall checkMobfButtonPath(const char *path) {
        const int kPathLength = 30; // includes null terminator
        bool matched;

        // Check against "/mobf/buttons/button_4/button"
        const char *cmpStr = "/mobf/buttons/button_4/button";
        const char *p = path;
        int i = kPathLength;
        matched = true;
        do {
            if (i == 0) break;
            i--;
            if (*cmpStr != *p) {
                matched = false;
                break;
            }
            cmpStr++;
            p++;
        } while (matched);

        if (matched) {
            *(uint8_t*)(this + 0x2c0) = 1;
            return true;
        }

        // Check against "/mobf/buttons/button_5/button"
        cmpStr = "/mobf/buttons/button_5/button";
        const char *p2 = path;
        i = kPathLength;
        matched = true;
        do {
            if (i == 0) break;
            i--;
            if (*cmpStr != *p2) {
                matched = false;
                break;
            }
            cmpStr++;
            p2++;
        } while (matched);

        if (matched) {
            *(uint8_t*)(this + 0x2c1) = 1;
        }

        return matched;
    }
};