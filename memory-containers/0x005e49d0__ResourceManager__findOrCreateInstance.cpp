// FUNC_NAME: ResourceManager::findOrCreateInstance
undefined4 __fastcall ResourceManager::findOrCreateInstance(undefined4 this, undefined4 assetId, undefined4 factoryContext)
{
  int handle;
  undefined1 buffer;
  int found;

  found = 0;
  handle = findAssetData(assetId, &buffer, &found);
  if ((handle != 0) && (found != 0)) {
    return createAssetInstance(factoryContext, handle);
  }
  return 0;
}