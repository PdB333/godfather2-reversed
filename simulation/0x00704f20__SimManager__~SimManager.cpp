// FUNC_NAME: SimManager::~SimManager

void __fastcall SimManager::~SimManager(undefined4 *this)
{
  int i;
  undefined4 *pSubObj;

  // Set vtable pointers for this and base destructor
  *this = &PTR_FUN_00d6105c;
  this[3] = &PTR_LAB_00d6104c;            // base destructor vtable?

  // Cleanup global data (likely singletons or pools)
  FUN_004086d0(&DAT_012069c4);
  FUN_004086d0(&DAT_0112ab34);
  FUN_00408310(&DAT_0112ab34);

  // Release a registered object by hash (e.g., a string key)
  // Hash: 0x5beea32a
  i = FUN_00463a80(0x5beea32a, &this);     // look up handler?
  if ((i != 0) && (*(char *)((int)this + 0x145) != '\0'))
  {
    *(undefined1 *)((int)this + 0x145) = 0;  // clear flag
    FUN_004639e0(0x5beea32a);                // unregister
  }

  // Free child object at offset 0x50 (slot 0x140)
  if (this[0x50] != 0)
  {
    FUN_009c8f10(this[0x50]);   // destruct
    this[0x50] = 0;
    this[0x4f] = 0;              // sibling count or similar
  }

  // Destroy two sub-controllers (offsets 0x108 and 0x100)
  if (this[0x42] != 0)
  {
    FUN_004daf90(this + 0x42);   // likely destructor
  }
  if (this[0x40] != 0)
  {
    FUN_004daf90(this + 0x40);
  }

  // Destroy array of 11 sub-objects (e.g., AI controllers, jobs, etc.)
  i = 10;
  pSubObj = this + 0x3c;         // start of array element 0
  do
  {
    pSubObj[-5] = &PTR_FUN_00d6102c;    // set vtable for sub-object
    if (pSubObj[-4] != 0)
    {
      FUN_004daf90(pSubObj + -4);       // destruct sub-object
    }
    i--;
    pSubObj = pSubObj + -5;             // move to next element in reverse
  } while (i >= 0);

  // Finalize: set vtable for base object and call base destructor
  this[3] = &PTR_LAB_00e30fe0;
  FUN_004083d0();                        // base class cleanup
  return;
}