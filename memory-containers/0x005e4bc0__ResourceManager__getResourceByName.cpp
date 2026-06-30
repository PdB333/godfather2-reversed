// FUNC_NAME: ResourceManager::getResourceByName
int __fastcall ResourceManager::getResourceByName(void* this, const char* name, int resourceType, int defaultVal)
{
    int id;
    char successFlag; // unused byte, likely indicates success

    id = 0;
    if (resolveNameToId(name, &successFlag, &id) && id != 0) {
        return getResourceById(resourceType, id, defaultVal);
    }
    return 0;
}