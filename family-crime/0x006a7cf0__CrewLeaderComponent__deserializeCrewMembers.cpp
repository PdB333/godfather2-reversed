// FUNC_NAME: CrewLeaderComponent::deserializeCrewMembers
void __thiscall CrewLeaderComponent::deserializeCrewMembers(int this, int dataStream)
{
  int slotIndex;
  char done;
  int tokenType;
  int memberPtr;
  int *memberArray;
  int localArray[26]; // used for linking

  deserializeBegin(dataStream);
  deserializeSetMagic(dataStream, 0xc5bdda89);
  done = deserializeIsDone();
  while (done == '\0') {
    deserializeAdvance();
    tokenType = deserializeGetType();
    switch(tokenType) {
    case 0: // member 0 (second array)
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x70) = *(int *)(memberPtr + 8);
      break;
    case 1: // slot index 0 (first array)
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x50) = *(int *)(memberPtr + 8);
      break;
    case 2: // member 1
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x74) = *(int *)(memberPtr + 8);
      break;
    case 3: // slot index 1
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x54) = *(int *)(memberPtr + 8);
      break;
    case 4: // member 2
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x78) = *(int *)(memberPtr + 8);
      break;
    case 5: // slot index 2
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x58) = *(int *)(memberPtr + 8);
      break;
    case 6: // member 3
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x7c) = *(int *)(memberPtr + 8);
      break;
    case 7: // slot index 3
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x5c) = *(int *)(memberPtr + 8);
      break;
    case 8: // member 4
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x80) = *(int *)(memberPtr + 8);
      break;
    case 9: // slot index 4
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x60) = *(int *)(memberPtr + 8);
      break;
    case 10: // member 5
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x84) = *(int *)(memberPtr + 8);
      break;
    case 11: // slot index 5
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x64) = *(int *)(memberPtr + 8);
      break;
    case 12: // member 6
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x88) = *(int *)(memberPtr + 8);
      break;
    case 13: // slot index 6
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x68) = *(int *)(memberPtr + 8);
      break;
    case 14: // member 7
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x8c) = *(int *)(memberPtr + 8);
      break;
    case 15: // slot index 7
      memberPtr = deserializeReadInt();
      *(int *)(this + 0x6c) = *(int *)(memberPtr + 8);
    }
    deserializeAdvance();
    done = deserializeIsDone();
  }
  // Link each non-zero member pointer with its slot index
  memberArray = (int *)(this + 0x70); // start of member array
  for (int i = 0; i < 8; i++) {
    int member = *memberArray;
    if (member != 0) {
      int slot = *(memberArray - 8); // corresponding slot index from first array
      linkCrewMember(localArray, &member);
      *(int *)(localArray[0] + 4) = slot;
    }
    memberArray++;
  }
  return;
}