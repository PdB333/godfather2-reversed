// FUNC_NAME: MoviePlayer::constructor

void __thiscall MoviePlayer::constructor(MoviePlayer *this)
{
  int *listPtr;
  uint hash;

  // Set up vtable pointers (likely two vtables for multiple inheritance)
  this->vtable1 = (void *)&PTR_FUN_00e35830;          // +0x00
  this->vtable2 = (void *)&PTR_LAB_00e35878;          // +0x04
  this->field_08 = 1;                                 // +0x08
  this->field_0C = 0;                                 // +0x0C
  this->field_10 = 0;                                 // +0x10
  this->field_14 = 0;                                 // +0x14

  // Call base class constructor (likely EventHandler or similar)
  FUN_004b1f30(this);

  // Initialize a field at large offset (e.g., movie playback flags)
  this->movieEndedFlag = 0;                           // +0x86C (0x21b * 4)

  // Insert this object into a global list (singleton list or object pool)
  listPtr = (int *)(DAT_01206880 + 0x14);             // global list head pointer offset
  *(void **)(*listPtr) = &PTR_LAB_011244ec;           // list entry vtable
  *listPtr = *listPtr + 4;                            // advance to next slot
  *(MoviePlayer **)(*listPtr) = this;
  *listPtr = *listPtr + 4;                            // advance past stored pointer

  // Insert this object into a hash table based on object address modulo some size
  hash = (uint)this % *(uint *)(*(int *)(DAT_01223398 + 4) + 8);
  FUN_00423cf0(&hashSlot1, &hashSlot2, hash);          // likely hash table insertion

  // Register event handlers for movie messages
  uVar2 = FUN_004dafd0("iMsgMovieEnded");              // hash string to ID
  FUN_00408260(&DAT_01218020, uVar2);                  // register with event manager

  uVar2 = FUN_004dafd0("iMsgMoviePlayerEnded");
  FUN_00408260(&DAT_01218028, uVar2);

  return;
}