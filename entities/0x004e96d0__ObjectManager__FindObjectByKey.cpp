// FUNC_NAME: ObjectManager::FindObjectByKey

// Function at 0x004e96d0
// Looks up an object by a 16-byte key (4 x uint32) via a global object table.
// Returns pointer to the first field of the matching entry, or NULL if not found.

struct ObjectKey
{
    uint32_t data[4];
};

struct ObjectEntry
{
    void* objectPtr; // +0x00
    char unknown[0x14]; // total size 0x18
};

struct ObjectManager
{
    char header[0x10]; // unknown header before the array
    ObjectEntry entries[1]; // placeholder, accessed via index
};

// Global pointer to the object manager (stored at address 0x012054c0)
ObjectManager* g_pObjectManager = (ObjectManager*) * (int*)0x012054c0;

// Forward declaration of the lookup function (at 0x004e1900)
int FindIndexByKey(ObjectKey* key);

void* __thiscall ObjectManager::FindObjectByKey(ObjectKey* key)
{
    ObjectKey localKey = *key;
    int index = FindIndexByKey(&localKey);

    if (index >= 0)
    {
        ObjectEntry* entry = (ObjectEntry*)((uint8_t*)g_pObjectManager + 0x10 + index * sizeof(ObjectEntry));
        if (entry != nullptr)
        {
            return entry->objectPtr;
        }
    }
    return nullptr;
}