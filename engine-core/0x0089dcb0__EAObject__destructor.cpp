// FUNC_NAME: EAObject::destructor
void __fastcall EAObject::~EAObject(undefined4 *this)
{
  int *refCount;
  int *ptr;
  undefined4 *next;
  undefined4 *curr;

  refCount = (int *)this[8];
  *this = &PTR_FUN_00d78694; // vtable for base class
  ptr = refCount + 1;
  *ptr = *ptr + -1; // decrement ref count
  if (*ptr == 0) {
    (**(code **)(*refCount + 4))(); // call destructor on ref counted object
  }
  refCount = (int *)this[6];
  ptr = refCount + 1;
  *ptr = *ptr + -1; // decrement another ref count
  if (*ptr == 0) {
    (**(code **)(*refCount + 4))(); // call destructor on another ref counted object
  }
  ptr = (int *)(this + 4);
  if (*ptr != 0) {
    FUN_004df600(); // likely free or release function
  }
  if (this[5] != 0) {
    *(undefined4 *)(this[5] + 8) = 0; // clear pointer
    this[5] = 0;
  }
  if (*ptr != 0) {
    *(undefined4 *)(*ptr + 8) = 0; // clear pointer
    *ptr = 0;
  }
  if (this[2] != 0) {
    FUN_004daf90(this + 2); // likely free or release function
  }
  *this = &PTR_FUN_00e32808; // vtable for derived class
  curr = (undefined4 *)this[1];
  while (curr != (undefined4 *)0x0) {
    next = (undefined4 *)curr[1];
    curr[1] = 0;
    *curr = 0;
    curr = next;
  }
  return;
}