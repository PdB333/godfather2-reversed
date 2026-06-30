// FUNC_NAME: ResourceManager::loadResource
undefined4 __thiscall ResourceManager::loadResource(int this, undefined4 resourceId)

{
  int resourceData;
  
  resourceData = FUN_005e3bb0(resourceId,0x10,0);  // Allocate 0x10 bytes for resource data
  if (resourceData != 0) {
    *(undefined4 *)(this + 0x44) = resourceId;     // +0x44: resource ID
    *(int *)(this + 0x40) = resourceData;          // +0x40: pointer to allocated resource data
    return 1;  // Success
  }
  return 0;  // Failed to allocate resource
}