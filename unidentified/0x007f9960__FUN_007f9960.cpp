// FUNC_NAME: SomeClass::ensureComponentAllocated
void __fastcall ensureComponentAllocated(int thisPtr)
{
  undefined4 *vtablePtr;
  int componentPtr;
  undefined4 stackArgs[3]; // local stack for allocation parameters
  
  // Check if component at offset 0x110 is already allocated
  if (*(int *)(thisPtr + 0x110) == 0) {
    // Get allocator vtable
    vtablePtr = (undefined4 *)FUN_009c8f80();
    stackArgs[0] = 2;   // allocation type/flags
    stackArgs[1] = 0x10; // alignment
    stackArgs[2] = 0;    // additional flags
    
    // Allocate 0x70 bytes for the component
    componentPtr = (**(code **)*vtablePtr)(0x70, &stackArgs);
    if (componentPtr != 0) {
      // Initialize component fields (offsets 0x60-0x64)
      *(undefined1 *)(componentPtr + 0x60) = 0;  // +0x60: some flag/byte
      *(undefined1 *)(componentPtr + 0x61) = 0;  // +0x61: some flag/byte
      *(undefined1 *)(componentPtr + 0x62) = 0;  // +0x62: some flag/byte
      *(undefined1 *)(componentPtr + 99) = 0;    // +0x63: some flag/byte
      *(undefined1 *)(componentPtr + 100) = 1;   // +0x64: set to 1 (enabled/active)
      
      // Store component pointer at +0x110
      *(int *)(thisPtr + 0x110) = componentPtr;
      return;
    }
    // Allocation failed, clear pointer
    *(undefined4 *)(thisPtr + 0x110) = 0;
  }
  return;
}