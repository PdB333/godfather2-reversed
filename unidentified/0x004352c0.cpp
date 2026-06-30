// FUN_004352c0: ResourceManager::getAsset
undefined* __thiscall ResourceManager::getAsset(int assetId, undefined4 subId, int context)
{
    undefined4 resolvedId;
    undefined* result;

    if (assetId != 0) {
        resolvedId = FUN_004dafd0(assetId);  // resolve asset ID -> internal hash
        if ((context == 0) && (*(int*)(this + 0x1c) != 0)) {
            context = *(int*)(this + 0x1c);  // +0x1c: m_defaultPackageContext
        }
        result = (undefined*)FUN_00435300(resolvedId, subId, context);  // allocate/load asset
        return result;
    }
    return &DAT_0120a5ec;  // null asset singleton
}