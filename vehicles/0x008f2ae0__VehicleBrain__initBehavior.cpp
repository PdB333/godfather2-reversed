// FUNC_NAME: VehicleBrain::initBehavior
void __thiscall VehicleBrain::initBehavior(int someParam)
{
  int* newBehavior; // newly allocated behavior object
  char* stringPtr;  // string/name for debug or lookup
  char* tempStrPtr; // temporary string pointer
  int tempInt1;     // unused
  int tempInt2;     // unused
  void (*tempFunc)(); // function pointer, likely set by string lookup (decompiler missing assignment)

  // Store argument at offset +0x18 (likely a type or ID)
  *(int*)(this + 0x18) = someParam;

  tempStrPtr = 0;
  tempInt1 = 0;
  tempInt2 = 0;
  tempFunc = 0;

  // Check bit 3 of flags at +0x10 (0x10 = flags? maybe something like 'isActive' or 'isInCar')
  if ((*(unsigned int*)(this + 0x10) >> 3 & 1) == 0) {
    // Use hash 0xe5ea4d7f (some resource ID)
    stringLookup(0xe5ea4d7f, &tempStrPtr);
  } else {
    // Use hash 0xe3b3dcaf
    stringLookup(0xe3b3dcaf, &tempStrPtr);
    // Set bit 4 in flags
    *(unsigned int*)(this + 0x10) |= 0x10;
  }

  // Allocate memory for a new behavior object (size 0xF0 = 240 bytes)
  newBehavior = (int*)allocator(0xF0);
  if (newBehavior != 0) {
    newBehavior = (int*)initializeObject(0);
  }

  // Use resolved string, fallback to default DAT_0120546e if null
  stringPtr = tempStrPtr;
  if (tempStrPtr == 0) {
    stringPtr = &DAT_0120546e; // default string
  }
  // Likely debug print or assert with the string
  printStringOrAssert(stringPtr);

  // Initialize fields of the new behavior object
  *(int*)(newBehavior + 0xC) = 8;                        // +0x0C: state ID or type
  *(int*)(newBehavior + 0x20) = 0x510c352b;              // +0x20: magic constant/hash
  *(void**)(newBehavior + 0x14) = (void*)FUN_008f2250;   // +0x14: function pointer (maybe update)
  *(char**)(newBehavior + 0x18) = &LAB_008f1e40;         // +0x18: label/state pointer

  // Set some global state (1)
  setSomeGlobalState(1);

  // Link the new behavior to this object
  *(int*)(newBehavior + 0x10) = (int)this;               // +0x10: back pointer to owner

  // Possibly finalize initialization
  finalizeInit();

  // Enable or activate something (1)
  enableSomething(1);

  // If string was resolved, call the function pointer (likely a cleanup or callback)
  if (tempStrPtr != 0) {
    tempFunc(tempStrPtr); // tempFunc is actually set by stringLookup? (decompiler artifact)
  }

  return;
}