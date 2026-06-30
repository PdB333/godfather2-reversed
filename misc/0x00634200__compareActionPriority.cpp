// FUNC_NAME: compareActionPriority
// Address: 0x00634200
// Role: Comparator function for sorting action priorities/types.
// Uses a global category table (PTR_DAT_00e2a89c) for cross-type comparisons.
// Returns 1 if the first element should come before the second, 0 otherwise.

#include <cstdint>

// Global table: array of pointers to arrays of integers (e.g., category IDs).
// Each type index (int) points to an array; [2] is the category field.
extern int** g_priorityCategoryTable; // PTR_DAT_00e2a89c

// Forward declarations of helper functions
uint32_t FUN_00634030();   // Returns some type-specific value
uint32_t FUN_006340e0();   // Returns a boolean result for type 4
uint32_t FUN_006337e0();   // Fallback evaluation
void     FUN_00633920();   // Logging / side effect

uint32_t compareActionPriority(int* a, int* b)
{
    int typeA = *a;
    int typeB = *b;

    if (typeA == typeB)
    {
        if (typeA != 3)
        {
            if (typeA == 4)
            {
                // Type 4: evaluate a condition; return 1 if condition fails (i.e., a should go first)
                return (uint32_t)(FUN_006340e0() < 1);
            }

            // Other types: first check via FUN_00634030
            uint32_t v = FUN_00634030();
            if (v == 0xFFFFFFFF)
            {
                // Special case: re-evaluate (logs or checks internal state)
                int32_t r = (int32_t)FUN_00634030();
                if (r != -1)
                {
                    return (uint32_t)(r == 0);
                }
                // Fall back to another function
                v = FUN_006337e0();
            }
            return v;
        }

        // Type 3: compare float priority values (a+1 and b+1)
        float priA = *(float*)(a + 1);
        float priB = *(float*)(b + 1);
        if (priA <= priB)
        {
            return 1;
        }
    }
    else
    {
        // Types differ: compare category from global table
        int catA = g_priorityCategoryTable[typeA][2]; // category for typeA
        int catB = g_priorityCategoryTable[typeB][2]; // category for typeB
        if (catA == catB)
        {
            FUN_00633920();    // Log / handle equal categories
        }
        else
        {
            FUN_00633920();    // Log / handle different categories
        }
        // In all cross-type cases, return 0 (b should come before a)
    }

    return 0;
}