// FUNC_NAME: ResourceManager::loadData
void __thiscall ResourceManager::loadData(void* this_)
{
    // +0x80: flag indicating whether data has been loaded
    if (*(char*)((int)this_ + 0x80) == '\0') {
        // +0x4c: target buffer for 32KB data block
        // DAT_0112f9c0 is likely a global pointer to a resource data block
        if (DAT_0112f9c0 != 0) {
            memcpy((void*)((int)this_ + 0x4c), DAT_0112f9c0, 0x8000);
        }
        // Mark as loaded
        *(char*)((int)this_ + 0x80) = 1;
    }
}