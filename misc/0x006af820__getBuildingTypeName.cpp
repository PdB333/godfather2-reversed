// FUNC_NAME: getBuildingTypeName
// Address: 0x006af820
// Role: Converts a building type enum value to its string representation.
// Used in The Godfather 2 for mapping property types (e.g., Business, Racket, etc.)

char* getBuildingTypeName(int buildingType)
{
    switch (buildingType)
    {
    case 0:
        return "Business";
    case 1:
        return "Racket";
    case 2:
        return "Compound";
    case 3:
        return "Doctor";
    case 4:
        return "Bank";
    case 5:
        return "Safehouse";
    case 6:
        return "Filler";
    case 7:
        return "Police";
    case 8:
        return "Airport";
    case 9:
        return "Hangout";
    default:
        return "Unknown";
    }
}