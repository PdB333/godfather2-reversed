// FUNC_NAME: buildingTypeToString
char* buildingTypeToString(int buildingType)
{
    switch (buildingType) {
    case 0:
        return "Business";      // Front business
    case 1:
        return "Racket";        // Criminal racket
    case 2:
        return "Compound";      // Secure compound
    case 3:
        return "Doctor";        // Doctor's office
    case 4:
        return "Bank";          // Bank
    case 5:
        return "Safehouse";     // Safehouse
    case 6:
        return "Filler";        // Filler building (unused?)
    case 7:
        return "Police";        // Police station
    case 8:
        return "Airport";       // Airport
    case 9:
        return "Hangout";       // Hangout spot
    default:
        return "Unknown";       // Invalid/unknown type
    }
}