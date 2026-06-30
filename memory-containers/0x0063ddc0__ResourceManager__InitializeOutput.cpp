// FUNC_NAME: ResourceManager::InitializeOutput
void ResourceManager::InitializeOutput(ResourceOutput* out)
{
    int versionArray[1] = {4}; // version query parameter
    int handle = FUN_00642970(*(int*)(this + 0x1c), versionArray); // +0x1c: pointer to resource table or factory
    out->version = 4;
    out->handle = handle;
    out->reserved1 = -1;
    out->reserved2 = -1;
}