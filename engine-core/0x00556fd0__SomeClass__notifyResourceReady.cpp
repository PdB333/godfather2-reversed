// FUNC_NAME: SomeClass::notifyResourceReady
void __thiscall SomeClass::notifyResourceReady(void) {
  int local_4 = 0;
  // Call virtual function at vtable+0x10 on the object at this+0x44 (likely a resource manager)
  // with a CRC32 hash (0xae986323) and pointer to local_4.
  char result = (**(char (__thiscall**)(uint, int*))(**(int**)(this + 0x44) + 0x10))(0xae986323, &local_4);
  
  if (result != 0 && unaff_ESI != nullptr) {
    int* vtable = *unaff_ESI; // unaff_ESI is probably a member or parameter passed via ESI
    uint uVar3 = FUN_005565f0(); // some utility function returning a value
    // Call virtual function at vtable+0x98 on the object pointed by unaff_ESI,
    // passing this+0x48 as first argument and uVar3 as second.
    (**(void (__thiscall**)(int, uint))(vtable + 0x98))(this + 0x48, uVar3);
  }
}