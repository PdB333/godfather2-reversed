// FUNC_NAME: isValidResourceIndex
// Function at 0x00962d10: Checks if an index is within valid bounds for a given resource type.
// The resource type (param_2) determines the maximum allowed index.
// Returns true if param_1 is within the allowed range for that type.
bool isValidResourceIndex(uint index, int resourceType)
{
    uint maxIndex = 7; // default maximum inclusive (<=7)

    switch (resourceType)
    {
    case 0: // type 0: max index 3 (inclusive)
        maxIndex = 3;
        break;
    case 1: // type 1: max index 4 (strictly <5)
        return index < 5;
    case 2: // type 2: max index 5 (strictly <6)
        return index < 6;
    case 3: // type 3: max index 6 (strictly <7)
        return index < 7;
    // default: maxIndex is 7, so returns index <= 7
    }

    return index <= maxIndex;
}