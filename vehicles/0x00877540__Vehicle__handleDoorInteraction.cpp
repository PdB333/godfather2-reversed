// FUNC_NAME: Vehicle::handleDoorInteraction
int __thiscall Vehicle::handleDoorInteraction(int *this, int *doorIndex, char param3)
{
  char *doorName;
  uint unaff_EBX;
  int doorHandleId;
  undefined4 soundEventId; // from a lookup
  undefined4 doorId; // mapped from doorIndex
  
  doorHandleId = 0;
  soundEventId = 0;
  doorName = (char *)0x0;
  doorId = 0xffffffff;
  
  // Map door index (0-3) to door ID
  switch(*doorIndex + -10) {
  case 0:
    doorId = 0;
    break;
  case 1:
    doorId = 1;
    break;
  case 2:
    doorId = 2;
    break;
  case 3:
    doorId = 3;
    break;
  default:
    goto default_case;
  }
  
  // Look up sound event and door name based on door index
  switch(*doorIndex + -10) {
  case 0: // front left
    soundEventId = FUN_00875af0(this, 0xf83e7a05);
    doorName = "JO_door_FL";
    doorHandleId = 0x5de881f8;
    break;
  case 1: // front right
    soundEventId = FUN_00875af0(this, 0x6391749d);
    doorName = "JO_door_FR";
    doorHandleId = (-(uint)(param3 != '\0') & 0x80a9d205) + 0x3714d2ea;
    break;
  case 2: // back left
    soundEventId = FUN_00875af0(this, 0xcaa90fdc);
    doorName = "JO_door_KL";
    doorHandleId = -0x871661a;
    break;
  case 3: // back right
    soundEventId = FUN_00875af0(this, 0xb5ff006);
    doorName = "JO_door_KR";
    doorHandleId = 0x3714d2ea;
  }
  
default_case:
  // Get door object by name (param_2 reused as output)
  doorIndex = (int *)0x0;
  (**(code **)(*this + 0x94))(&doorIndex, doorName); // vtable call to getChild or getDoor
  
  // Play opening animation/sound
  FUN_00460340(doorId, doorIndex);
  
  // Play additional sound effect
  FUN_0045f0c0(soundEventId, doorId, unaff_EBX >> 2, 1, 1, 0, 1);
  
  // Finalize handle interaction
  FUN_0087f8d0(this);
  
  return doorHandleId;
}