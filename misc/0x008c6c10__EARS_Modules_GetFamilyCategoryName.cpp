// Xbox PDB: EARS_Modules_GetFamilyCategoryName
// FUNC_NAME: occupationToString
// Address: 0x008c6c10
// Role: Converts an occupation/role enum to a display string. Used for NPC types (Innocent, Worker, Law, Gangster).

const char* occupationToString(int role)
{
    // Role enum values: 0=Innocent, 1=Worker, 2=Law, 3=Gangster
    switch (role)
    {
    case 0:
        return "Innocent";
    case 1:
        return "Worker";
    case 2:
        return "Law";
    case 3:
        return "Gangster";
    default:
        return "Unknown";
    }
}