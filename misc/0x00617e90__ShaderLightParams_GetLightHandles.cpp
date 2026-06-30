// Xbox PDB: ShaderLightParams::GetLightHandles
// FUNC_NAME: WorldLightManager::loadFromConfig
// Address: 0x00617e90 - Load world light parameters from configuration
// This function initializes an array of 4 light entries from a config source (like XML).
// Each entry has type, position, color, direction, and property fields.
// After reading, it counts how many entries have a non-zero color value.

class WorldLightManager {
public:
    // Offsets in the class (from this):
    // +0x04: configHandle (some configuration object, e.g., XML node)
    // +0x08: activeLightCount (number of lights with non-zero color)
    // +0x0C: lightEntries[4] (each entry is LightEntry, size 0x14 = 20 bytes)

    struct LightEntry {
        uint type;        // +0x00
        uint position;    // +0x04
        uint color;       // +0x08
        uint direction;   // +0x0C
        uint property;    // +0x10
    };

    void loadFromConfig(uint configHandle) {
        // this->configHandle = configHandle;
        *(uint *)(this + 4) = configHandle;
        // this->activeLightCount = 0;
        *(uint *)(this + 8) = 0;

        // Pointer to the color field of the first entry (entry[0].color)
        int *colorField = (int *)(this + 0x14); // LightEntry[0] at +0x0C, color at +0x08 relative to entry -> +0x14
        char keyBuffer[68];

        for (uint index = 0; index < 4; ++index) {
            LightEntry *entry = (LightEntry *)(this + 0x0C + index * 0x14);

            // Read type
            sprintf(keyBuffer, "%s[%d].type", "g_WorldLightParameters", index);
            entry->type = readConfigValue(configHandle, keyBuffer);

            // Read position
            sprintf(keyBuffer, "%s[%d].position", "g_WorldLightParameters", index);
            entry->position = readConfigValue(configHandle, keyBuffer);

            // Read color
            sprintf(keyBuffer, "%s[%d].color", "g_WorldLightParameters", index);
            entry->color = readConfigValue(configHandle, keyBuffer);

            // Read direction
            sprintf(keyBuffer, "%s[%d].direction", "g_WorldLightParameters", index);
            entry->direction = readConfigValue(configHandle, keyBuffer);

            // Read property
            sprintf(keyBuffer, "%s[%d].property", "g_WorldLightParameters", index);
            entry->property = readConfigValue(configHandle, keyBuffer);

            // If color is non-zero, increment active light count
            if (*colorField != 0) {
                *(int *)(this + 8) += 1;
            }

            // Advance colorField pointer to the next entry's color field
            colorField += 5; // 5 integers (20 bytes) per entry
        }
    }

private:
    // External function that reads a configuration value by key string.
    // Likely provides handles or integer IDs.
    uint readConfigValue(uint configHandle, const char *key);
};