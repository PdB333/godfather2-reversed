// FUNC_NAME: readPageUpDownConfig
// Address: 0x00966390
// Role: Reads the "PageUpDown" config value and applies it as a key binding.

#include <cstring>
#include <cstdio>

// Forward declarations of internal engine functions
// Gets a configuration string by key; fills buffer with the value, or defaultVal if missing.
// Params: key, output buffer, default value pointer, flags (unknown).
extern void getConfigString(const char* key, char* buffer, int* defaultVal, int flags);

// Applies the provided integer as a page up/down key mapping.
extern void setPageUpDownKey(int key);

void readPageUpDownConfig()
{
    char buffer[256];   // Buffer to hold the config string (max 255 chars + null)
    int key = 0;        // Parsed key value

    memset(buffer, 0, sizeof(buffer));

    // Read the "PageUpDown" setting; default value pointer at DAT_00d8cdec (unknown)
    getConfigString("PageUpDown", buffer, 0, 0);  // third param likely default value pointer

    // Parse the integer from the config string
    sscanf(buffer, "%d", &key);

    // Apply the parsed key value (e.g., map to input action)
    setPageUpDownKey(key);
}