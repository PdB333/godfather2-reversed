// Xbox PDB: EARS_Modules_GetCrewSpecialtyName
// FUNC_NAME: CrewManager::addCrewMember
void __thiscall CrewManager::addCrewMember(int this, char *crewMemberName, undefined4 param_3, undefined4 param_4, void (*callback)(), undefined4 param_6, byte crewSpecialtyFlags, undefined4 param_8)
{
  char *localName;
  int i;
  
  i = 6;
  do {
    if ((crewSpecialtyFlags & 4) == 0) {
      if ((crewSpecialtyFlags & 8) == 0) {
        if ((crewSpecialtyFlags & 0x10) == 0) {
          if ((crewSpecialtyFlags & 0x20) == 0) {
            if ((crewSpecialtyFlags & 0x40) == 0) {
              if ((char)crewSpecialtyFlags < '\0') {
                FUN_004d3d90("Hitman"); // Output crew member specialty
                crewSpecialtyFlags = crewSpecialtyFlags & 0x7f;
              }
            }
            else {
              FUN_004d3d90("Medic");
              crewSpecialtyFlags = crewSpecialtyFlags & 0xbf;
            }
          }
          else {
            FUN_004d3d90("Engineer");
            crewSpecialtyFlags = crewSpecialtyFlags & 0xdf;
          }
        }
        else {
          FUN_004d3d90("SafeCracker");
          crewSpecialtyFlags = crewSpecialtyFlags & 0xef;
        }
      }
      else {
        FUN_004d3d90("Arsonist");
        crewSpecialtyFlags = crewSpecialtyFlags & 0xf7;
      }
    }
    else {
      FUN_004d3d90("Demolitions");
      crewSpecialtyFlags = crewSpecialtyFlags & 0xfb;
    }
    i = i + -1;
  } while (i != 0);
  *(undefined4 *)(DAT_01129930 + 0x2d0) = param_6; // +0x2d0 some global state related to crew
  *(undefined4 *)(DAT_01129930 + 0x2d4) = param_8; // +0x2d4
  localName = crewMemberName;
  if (crewMemberName == (char *)0x0) {
    localName = &DAT_0120546e; // Default empty string?
  }
  FUN_005a04a0("AddCrewMember",0,&DAT_00d8cdec,7,localName,&DAT_0120546e,&DAT_0120546e,&DAT_0120546e,
               &DAT_0120546e,&DAT_0120546e,&DAT_0120546e); // GameplayLogging call
  *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1; // +0x10 member count increment
  i = 5;
  localName = (char *)register0x00000010;
  do {
    if (*(int *)(localName + -0x10) != 0) {
      (**(code **)(localName + -4))(*(int *)(localName + -0x10)); // Execute callback chain
    }
    i = i + -1;
    localName = localName + -0x10;
  } while (-1 < i);
  if (crewMemberName != (char *)0x0) {
    (*callback)(crewMemberName); // Callback after member added
  }
  return;
}