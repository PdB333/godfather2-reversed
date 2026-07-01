// FUNC_NAME: StreamManager::constructor
undefined4 * __fastcall StreamManager::constructor(undefined4 *this)

{
  *this = &PTR_LAB_00d77114;
  DAT_01129824 = this;
  FUN_0049c610();
  this[3] = &PTR_FUN_00e2f19c;
  this[4] = 1;
  this[5] = 0;
  *this = &PTR_FUN_00d77134;
  this[1] = &PTR_LAB_00d77128;
  this[3] = &PTR_LAB_00d77118;
  this[0x1f] = 0;   // +0x7C - some stream state flag
  this[0x52] = 0;   // +0x148 - another state flag
  this[0x85] = 0;   // +0x214 - yet another state flag
  FUN_0049c6e0(&PTR_LAB_00d770b8,1);
  FUN_0042b480(0,0x40);   // allocate 0x40 bytes for stream type 0
  FUN_0042b480(1,0x80);   // allocate 0x80 bytes for stream type 1
  FUN_0042b570(0x3c);     // set some buffer size to 0x3C
  FUN_0042b3f0(&LAB_0088ced0);  // register callback function
  FUN_0042b420(&LAB_0088cf00);  // register another callback
  FUN_0042b440(0x200);    // set some limit to 0x200
  FUN_0042b430(0x400);    // set another limit to 0x400
  FUN_0088cf50();         // initialize stream manager internals
  if (DAT_01206940 != 0) {
    FUN_00408900(this + 3,&DAT_01206940,0x8000);  // copy 0x8000 bytes from global data
  }
  FUN_004086b0(&DAT_01206a20,0xfffe);  // initialize another buffer with 0xFFFE size
  return this;
}