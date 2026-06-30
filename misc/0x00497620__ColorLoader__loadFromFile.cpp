// FUNC_NAME: ColorLoader::loadFromFile

#include <cstdio>
#include <cwchar>
#include <cstdint>

// EA color resource file magic: "RCAE" (0x45414352 in little-endian)
#define COLOR_FILE_MAGIC 0x45414352
#define COLOR_FILE_VERSION 2

// Header structure for EA color resource files (28 bytes)
#pragma pack(push, 1)
struct ColorFileHeader {
    uint32_t magic;       // +0x00: must equal COLOR_FILE_MAGIC
    uint32_t version;     // +0x04: must equal COLOR_FILE_VERSION
    uint32_t count;       // +0x08: number of color entries
    uint64_t reserved1;   // +0x0C: unused
    uint64_t reserved2;   // +0x14: unused
};
#pragma pack(pop)

// Entry: 4-byte ID + 16 bytes of color data (likely 4xuint32 RGBA colors)
struct ColorEntry {
    uint32_t id;         // object/territory ID
    uint32_t colors[4];  // e.g., two colors for two states (initial values show 0xFFFF00 yellow)
};

// External functions (simplified signatures)
extern "C" {
    errno_t wfopen_s(FILE** pFile, const wchar_t* filename, const wchar_t* mode);
    size_t fread(void* buffer, size_t size, size_t count, FILE* stream);
    int feof(FILE* stream);
    int fclose(FILE* stream);
};

// Forward declarations of game functions (signatures inferred)
void* lookupObjectHandle(uint32_t* id); // returns pointer to handle table
void applyColorById(uint32_t id);        // applies color from loaded data to object

// Loads a color resource file and applies colors to matching objects
int ColorLoader::loadFromFile(const wchar_t* filename) {
    FILE* file = nullptr;
    int result = 0;

    // Open file in binary read mode
    if (wfopen_s(&file, filename, L"rb") != 0) {
        return result;
    }

    ColorFileHeader header;
    header.magic = COLOR_FILE_MAGIC;
    header.version = COLOR_FILE_VERSION;
    header.count = 0;
    header.reserved1 = 0;
    header.reserved2 = 0;

    // Read header (28 bytes)
    if (fread(&header, sizeof(header), 1, file) == 1) {
        // Validate magic and version
        if (header.magic == COLOR_FILE_MAGIC && header.version == COLOR_FILE_VERSION) {
            int entryCount = header.count;
            int index = 0;

            // Process each entry
            while (index < entryCount && !feof(file)) {
                // Initialize entry data with default colors (yellow/transparent)
                ColorEntry entry;
                entry.id = 0;
                // Default: first 3 bytes (alpha?): 0x01, 0xFF, 0xFF then 4 bytes 0x00FFFF00
                entry.colors[0] = 0xFFFFFF01; // ARGB? Actually 0x01FF as alpha? But typical: 0xFFFFFF01 is RGBA?
                entry.colors[1] = 0xFF00FFFF; // inverted? Not sure, but base is 0xFFFF00 => R=0,G=255,B=255? Actually 0xFFFF00 is yellow. We keep the initial layout.
                entry.colors[2] = 0;
                entry.colors[3] = 0xFFFF00;

                // Read entry ID (4 bytes)
                fread(&entry.id, sizeof(entry.id), 1, file);

                // Read color data (16 bytes) – overwrites initial values
                uint32_t colorBuffer[4];
                fread(colorBuffer, sizeof(colorBuffer), 1, file);
                // Copy into entry (or directly use, but for clarity)
                entry.colors[0] = colorBuffer[0];
                entry.colors[1] = colorBuffer[1];
                entry.colors[2] = colorBuffer[2];
                entry.colors[3] = colorBuffer[3];

                // Look up the object associated with this ID
                void** handlePtr = (void**)lookupObjectHandle(&entry.id);
                if (handlePtr != nullptr) {
                    void* obj = *handlePtr;
                    // Check if object exists and its type/index field at +0x28 equals 1
                    if (obj != nullptr && *(int*)((uint8_t*)obj + 0x28) == 1) {
                        applyColorById(entry.id);
                    }
                }

                index++;
            }
            result = 1; // success
        }
    }

    fclose(file);
    return result;
}