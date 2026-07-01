// FUNC_NAME: PlayerSM::destructor
void __fastcall PlayerSM::~PlayerSM(undefined4 *this)
{
  int *piVar1;
  undefined4 uVar2;
  
  *this = &PTR_LAB_00d6fe74; // vtable for PlayerSM
  if (this[0x16] != 0) { // +0x58 - m_pPlayer
    FUN_007f6420(0x11); // stopSound(0x11)
    FUN_007f6420(0xb);  // stopSound(0xb)
    FUN_007f6420(0x2d); // stopSound(0x2d)
    *(uint *)(this[0x16] + 0x1b94) = *(uint *)(this[0x16] + 0x1b94) & 0xfffffff1; // clear some flags on player
    piVar1 = (int *)this[0x16]; // m_pPlayer
    if (((uint)piVar1[0x238] >> 1 & 1) == 0) { // check some flag
      if ((char)piVar1[0x6e3] != '\0') { // check another flag
        uVar2 = 0;
        goto LAB_007ead30;
      }
    }
    else {
      uVar2 = 4;
LAB_007ead30:
      (**(code **)(*piVar1 + 0x234))(uVar2,1); // call some method on player
    }
    piVar1 = (int *)FUN_007ab150(); // get some manager
    (**(code **)(*piVar1 + 4))(this[0x1f]); // release resource at +0x7C
    piVar1 = (int *)FUN_007ab130(); // get another manager
    (**(code **)(*piVar1 + 4))(this[0x1d]); // release resource at +0x74
    FUN_007ab260(DAT_01205224 + 400); // some cleanup
  }
  *this = &PTR_LAB_00d6b95c; // vtable for base class
  FUN_0080ea60(); // base destructor
  return;
}