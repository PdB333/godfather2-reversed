// FUNC_NAME: EntityContainer::findByPredicate
undefined4 __fastcall EntityContainer::findByPredicate(int thisPtr)
{
    char predicateResult;
    int playerData;
    undefined4 result;
    uint index;
    char searchContext[12];

    result = 0;
    // Check if container has items and global game state is valid
    if ( (*(int *)(thisPtr + 0x60) != 0) &&
         (**(int **)(DAT_012233a0 + 4) != 0) &&
         (**(int **)(DAT_012233a0 + 4) != 0x1f30) )
    {
        playerData = FUN_00471610();                 // Get current player state
        FUN_00424fb0(searchContext, 0);             // Clear search context buffer

        index = 0;
        if (*(int *)(thisPtr + 0x60) != 0)
        {
            while (true)
            {
                result = *(undefined4 *)(*(int *)(thisPtr + 0x5c) + index * 4); // +0x5c: item array, +0x60: item count
                predicateResult = FUN_006ba510(result, playerData + 0x30, searchContext);
                if (predicateResult != '\0')
                    break;

                index++;
                if (*(uint *)(thisPtr + 0x60) <= index)
                    return 0;
            }
            FUN_006ba720(index);                     // Notify that item at index was found
        }
        return result;
    }
    return 0;
}