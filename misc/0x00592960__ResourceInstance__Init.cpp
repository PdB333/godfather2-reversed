// FUNC_NAME: ResourceInstance::Init
void __thiscall ResourceInstance::Init(void* pOwner, void* pData1, void* pData2)
{
  short sIndex;
  int* pTable;
  
  this->pOwner = pOwner;
  this->pData1 = pData1;
  this->pData2 = pData2;
  this->field_C = 0;
  
  // Fetch a pointer at offset 0x70 from the owner object (likely a table/array)
  pTable = *(int**)((char*)pOwner + 0x70);
  if (pTable == NULL)
  {
    this->pLookupResult = NULL;
    return;
  }
  
  // Check validity: pTable has count at +0x18 and data at +0x1c
  if ((*(int*)((char*)pTable + 0x18) > 0) && (*(void**)((char*)pTable + 0x1c) != NULL))
  {
    sIndex = *(short*)((char*)pOwner + 0x76);
    if ((sIndex >= 0) && (sIndex < *(int*)((char*)pTable + 0x18)))
    {
      // Each entry is 0x18 bytes
      this->pLookupResult = (void*)(*(char**)((char*)pTable + 0x1c) + sIndex * 0x18);
      return;
    }
  }
  this->pLookupResult = NULL;
}