// FUNC_NAME: SomeClass::clearStateFlags
void __thiscall clearStateFlags(int this, uint flags)
{
  // Clear the specified flags from the state bitfield at +0x88
  *(uint *)(this + 0x88) = *(uint *)(this + 0x88) & ~flags;
  
  // If current state is 4 (e.g., STATE_LOADING or STATE_ACTIVE) and no flags remain set
  if ((*(int *)(this + 0x84) == 4) && (*(uint *)(this + 0x88) == 0)) {
    // Call a virtual function on the callback object at +0x98 (likely a completion handler)
    if (*(int **)(this + 0x98) != (int *)0x0) {
      (**(code **)(**(int **)(this + 0x98) + 0xc))();
    }
    // Transition state to 3 (e.g., STATE_IDLE or STATE_COMPLETE)
    *(int *)(this + 0x84) = 3;
  }
}