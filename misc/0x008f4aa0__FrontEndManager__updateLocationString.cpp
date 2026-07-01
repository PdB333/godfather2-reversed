// FUNC_NAME: FrontEndManager::updateLocationString
// Address: 0x008f4aa0
// This function updates the location string displayed on the front end.
// Based on game state (front end active vs. city), it retrieves the current city or district name (localized),
// formats it, and optionally calls a callback function stored at a fixed offset in the parameter structure.
void FrontEndManager::updateLocationString(undefined2 **outString) // param_1 is a pointer to a caller's wchar_t* buffer
{
    // Global state checks
    if ( (DAT_012233a0 == 0) || (**(int **)(DAT_012233a0 + 4) == 0) ) // +0x4: maybe "front end active" flag
    {
        FUN_004dba80("front end", 9); // Set string "front end" (length 9)
    }
    else
    {
        // city name manager singleton at DAT_0112a66c
        if ( *(int *)(DAT_0112a66c + 8) != 0 ) // +0x8: some city ID
        {
            undefined4 cityId = FUN_00849e60( *(int *)(DAT_0112a66c + 8) ); // Get city identifier
            char *cityName = (char *)FUN_0068b910(cityId); // Convert to localized string (ASCII?)
            // Calculate length including null terminator
            do {
                cVar1 = *cityName;
                cityName++;
            } while (cVar1 != '\0');
            FUN_004dba80(cityName, (int)cityName - (int)(cityName + 1)); // Print the string with its length
            goto LAB_008f4b1b;
        }
        // Default: use placeholder for Havana
        FUN_004dba80("{$city_name_havana}", 0x13); // Placeholder string, length 19
    }
LAB_008f4b1b:
    // Output handling: if outString is not pointing to the local buffer (stack check),
    // copy the result to the caller's buffer.
    undefined2 *localBuffer; // local_10
    undefined4 local_c;      // uninitialized (likely junk)
    code *local_4;           // uninitialized (likely callback pointer in the caller's struct)
    if (outString != &localBuffer) // This check seems to verify that outString is not the same as the local variable's address
    {
        undefined2 *src = localBuffer;
        if (localBuffer == (undefined2 *)0x0)
        {
            src = &DAT_00e2df14; // Possibly a default empty string
        }
        FUN_004dbb10(src, 0, local_c); // Copy to output? (0 may be flags)
    }
    if (localBuffer != (undefined2 *)0x0)
    {
        (*local_4)(localBuffer); // Callback: e.g., GUI update function
    }
    return;
}