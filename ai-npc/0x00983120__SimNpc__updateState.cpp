// FUNC_NAME: SimNpc::updateState
void __thiscall SimNpc::updateState(int *this, undefined4 param_2, int param_3, undefined1 param_4)
{
  FUN_004d3d90(param_2); // likely some base class update or state init
  this[0x23] = param_3; // +0x8C - some state timer or counter
  *(undefined1 *)((int)this + 0x91) = param_4; // +0x91 - flag byte (e.g., behavior flag)
  
  if (this[0x1f] == 0) { // +0x7C - check if some flag is zero (e.g., isDead or isInactive)
    if (((char)this[0x12] != '\0') && ((*(byte *)((int)this + 0x49) & 10) == 0)) {
      // +0x48 - some state byte, bit 1 (0x02) and bit 3 (0x08) mask = 0x0A
      // If not dead/inactive, and state is active, and certain bits not set, call idle/patrol update
      FUN_00982d40(); // SimNpc::updateIdleBehavior
    }
  }
  else {
    if ((char)this[0x12] == '\0') { // +0x48 - check if state is zero
      (**(code **)(*this + 0x28))(); // vtable call at offset 0x28 (likely virtual method, e.g., onStateExit)
      return;
    }
    if ((*(byte *)((int)this + 0x49) & 10) == 0) { // +0x49 - check same bitmask
      FUN_009821a0(); // SimNpc::updateCombatBehavior
      return;
    }
  }
  return;
}