// FUNC_NAME: EARSString::split
undefined1 __thiscall EARSString::split(uint *this, char *delimiter, uint *firstPart, uint *secondPart)
{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  undefined1 uVar4;
  uint uVar5;
  undefined1 result;
  int local_10;
  code *local_4;
  
  result = 0;
  // Avoid self-assignment: if this == firstPart or this == secondPart, fall through to the self-assignment handler
  if ((this != firstPart) && (this != secondPart)) {
    // Clear firstPart
    if (*firstPart != 0) {
      (*(code *)firstPart[3])(*firstPart);  // free? destructor?
    }
    *firstPart = 0;
    firstPart[2] = 0;
    firstPart[1] = 0;
    // Clear secondPart
    if (*secondPart != 0) {
      (*(code *)secondPart[3])(*secondPart);
    }
    *secondPart = 0;
    secondPart[2] = 0;
    secondPart[1] = 0;
    // If the string has a length
    if (this[1] != 0) {
      uVar3 = *this;
      uVar5 = FUN_004d4e20(uVar3);  // find delimiter position? returns index
      if (uVar5 != 0) {
        if (uVar3 < uVar5) {
          FUN_004d3f10(uVar3,0,uVar5 - uVar3);  // memcpy? copy first part
        }
        pcVar1 = delimiter + 1;
        do {
          cVar2 = *delimiter;
          delimiter = delimiter + 1;
        } while (cVar2 != '\0');
        delimiter = delimiter + (uVar5 - (int)pcVar1);
        if (*delimiter != '\0') {
          FUN_004d3f10(delimiter,0,(this[1] - (int)delimiter) + *this);  // copy second part
        }
        result = 1;
      }
    }
    return result;
  }
  // Self-assignment case: perform split via a temporary
  FUN_004d3b50(this);  // copy to temporary?
  uVar4 = EARSString::split(delimiter, firstPart, secondPart);  // recursive call with this swapped? This is likely a bug or tricky pattern
  if (local_10 != 0) {
    (*local_4)(local_10);
  }
  return uVar4;
}