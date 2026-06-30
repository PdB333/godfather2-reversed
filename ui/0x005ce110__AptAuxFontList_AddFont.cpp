// Xbox PDB: AptAuxFontList::AddFont
//FUNC_NAME: FontManager::registerFont
// Address: 0x005ce110
// Registers a font name with associated data (param2, param3). Handles alias "EAS Sans Regular" -> "EAS Sans".

#include <cstring> // for __stricmp

// Forward declaration of internal resize function
int* resizeFontArray(int* oldBase, int newCount, int elementSize, int* countPtr, int* capacityPtr);

// Structure for a font entry (0x48 bytes)
// Offset 0x00: char name[64] (null-terminated)
// Offset 0x40: uint32_t field40
// Offset 0x44: uint32_t field44
struct FontEntry {
    char name[64];
    uint32_t field40;
    uint32_t field44;
};

// Class managing font registrations
class FontManager {
public:
    // +0x00: pointer to array of FontEntry
    FontEntry* fontEntries;
    // +0x04: number of entries
    int entryCount;
    // +0x08: capacity (max entries before resize)
    int entryCapacity;

    // Registers a font name with associated data.
    // If fontName is "EAS Sans Regular", also registers "EAS Sans" as an alias.
    void registerFont(char* fontName, uint32_t param2, uint32_t param3);
};

void __thiscall FontManager::registerFont(char* fontName, uint32_t param2, uint32_t param3)
{
    // Loop to handle alias registration
    while (true) {
        // Ensure capacity for one more entry
        if (entryCapacity < entryCount + 1) {
            int* newBase = resizeFontArray(
                reinterpret_cast<int*>(fontEntries),
                entryCount + 1,
                sizeof(FontEntry), // 0x48
                &entryCount,
                &entryCapacity
            );
            fontEntries = reinterpret_cast<FontEntry*>(newBase);
        }

        // Compute address of new entry and increment count
        FontEntry* newEntry = &fontEntries[entryCount];
        entryCount++;

        // Store the two data fields
        newEntry->field40 = param2;
        newEntry->field44 = param3;

        // Copy font name string into entry (null-terminated)
        char* src = fontName;
        char* dst = newEntry->name;
        do {
            char c = *src;
            *dst = c;
            src++;
            dst++;
        } while (c != '\0');

        // If the font name is "EAS Sans Regular", add an alias "EAS Sans"
        if (__stricmp(fontName, "EAS Sans Regular") != 0) {
            break;
        }
        fontName = "EAS Sans";
    }
}