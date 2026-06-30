// FUNC_NAME: priorityCompare
// Function address: 0x00587780
// Role: Compares two structures based on flags and fields, returns bool indicating if first is less than second (for sorting/ordering)
uint __fastcall priorityCompare(int *param2, int *param3, int unusedParam1)
{
    int local_primary_a;
    int local_secondary_a;
    int local_primary_b;
    int local_secondary_b;
    uint flagA, flagB;
    uint result;

    // Extract flags from offset 0x2C (11 * 4)
    flagA = param2[0xB] & 0x20;
    if (flagA == 0 || param2[0] < 2)
    {
        local_primary_a = param2[0];
        local_secondary_a = local_primary_a;
    }
    else
    {
        local_primary_a = param2[0];
        local_secondary_a = param2[1];
    }

    flagB = param3[0xB] & 0x20;
    if (flagB == 0 || param3[0] < 2)
    {
        local_primary_b = param3[0];
        local_secondary_b = local_primary_b;
    }
    else
    {
        local_primary_b = param3[0];
        local_secondary_b = param3[1];
    }

    if (local_secondary_a == local_secondary_b)
    {
        // Tie on secondary values
        int cmpA = 0;
        if (flagA != 0 && local_primary_a >= 4)
        {
            cmpA = param2[5]; // offset 0x14
        }

        if (flagB != 0 && local_primary_b > 3)
        {
            // Compare using sub-field at offset 0x14
            int cmpB = param3[5];
            return (uint)(cmpA < cmpB); // bool: is cmpA less than cmpB?
        }
        // Fallback: compare primary values
        return (uint)(local_primary_a < 0); // treat as signed? likely no meaning
    }
    else
    {
        // Different secondary values
        if (flagA != 0 && local_primary_a > 1)
        {
            local_primary_a = param2[1];
        }
        // Keep high byte of local_primary_a for potential sign extension (unused here)
        // Compare with secondary value of param3
        if (flagB != 0 && local_primary_b > 1)
        {
            return (uint)(local_primary_a < param3[1]);
        }
        else
        {
            return (uint)(local_primary_a < local_primary_b);
        }
    }
}