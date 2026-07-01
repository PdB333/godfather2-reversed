// FUNC_NAME: Entity::setAssetId
void __thiscall Entity::setAssetId(const int *pAssetId)
{
    // Compare current asset ID (stored as 4 ints at offsets 0x180-0x18c)
    if ((*(int *)(this + 0x180) != pAssetId[0]) ||
        (*(int *)(this + 0x184) != pAssetId[1]) ||
        (*(int *)(this + 0x188) != pAssetId[2]) ||
        (*(int *)(this + 0x18c) != pAssetId[3]))
    {
        // If a cached resource handle exists (offset 0x190), release it
        if (*(int *)(this + 0x190) != 0)
        {
            FUN_004daf90((undefined4 *)(this + 0x190)); // releaseResourceHandle
            *(int *)(this + 0x190) = 0;
        }
        // Copy new asset ID into the member fields
        *(int *)(this + 0x180) = pAssetId[0];
        *(int *)(this + 0x184) = pAssetId[1];
        *(int *)(this + 0x188) = pAssetId[2];
        *(int *)(this + 0x18c) = pAssetId[3];
    }
}