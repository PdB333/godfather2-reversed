// FUNC_NAME: OptionsControlPanel::handleWidgetEvent
class OptionsControlPanel {
public:
    char handleWidgetEvent(char* widgetPath);
private:
    char m_bIsVolume;       // +0x50: whether in volume bar mode
    char m_bIsScrolling;    // +0x51: whether in scrolling mode
    int m_controlId;        // +0x54: control index (e.g., controller number)

    void formatString(char* buffer, const char* format, int arg1, int arg2);
    void sendUICommand(const char* command, int param1, const char* target, int param2, const char* value);
    void playSound(void* soundSystem, int soundId);
};

char OptionsControlPanel::handleWidgetEvent(char* widgetPath)
{
    char done = 0;
    if (m_bIsVolume == 0) {
        unsigned int idx = 0;
        do {
            if (idx > 10) {
                return done;
            }
            char formatted[64];
            formatString(formatted, "/syss/content/control_%d/volume/bar_%d", m_controlId, idx);
            // Compare formatted with widgetPath
            char* a = formatted;
            char* b = widgetPath;
            char cmp;
            while (true) {
                char ca = *a;
                char cb = *b;
                if (ca != cb) {
                    // Simulate strcmp result: 1 if ca < cb else -1
                    int result = (ca < cb) ? 1 : -1;
                    // result != 0 -> not equal
                    break;
                }
                if (ca == 0) {
                    // equal strings
                    result = 0;
                    break;
                }
                a++;
                b++;
            }
            if (result == 0) {
                // Match found, select option value
                char value[64];
                formatString(value, "/syss/content/control_%d/volume/bar_%d", idx); // Actually format uses idx only? See decompiled: &DAT_00e3266c is likely "%d" or similar
                // Actually the decompiled shows FUN_00910160(local_40,&DAT_00e3266c,uVar7); so second format uses only the index
                // So value = formatted with just the index
                sendUICommand("SelectOptionValue", 0, g_uiCommandTarget, 1, value);
                done = 1;
            }
            idx++;
        } while (done == 0);
    } else {
        if (m_bIsScrolling != 0) {
            // Compare with "/syss/content/control_0/dropbox/dropdown/scrollbar/hspt"
            char* pattern = "/syss/content/control_0/dropbox/dropdown/scrollbar/hspt";
            char* p = pattern;
            char* q = widgetPath;
            bool match = true;
            int len = 0x38; // length of string (57 chars actually, but 0x38=56)
            while (true) {
                if (len == 0) break;
                len--;
                match = (*p == *q);
                p++; q++;
                if (!match) break;
            }
            if (!match) {
                // Second try: compare "/syss/content/control_0/dropbox/dropdown/scrollbar/slider/hspt"
                pattern = "/syss/content/control_0/dropbox/dropdown/scrollbar/slider/hspt";
                p = pattern;
                q = widgetPath;
                match = true;
                len = 0x3f; // 63 chars
                while (true) {
                    if (len == 0) break;
                    len--;
                    match = (*p == *q);
                    p++; q++;
                    if (!match) break;
                }
                if (!match) {
                    return 0;
                }
            }
            sendUICommand("UpdateScrolling", 0, g_uiCommandTarget, 0, nullptr);
            return 1;
        }
        // Compare with "/syss/content/control_0/dropbox/dropdown/scrollbar/caret_up"
        char* pattern = "/syss/content/control_0/dropbox/dropdown/scrollbar/caret_up";
        char* p = pattern;
        char* q = widgetPath;
        bool match = true;
        int len = 0x3c; // 60 chars
        while (true) {
            if (len == 0) break;
            len--;
            match = (*p == *q);
            p++; q++;
            if (!match) break;
        }
        if (match) {
            sendUICommand("MoveDropNonLoopUp", 0, g_uiCommandTarget, 0, nullptr);
            playSound(&g_soundSystem, 0);
            return 1;
        }
        // Compare with "/syss/content/control_0/dropbox/dropdown/scrollbar/caret_down"
        pattern = "/syss/content/control_0/dropbox/dropdown/scrollbar/caret_down";
        p = pattern;
        q = widgetPath;
        match = true;
        len = 0x3e; // 62 chars
        while (true) {
            if (len == 0) break;
            len--;
            match = (*p == *q);
            p++; q++;
            if (!match) break;
        }
        if (match) {
            sendUICommand("MoveDropNonLoopDown", 0, g_uiCommandTarget, 0, nullptr);
            playSound(&g_soundSystem, 0);
            return 1;
        }
        // Compare with "/syss/content/control_0/dropbox/dropdown/scrollbar/track/hspt" but pattern starts with '?' in decompiled? Actually pattern is "?/syss/..." with first char '?' skipped in loop.
        pattern = "/syss/content/control_0/dropbox/dropdown/scrollbar/track/hspt";
        p = pattern;
        q = widgetPath;
        match = true;
        len = 0x3e; // 62 chars
        while (true) {
            if (len == 0) break;
            len--;
            match = (*p == *q);
            p++; q++;
            if (!match) break;
        }
        if (match) {
            sendUICommand("PageUpDown", 0, g_uiCommandTarget, 0, nullptr);
            playSound(&g_soundSystem, 0);
            return 1;
        }
    }
    return done;
}