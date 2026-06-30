// FUNC_NAME: SimNpc::destroyOrReset
void SimNpc::destroyOrReset(void)
{
  int this = in_EAX;
  undefined1 local_c[12];
  
  // Call some cleanup function (likely detach from world or remove references)
  FUN_005dffe0(local_c,this,*(undefined4 **)(this + 0x1c),this,
               *(undefined4 **)(this + 0x1c));
  
  // Release the object at offset 0x1c using vtable[1] (likely release or destruct)
  (**(code **)(**(int **)(this + 4) + 4))(*(undefined4 *)(this + 0x1c),0x18);
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  
  // If there's a component at offset 0x18, release it too (via vtable of offset 0x14)
  if (*(int *)(this + 0x18) != 0) {
    (**(code **)(**(int **)(this + 0x14) + 4))(*(int *)(this + 0x18),0);
    *(undefined4 *)(this + 0x18) = 0;
  }
  
  // Call destroy on the component at offset 0x14 (vtable[3])
  (**(code **)(**(int **)(this + 0x14) + 0xc))();
  
  // Delete self
  FUN_005df3e0();
  return;
}