// FUNC_NAME: ResourceHolder::attachResource
void ResourceHolder::attachResource(int* pResource, int resourceId)
{
    // Store resource pointer at offset +0x04
    this->m_pResource = pResource;

    // Call vtable function at index 2 (prepare/init)
    pResource->vtbl->prepare();

    if (resourceId != 0)
    {
        // Call external function to resolve resource ID
        int result = FUN_004265d0(resourceId, this->m_pResource);
        // Store resolved handle at offset +0x08
        this->m_nHandle = result;

        // Call vtable function at index 1 (configure)
        pResource->vtbl->configure(resourceId, 0);

        // Call vtable function at index 3 (finalize)
        pResource->vtbl->finalize();
    }
    else
    {
        this->m_nHandle = 0;

        // Call vtable function at index 3 (finalize)
        pResource->vtbl->finalize();
    }
}