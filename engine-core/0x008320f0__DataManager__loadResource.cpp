// FUNC_NAME: DataManager::loadResource
void __thiscall DataManager::loadResource(int resourceType, int resourceId)
{
    char buffer1[80];  // used for type 1 or default
    char buffer2[80];  // used for type 1 or default
    char buffer3[92];  // used for type 0

    void *newResource;

    // Dispatch based on resource type stored at +0x24
    if (*(int *)(this + 0x24) == 0) {
        newResource = (void *)FUN_00830380(buffer3, resourceId);
    }
    else if (*(int *)(this + 0x24) == 1) {
        newResource = (void *)FUN_00830130(buffer1, resourceId, 0);
    }
    else {
        newResource = (void *)FUN_00830130(buffer2, resourceId, 0);
    }

    // Compare with current resource at +0x30
    if (this + 0x30 != (int)newResource) {
        // Copy/initialize resource data
        FUN_00820830((int)newResource);
        // Update field at +0x7c from new resource's +0x4c
        *(int *)(this + 0x7c) = *(int *)((int)newResource + 0x4c);
    }
}