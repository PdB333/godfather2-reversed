// FUNC_NAME: Comparator::compareItems
// Address: 0x006ed990
// Role: Compares two items (each defined by a pair of values) against a context target.
//       The comparison type is determined by the first int in the struct (0=byte,1=int,2=float).
//       Returns true if the first item is "less than" the second according to the target-based distance.

// Forward declarations of the underlying comparison helpers (defined elsewhere)
byte compareBytePair(int a, int b, int context);
int compareIntPair(int a, int b, int context);
long double compareFloatPair(int a, int b, int context);

bool Comparator::compareItems(int* param1, int contextValue)
{
    // param1 points to a struct with layout:
    // +0x00: type (int)
    // +0x04: first item first value (int)
    // +0x08: first item second value (int)
    // +0x0C: second item first value (int)
    // +0x10: second item second value (int)
    int type = param1[0];
    bool result = false;

    if (type == 0)
    {
        // Byte comparison
        byte cmp1 = compareBytePair(param1[1], param1[2], contextValue);
        byte cmp2 = compareBytePair(param1[3], param1[4], contextValue);
        result = (cmp1 < cmp2);
    }
    else if (type == 1)
    {
        // Integer comparison
        int cmp1 = compareIntPair(param1[1], param1[2], contextValue);
        int cmp2 = compareIntPair(param1[3], param1[4], contextValue);
        return (cmp1 < cmp2);
    }
    else if (type == 2)
    {
        // Float comparison (note the cast to float before comparison)
        long double cmp1 = compareFloatPair(param1[1], param1[2], contextValue);
        long double cmp2 = compareFloatPair(param1[3], param1[4], contextValue);
        if ((float)cmp1 < cmp2)
        {
            return true;
        }
        return false;
    }
    return result;
}