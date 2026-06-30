// FUNC_NAME: DataSourceBinding::initialize

void DataSourceBinding::initialize(DataSource* pDataSource, int resourceId)
{
    // +0x04: Store data source pointer
    this->pDataSource = pDataSource;

    // VTable offset +0x08: vfunc2 (pre‑initialization)
    pDataSource->vfunc2();

    if (resourceId != 0)
    {
        // Create a resource handle via the engine helper
        // FUN_004265d0 likely creates a stream reader or asset container
        this->pResource = createResourceHandle(resourceId, this->pDataSource);

        // VTable offset +0x04: vfunc1 (bind resource to source)
        pDataSource->vfunc1(resourceId, 0);

        // VTable offset +0x0C: vfunc3 (finalize binding)
        pDataSource->vfunc3();
    }
    else
    {
        // No resource provided – clear handle and finalize
        this->pResource = nullptr;
        pDataSource->vfunc3();
    }
}