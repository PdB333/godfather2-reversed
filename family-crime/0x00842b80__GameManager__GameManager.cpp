// FUNC_NAME: GameManager::GameManager
// Address: 0x00842b80
// Role: Constructor for GameManager class, initializes dual vtable and 7 member objects

void * __thiscall GameManager::GameManager(GameManager *this)
{
  // Set base class vtable pointer (likely first base)
  *this = &PTR_LAB_00d74620;
  // Set second vtable pointer (likely second base or additional interface)
  *(int *)((char *)this + 4) = &PTR_LAB_00d748f8;

  // Construct 7 member objects (e.g., array of sub-managers)
  // Each call is a constructor for a member object at a fixed offset
  FUN_005953b0((int)this + 8);   // member1
  FUN_005953b0((int)this + 12);  // member2 (size assumed 4)
  FUN_005953b0((int)this + 16);
  FUN_005953b0((int)this + 20);
  FUN_005953b0((int)this + 24);
  FUN_005953b0((int)this + 28);
  FUN_005953b0((int)this + 32);

  // Override vtable for final class (derived or specialized)
  *this = &PTR_FUN_00d749d0;
  *(int *)((char *)this + 4) = &PTR_LAB_00d74980;

  return this;
}