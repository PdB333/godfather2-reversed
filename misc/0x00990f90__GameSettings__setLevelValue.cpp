// FUNC_NAME: GameSettings::setLevelValue
// Address: 0x00990f90
// Role: Searches a linked list of level settings and stores a value in a key-value store.
// This function looks for a node with a matching level ID (param_3), then writes the node's stored value
// into a formatted key "_level%u" using a global settings manager (DAT_00d5df7c).

#include <cstdio>  // for sprintf

// Assuming a global settings object or manager (DAT_00d5df7c)
extern int g_settingsManager;  // placeholder for the actual global

// Internal helper function to set a key-value pair (defined elsewhere)
int SettingsManager_SetStringValue(int* manager, int unusedFlag, const char* key, int mode, const char* value);

// Data structure for a node in the level list
struct LevelNode {
    LevelNode* next;       // +0x04 next node in list
    int value;             // +0x40 stored value (e.g., some integer)
    short levelId;         // +0x44 level identifier
    // other fields may exist
};

// The class containing this method
class GameSettings {
public:
    // Offset of the head pointer in the class
    // +0x60: pointer to first LevelNode
    int setLevelValue(int unused, unsigned int levelId);
};

int GameSettings::setLevelValue(int unused, unsigned int levelId)
{
    LevelNode* node = *(LevelNode**)(this + 0x60);  // get head of level list

    if (node) {
        // Search for the node with matching levelId
        while (node->levelId != levelId) {
            if (levelId < (unsigned int)node->levelId) {
                // levelId not found; exit with code 2
                return 2;
            }
            node = node->next;
            if (!node) {
                return 2;  // end of list
            }
        }

        // Node found; format the key and value
        char keyBuffer[32];
        char valueBuffer[32];
        sprintf(keyBuffer, "_level%u", levelId);
        sprintf(valueBuffer, "%u", node->value);

        // Store the value in the global settings manager
        SettingsManager_SetStringValue(&g_settingsManager, 0, keyBuffer, 1, valueBuffer);
    }
    return 2;
}