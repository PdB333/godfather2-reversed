// Xbox PDB: EARS_Apt_LobbyTeamPlayer_GetCrewDescription
// FUNC_NAME: CrewSpecialty::getSpecialtyString
char* __fastcall CrewSpecialty::getSpecialtyString(uint* specialtyFlags)
{
  uint flags = *specialtyFlags;
  
  if ((flags & 4) != 0) {
    return "$crew_specialty_demolition";
  }
  if ((flags & 8) != 0) {
    return "$crew_specialty_arsonist";
  }
  if ((flags & 0x10) != 0) {
    return "$crew_specialty_safe_cracker";
  }
  if ((flags & 0x20) != 0) {
    return "$crew_specialty_engineer";
  }
  if ((flags & 0x40) != 0) {
    return "$crew_specialty_medic";
  }
  // Bit 0x80 = bruiser (checked via signed comparison)
  char* result = "$crew_specialty_bruiser";
  if (-1 < (char)flags) {
    result = "";
  }
  return result;
}