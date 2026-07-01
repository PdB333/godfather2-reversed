// FUNC_NAME: Player::destructor
void __fastcall Player::~Player(int *this)
{
  int iVar1;
  
  *this = (int)&PTR_FUN_00d75eb0;
  this[0xf] = (int)&PTR_LAB_00d75e9c;
  this[0x12] = (int)&PTR_LAB_00d75e98;
  FUN_008f67c0(0x11,this); // Release reference count
  FUN_004086d0(&DAT_0120e93c); // Unregister from some manager
  FUN_004086d0(&DAT_0112e12c);
  FUN_004086d0(&DAT_0112e13c);
  if ((((((*(byte *)(this + 0x32) >> 5 & 1) != 0) && (this[0x14] != 0)) &&
       (this[0x14] != 0x48)) && ((iVar1 = this[0x14], iVar1 != 0 && (iVar1 != 0x48)))) &&
     ((*(uint *)(iVar1 + 0xc40) >> 0x15 & 1) != 0)) {
    *(uint *)(DAT_0112af68 + 0x170) = *(uint *)(DAT_0112af68 + 0x170) & 0xffffff7f; // Clear bit 7
  }
  if (this[0x1b] != 0) {
    if ((this[0x14] != 0) && (this[0x14] != 0x48)) {
      (**(code **)(*this + 0x1c))(0); // Call virtual destructor on component
    }
    if ((undefined4 *)this[0x1b] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)this[0x1b])(1); // Release component
    }
    this[0x1b] = 0;
  }
  if (this[0x1c] != 0) {
    FUN_004daf90(this + 0x1c); // Release smart pointer
  }
  if (this[0x14] != 0) {
    FUN_004daf90(this + 0x14); // Release smart pointer
  }
  this[0xf] = (int)&PTR_LAB_00d75e4c;
  *this = (int)&PTR_FUN_00d75e5c;
  this[0x12] = (int)&PTR_LAB_00d75e48;
  FUN_0046c640(); // Base class destructor
  return;
}