// FUNC_NAME: ResourceManager::isValidResourceType
bool ResourceManager::isValidResourceType(int resourceType)
{
    // Check if the resource type is one of the known valid types
    // Valid types are identified by their four-character codes:
    // 0x62617365 = "base"
    // 0x68756464 = "hudd"
    // 0x6d6d6170 = "mmap"
    // 0x6d61706d = "mapm"
    // 0x6d706c61 = "mpla"
    // 0x63757273 = "curs"
    // 0x73637262 = "scrb"
    if (resourceType == 0x62617365 || // "base"
        resourceType == 0x68756464 || // "hudd"
        resourceType == 0x6d6d6170 || // "mmap"
        resourceType == 0x6d61706d || // "mapm"
        resourceType == 0x6d706c61 || // "mpla"
        resourceType == 0x63757273 || // "curs"
        resourceType == 0x73637262)   // "scrb"
    {
        return false; // Invalid type (matches known types)
    }
    return true; // Valid type (unknown type)
}