// FUNC_NAME: GodfatherGameManager::destructor
void __fastcall GodfatherGameManager::~GodfatherGameManager(undefined4 *this)
{
  undefined1 local_8[8];
  
  *this = &PTR_FUN_00d80e0c; // vtable pointer
  FUN_008ec590(); // base destructor
  FUN_004086d0(&DAT_01206940); // cleanup some global
  FUN_00408310(&DAT_0112fdf0); // release resource
  FUN_00408310(&DAT_0112fe00); // release resource
  FUN_00408310(&DAT_0112fde8); // release resource
  FUN_00408310(&DAT_0112fdf8); // release resource
  FUN_00408310(&DAT_0112fddc); // release resource
  FUN_008eb7a0(); // cleanup
  FUN_008ee740(local_8, this + 0xe, *(undefined4 *)this[0xf], this + 0xe,
               (undefined4 *)this[0xf]); // destroy member at +0x38
  FUN_009c8eb0(this[0xf]); // free memory
  this[0xf] = 0;
  this[0x10] = 0;
  FUN_008ee5b0(local_8, this + 0xb, *(undefined4 *)this[0xc], this + 0xb,
               (undefined4 *)this[0xc]); // destroy member at +0x2C
  FUN_009c8eb0(this[0xc]); // free memory
  this[0xc] = 0;
  this[0xd] = 0;
  FUN_008ee5b0(local_8, this + 8, *(undefined4 *)this[9], this + 8, (undefined4 *)this[9]); // destroy member at +0x20
  FUN_009c8eb0(this[9]); // free memory
  this[9] = 0;
  this[10] = 0;
  FUN_008ee420(local_8, this + 3, *(undefined4 *)this[4], this + 3, (undefined4 *)this[4]); // destroy member at +0x0C
  FUN_009c8eb0(this[4]); // free memory
  this[4] = 0;
  this[5] = 0;
  FUN_004083d0(); // final cleanup
  return;
}