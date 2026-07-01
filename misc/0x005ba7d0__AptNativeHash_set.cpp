// Xbox PDB: AptNativeHash::set
// FUNC_NAME: AptNativeHash::setValue
void AptNativeHash::setValue(byte *this, int key, int value)
{
  int *entry;
  code *handler;
  uint hash;
  uint index;
  int cmpResult;
  int *bucket;
  uint uVar7;
  int fsOffset;
  char *msg;
  char *file;
  undefined4 line;
  int severity;
  undefined1 *assertFlag;
  
  if (key == 0) {
    msg = "pKey";
    file = "..\\source\\Apt\\AptNativeHash.cpp";
    line = 0x73;
    severity = 2;
    assertFlag = &DAT_0112915e;
    if (DAT_0112915e != '\0') {
      bucket = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
      hash = 1;
      if (((bucket == (int *)0x0) ||
          (hash = (**(code **)(*bucket + 8))(&msg,&DAT_00e3de3c), assertFlag != (undefined1 *)0x0
          )) && ((hash & 2) != 0)) {
        *assertFlag = 0;
      }
      if (((bucket != (int *)0x0) || (severity != 4)) &&
         (((hash & 1) != 0 || ((severity == 0 || (severity == 1)))))) {
        handler = (code *)swi(3);
        (*handler)();
        return;
      }
    }
  }
  if (value == 0) {
    FUN_005bad80(this);
    return;
  }
  hash = FUN_005ba580();
  index = (1 << (*this & 0x1f)) - 1U & hash;
  if (*(short *)(this + 2) != 0) {
    for (bucket = *(int **)(*(int *)(this + 4) + index * 4); bucket != (int *)0x0;
        bucket = (int *)bucket[2]) {
      if (*bucket == 0) {
        msg = "pEntry->pKey";
        file = "..\\source\\Apt\\AptNativeHash.cpp";
        line = 0x7f;
        severity = 2;
        assertFlag = &DAT_0112915f;
        if (DAT_0112915f != '\0') {
          entry = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
          uVar7 = 1;
          if (((entry == (int *)0x0) ||
              (uVar7 = (**(code **)(*entry + 8))(&msg,"pEntry->pKey"),
              assertFlag != (undefined1 *)0x0)) && ((uVar7 & 2) != 0)) {
            *assertFlag = 0;
          }
          if (((entry != (int *)0x0) || (severity != 4)) &&
             (((uVar7 & 1) != 0 || ((severity == 0 || (severity == 1)))))) {
            handler = (code *)swi(3);
            (*handler)();
            return;
          }
        }
      }
      cmpResult = *bucket;
      if ((cmpResult == key) ||
         (((bucket[3] == hash && (*(int *)(cmpResult + 4) == *(int *)(key + 4))) &&
          (cmpResult = __stricmp(*(char **)(cmpResult + 0xc),*(char **)(key + 0xc)), cmpResult == 0)))) {
        if (bucket[1] == 0) {
          msg = "pEntry->pValue";
          file = "..\\source\\Apt\\AptNativeHash.cpp";
          line = 0x83;
          severity = 2;
          assertFlag = &DAT_01129160;
          FUN_0059bf00();
        }
        if (bucket[1] == value) {
          return;
        }
        FUN_0059c690();
        (**(code **)(&DAT_0103aee0 + (*(uint *)bucket[1] & 0x7fff) * 4))((uint *)bucket[1]);
        bucket[1] = value;
        return;
      }
    }
  }
  entry = (int *)(*DAT_0119caf0)(0x10,0);
  if (entry == (int *)0x0) {
    msg = "pEntry";
    file = "..\\source\\Apt\\AptNativeHash.cpp";
    line = 0x93;
    severity = 2;
    assertFlag = &DAT_01129161;
    FUN_0059bf00();
  }
  entry[3] = hash;
  FUN_0059c690();
  FUN_0059c690();
  *entry = key;
  entry[1] = value;
  entry[2] = *(int *)(*(int *)(this + 4) + index * 4);
  *(int **)(*(int *)(this + 4) + index * 4) = entry;
  *(short *)(this + 2) = *(short *)(this + 2) + 1;
  return;
}