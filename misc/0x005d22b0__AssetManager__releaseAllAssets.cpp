// FUNC_NAME: AssetManager::releaseAllAssets
void AssetManager::releaseAllAssets(void)
{
    if (DAT_00f17618 != 0) {
        FUN_00611cc0(&PTR_PTR_01127408);  // release texture asset pointer
        FUN_00611cc0(&PTR_PTR_01126fc0);  // release mesh asset pointer
        FUN_00611cc0(&PTR_PTR_01126f18);  // release sound asset pointer
        FUN_00611cc0(&PTR_PTR_011270e0);  // release animation asset pointer
        FUN_00611cc0(&PTR_PTR_01127200);  // release shader asset pointer
        DAT_00f17618 = 0;                 // clear asset loaded flag
    }
}