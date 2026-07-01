// FUNC_NAME: GameSystem::constructor
void __thiscall GameSystem::constructor(GameSystem *this)
{
  // Set vtable pointer
  *this = (GameSystem *)&PTR_FUN_00d69c7c;
  
  // Set function pointers or data at offsets +0x3C, +0x48, +0x50
  *(void **)((char *)this + 0x3C) = (void *)&LAB_00d69c6c;
  *(void **)((char *)this + 0x48) = (void *)&LAB_00d69c68;
  *(void **)((char *)this + 0x50) = (void *)&LAB_00d69c50;
  
  // Initialize global singletons/reference counts
  FUN_004086d0(&DAT_0112db6c);  // Possibly register global object 1
  FUN_004086d0(&DAT_012069c4);  // Possibly register global object 2
  
  // Conditional secondary init (if offset +0x98 is non-zero)
  if (*(int *)((char *)this + 0x98) != 0) {
    FUN_0078f5f0();  // Likely cleanup or deferred initialization
  }
  
  // Finalize initialization (global function)
  FUN_0046c640();  // Probably global setup or transition
}