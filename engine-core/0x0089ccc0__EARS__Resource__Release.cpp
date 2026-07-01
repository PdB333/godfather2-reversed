// FUNC_NAME: EARS::Resource::Release
void EARS::Resource::Release(int *pResource)
{
  if (*pResource != 0) {
    FUN_004daf90(pResource);  // likely frees the resource handle/object
    *pResource = 0;           // null out the pointer to avoid double free
  }
  pResource[2] = 0;           // set count/state at offset +0x08 to zero
}