// FUNC_NAME: AppearanceManager::findFirstValidColorSet
int* __fastcall AppearanceManager::findFirstValidColorSet(int* thisPtr)
{
    int* entityObj;
    int* colorSetPtr; // points to four consecutive ints at entity+0xb4
    uint32_t index = 0;

    // +0x128: count of elements in array at +0x124
    if (*(int*)(thisPtr + 0x128) != 0)
    {
        do
        {
            // +0x124: pointer to array of entity IDs/pointers
            // FUN_009b9c00 looks up the entity by ID/reference
            entityObj = (int*)FUN_009b9c00(*(uint32_t*)(*(int*)(thisPtr + 0x124) + index * 4));
            colorSetPtr = (int*)(entityObj + 0xb4); // +0xb4: pointer to color set (4 ints)

            // +0x74: entity type (e.g., 4 = character/gangster)
            if ((*(int*)(entityObj + 0x74) == 4) &&
                // Check if any of the four color ints is NOT the sentinel value (uninitialized)
                (((*colorSetPtr != -0x45245246 || *(int*)(entityObj + 0xb8) != -0x41104111) ||
                  *(int*)(entityObj + 0xbc) != -0x153ea5ab) || *(int*)(entityObj + 0xc0) != -0x6eeff6ef))
            {
                return colorSetPtr;
            }

            // Also return if any of the four ints is non-zero (valid override)
            if (*colorSetPtr != 0)
                return colorSetPtr;
            if (*(int*)(entityObj + 0xb8) != 0)
                return colorSetPtr;
            if (*(int*)(entityObj + 0xbc) != 0)
                return colorSetPtr;
            if (*(int*)(entityObj + 0xc0) != 0)
                return colorSetPtr;

            index++;
        } while (index < *(uint32_t*)(thisPtr + 0x128));
    }

    // +0xcc: default/invalid color set to return when nothing valid found
    return (int*)(thisPtr + 0xcc);
}