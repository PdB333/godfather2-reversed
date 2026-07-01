// FUNC_NAME: ResourceManager::findResourceByKey
bool __thiscall ResourceManager::findResourceByKey(void *this, const uint32_t *key, void **outObject)
{
    // this+0x1c: pointer to array of resource pointers
    // this+0x20: number of resources in array
    uint32_t count = *(uint32_t *)((uint8_t *)this + 0x20);
    if (count == 0)
        return false;

    uint32_t **resourceArray = *(uint32_t ***)((uint8_t *)this + 0x1c);
    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t *resource = resourceArray[i];
        // Resource key is stored at offsets 0x20, 0x24, 0x28, 0x2c (4 uint32s)
        if (resource[0x20/4] == key[0] &&
            resource[0x24/4] == key[1] &&
            resource[0x28/4] == key[2] &&
            resource[0x2c/4] == key[3])
        {
            *outObject = resource;
            return true;
        }
    }
    return false;
}