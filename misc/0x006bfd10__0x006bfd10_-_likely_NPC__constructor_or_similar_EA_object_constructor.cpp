// FUNC_NAME: 0x006bfd10 - likely NPC::constructor or similar EA object constructor
undefined4 * __thiscall NPC::constructor(NPC *this, byte allocFlag)
{
  int *allocMem;
  
  // Set primary vtable pointer
  *this = &NPC_VTABLE; // PTR_FUN_00d5ee24
  // Set secondary vtable (possible interface)
  this->secondaryVtable = &SECONDARY_VTABLE; // PTR_LAB_00d5ee1c, offset 0x8
  
  // If sub-object at offset 0x9c (0x270) exists, clean it up
  if (this->someObject != NULL) // +0x9c (0x270)
  {
    // Destructor/cleanup for that embedded object
    cleanupEmbeddedObject(&this->someObject); // FUN_004daf90
  }
  
  // General initialization call (likely base class or manager)
  initializeSomething(); // FUN_006d6500
  
  // If the allocFlag's lowest bit is set, allocate a new object with vtable
  if ((allocFlag & 1) != 0)
  {
    allocMem = (int *)allocateMemory(); // FUN_009c8f80, returns pointer to raw memory
    // Call virtual function at index 1 (offset 4) on the newly allocated object
    // using this as param and size 0x280
    (*(code **)(*allocMem + 4))(this, 0x280);
  }
  
  return this;
}