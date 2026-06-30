// FUNC_NAME: ResourceCache::getCachedData

undefined4 __fastcall ResourceCache::getCachedData(int this) {
    if (*(int *)(this + 0x20) == 0) {
        *(int *)(this + 0x20) = FUN_006f5dd0(**(undefined4 **)(this + 0x18));
    }
    return *(undefined4 *)(this + 0x20);
}