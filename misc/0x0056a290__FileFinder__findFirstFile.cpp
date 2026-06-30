// FUNC_NAME: FileFinder::findFirstFile
undefined4 __thiscall FileFinder::findFirstFile(int thisPtr, undefined4 path, undefined4 pattern, undefined4 param4, uint *outSize)
{
  HANDLE hFind;
  char searchPath [128];
  _WIN32_FIND_DATAA findData;
  
  _sprintf(searchPath,"%s:\\*%s",path,pattern);
  hFind = FindFirstFileA(searchPath,&findData);
  *(HANDLE *)(thisPtr + 0x344) = hFind;
  if (hFind != (HANDLE)0xffffffff) {
    *outSize = findData.nFileSizeLow + 0x1ff & 0xfffffe00;
    FUN_004d3d90(findData.cFileName);
    return 1;
  }
  return 0;
}