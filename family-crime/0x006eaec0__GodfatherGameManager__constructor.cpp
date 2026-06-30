// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
  // Set vtable pointer (offset +0x0)
  *(int**)this = &VTABLE_GodfatherGameManager; // 0x00d5fe00

  // Set function table pointer at offset +0x3C
  *(int**)((char*)this + 0x3C) = &LABEL_00d5fdf0;

  // Set function table pointer at offset +0x48
  *(int**)((char*)this + 0x48) = &LABEL_00d5fdec;

  // Call base class constructor at offset +0x50 (likely GameManager base)
  GameManager::constructor((GameManager*)((char*)this + 0x50));

  // Initialize base subobject further
  GameManager::init((GameManager*)((char*)this + 0x50));

  // Global/static initialization
  FUN_0046c640(); // Possibly Singleton::initialize or similar
  return;
}