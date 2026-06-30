// FUNC_NAME: SomeClass::initResources
void SomeClass::initResources(void)
{
  int thisPtr; // in_EAX - this pointer
  int resource1; // uVar1
  int resource2; // uVar1

  // Initialize two resource handles with type 3
  FUN_0049c6e0(&DAT_00e40e50, 3); // Initialize resource handle 1
  FUN_0049c6e0(&DAT_00e40e58, 3); // Initialize resource handle 2

  // Load resources from the handles
  resource1 = FUN_004dafd0(&DAT_00e40e50); // Load resource 1
  *(int *)(thisPtr + 0x18) = resource1;    // Store at +0x18

  resource2 = FUN_004dafd0(&DAT_00e40e58); // Load resource 2
  *(int *)(thisPtr + 0x1c) = resource2;    // Store at +0x1c

  // If there's a global resource pointer, copy it to the object
  if (DAT_01206940 != 0) {
    FUN_00407e60(thisPtr + 8, &DAT_01206940); // Copy global resource to +0x08
  }
  return;
}