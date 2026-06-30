// FUNC_NAME: NetSession::NetSession
void __thiscall NetSession::NetSession(NetSession *this)
{
  int *pMagic; // pointer to magic number at offset 0x2670
  int size;    // computed size for allocation
  int iVar1;

  // Set primary vtable pointer (base class)
  *(undefined4 *)this = PTR_FUN_00d626d8;

  // Set vtable pointers for multiple inheritance interfaces
  *(undefined4 *)(this + 0x3C) = PTR_LAB_00d626c8; // interface A
  *(undefined4 *)(this + 0x48) = PTR_LAB_00d626c4; // interface B
  *(undefined4 *)(this + 0x50) = PTR_LAB_00d626c0; // interface C
  *(undefined4 *)(this + 0x54) = PTR_LAB_00d62660; // interface D
  *(undefined4 *)(this + 0x58) = PTR_LAB_00d625f8; // interface E
  *(undefined4 *)(this + 0x390) = PTR_LAB_00d625d8; // interface F
  *(undefined4 *)(this + 0x394) = PTR_FUN_00d625c4; // function pointer (probably vtable entry)
  *(undefined4 *)(this + 0x3A0) = PTR_FUN_00d625bc; // function pointer
  *(undefined4 *)(this + 0x1F30) = PTR_LAB_00d625b4; // another vtable

  // pMagic points to magic number at offset 0x2670 from this
  pMagic = (int *)(this + 0x2670);

  // If magic is non-zero and not 0x48 (72), adjust and allocate
  if ((*pMagic != 0) && (*pMagic != 0x48))
  {
    if (*pMagic == 0)
    {
      size = 0;
    }
    else
    {
      size = *pMagic - 0x48;
    }
    operator new(size + 0x3C); // allocate memory (size+60 bytes)
  }

  // Initialize global data structures (e.g., memory pools, subsystems)
  sub_004086d0(&DAT_0112ad8c); // likely memset or init
  sub_00408310(&DAT_0112ad8c); // cleanup or reset
  sub_00408310(&DAT_0112ad84); // another global
  sub_004086d0(&DAT_0112ad7c); // init again

  // Initialize some network subsystem
  sub_00732300();

  // Register this object with a manager (type 9)
  sub_008f67c0(9, this);

  // Free the old allocation if magic was set
  if (*pMagic != 0)
  {
    operator delete(pMagic);
  }

  // Set final vtable pointer after cleanup
  *(undefined4 *)(this + 0x26A0) = PTR_LAB_00d60cdc;

  // Post-initialization step
  sub_00735560();
}