// FUNC_NAME: EngineObject::getRefCount
int __fastcall EngineObject::getRefCount(int* pObject)
{
  // Check if the object is a valid, non-null sentinel.
  // The object struct: +0x00 to +0x0C is a quad-word identifier,
  // +0x10 is a reference count.
  // Null sentinel is either all zeros or the specific magic pattern:
  //   0xBABDBDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
  const int kNullPart0 = -0x45245246; // 0xBABDBDBA
  const int kNullPart1 = -0x41104111; // 0xBEEFBEEF
  const int kNullPart2 = -0x153EA5AB; // 0xEAC15A55
  const int kNullPart3 = -0x6EEFF6EF; // 0x91100911

  int result = 0;

  // Skip if the identifier is all zeros or matches the null sentinel
  if ( (pObject[0] != 0 || pObject[1] != 0 || pObject[2] != 0 || pObject[3] != 0) &&
       !(pObject[0] == kNullPart0 && pObject[1] == kNullPart1 &&
         pObject[2] == kNullPart2 && pObject[3] == kNullPart3) )
  {
    // If the reference count is zero, initialize the object
    if (pObject[4] == 0)
    {
      int initResult = ::initializeObject(pObject);  // FUN_0044ede0
      ::setObjectInitialized(initResult);            // FUN_004ab5c0
    }
    result = pObject[4];  // Return the reference count (may have been set by init)
  }
  return result;
}