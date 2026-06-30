// FUNC_NAME: ResourceManager::loadResource
// Function address: 0x00603330
// Loads or validates a resource using an ID (e.g. file path) and updates the provided handle.
// handle layout: +0x00: resource pointer, +0x04: unknown, +0x08: unknown, +0x0C: destructor callback
void ResourceManager::loadResource(void* resourceId, ResourceHandle* handle)
{
    char result;
    int outResource;
    char outFlag;

    outResource = 0;
    outFlag = '\0';

    result = FUN_006039d0(resourceId, &outResource, &outFlag); // Check/load resource info

    if (result == '\0') {
        // Resource not found or failed to load
        if (handle->ptr != 0) {
            handle->destructor(handle->ptr); // Release existing resource
        }
        handle->ptr = 0;
        handle->field_8 = 0;
        handle->field_4 = 0;
        return;
    }

    if (outFlag != '\0') {
        // Resource was newly loaded; release old handle data and assign new
        if (handle->ptr != 0) {
            handle->destructor(handle->ptr);
        }
        handle->ptr = 0;
        handle->field_8 = 0;
        handle->field_4 = 0;
        FUN_004ddaf0(outResource, handle); // Initialize handle with loaded resource
        return;
    }

    // Resource already cached; just finalize/apply
    FUN_004d3d90(outResource);
}