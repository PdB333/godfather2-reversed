// FUNC_NAME: Sentient::getCurrentCoverNode
int __fastcall Sentient::getCurrentCoverNode(int thisPtr)
{
  int coverNodeIndex;
  
  if ((*(int *)(thisPtr + 0x74c) != 0) && (*(int *)(thisPtr + 0x74c) != 0x48)) {
    if (*(int *)(thisPtr + 0x74c) == 0) {
      coverNodeIndex = 0;
    }
    else {
      coverNodeIndex = *(int *)(thisPtr + 0x74c) + -0x48;
    }
    if ((*(char *)(coverNodeIndex + 0x1a8) == '\x01') && (*(int *)(thisPtr + 0x74c) != 0)) {
      return *(int *)(thisPtr + 0x74c) + -0x48;
    }
  }
  return 0;
}