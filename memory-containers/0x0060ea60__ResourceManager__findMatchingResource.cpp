// FUNC_NAME: ResourceManager::findMatchingResource
undefined4 FUN_0060ea60(undefined4 *outResource, undefined4 *param_2, int *outType, undefined4 *outSize, char extraParam)
{
  int *piVar1;
  int iVar2;
  uint index;
  int iVar4;
  undefined4 *source;
  undefined4 *dest;
  int local_14;
  uint count;
  undefined4 local_c;
  
  *param_2 = 0;
  index = 0;
  local_14 = 0;
  count = 0;
  local_c = 0;
  if (g_ResourceTableBase != 0) {
    iVar4 = 0;
    do {
      if (*(int *)(iVar4 + (-(uint)(g_ResourceTableBase != 0) & g_ResourceTableSize)) == 0) {
        FUN_0060f7f0(&local_14, index * 0x10 + (-(uint)(g_ResourceTableBase != 0) & g_ResourceTableSize) + 4);
        index = 0;
        *outType = 1;
        *outSize = 0x54;
        if (count != 0) {
          piVar1 = (int *)(local_14 + 8);
          do {
            if (((piVar1[-1] == *outType) && (*piVar1 == 0x50)) && ((char)piVar1[1] == extraParam)) {
              iVar4 = index * 0x14c + local_14;
              *outResource = *(undefined4 *)(index * 0x14c + local_14);
              outResource[1] = *(undefined4 *)(iVar4 + 4);
              outResource[2] = *(undefined4 *)(iVar4 + 8);
              *(undefined1 *)(outResource + 3) = *(undefined1 *)(iVar4 + 0xc);
              source = (undefined4 *)(iVar4 + 0x10);
              dest = outResource + 4;
              for (iVar2 = 0x4c; iVar2 != 0; iVar2 = iVar2 + -1) {
                *dest = *source;
                source = source + 1;
                dest = dest + 1;
              }
              FUN_0060f680(outResource + 0x50, iVar4 + 0x140);
              FUN_0060f750(&local_14);
              return 1;
            }
            index = index + 1;
            piVar1 = piVar1 + 0x53;
          } while (index < count);
        }
        FUN_0060f750(&local_14);
        return 0;
      }
      index = index + 1;
      iVar4 = iVar4 + 0x10;
    } while (index < g_ResourceTableSize);
  }
  FUN_0060f750(&local_14);
  return 0;
}