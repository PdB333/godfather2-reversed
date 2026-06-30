// FUNC_NAME: SomeClass::removeFromList
void __thiscall SomeClass::removeFromList(int this, int param_2)
{
  uint uVar1;
  int *piVar2;
  int local_8;
  undefined4 local_4;
  
  if (param_2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = param_2 + 0x48; // +0x48: offset to some node/list entry
  }
  local_4 = 0;
  if (local_8 != 0) {
    local_4 = *(undefined4 *)(local_8 + 4); // +0x04: next pointer in list
    *(int **)(local_8 + 4) = &local_8; // unlink: set next to self (circular?)
  }
  uVar1 = 0;
  if (*(uint *)(this + 0xf4) != 0) { // +0xf4: count of entries in array
    piVar2 = *(int **)(this + 0xf0); // +0xf0: pointer to array of pairs (key, value?)
    do {
      if (*piVar2 == local_8) { // match found
        if (-1 < (int)uVar1) {
          FUN_006b3580(uVar1); // remove from array at index uVar1
        }
        break;
      }
      uVar1 = uVar1 + 1;
      piVar2 = piVar2 + 2; // each entry is 2 ints (key, value?)
    } while (uVar1 < *(uint *)(this + 0xf4));
  }
  if (local_8 != 0) {
    FUN_004daf90(&local_8); // likely free/delete the node
  }
  return;
}