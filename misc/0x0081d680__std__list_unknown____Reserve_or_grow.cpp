// FUNC_NAME: std::list<unknown>::_Reserve_or_grow
void __thiscall std_list_ReserveOrGrow(int this, uint count)
{
  // +0x1c: current size of list (number of elements)
  // This function checks if adding 'count' elements would exceed max_size (0x71C71C7)
  // and throws if so, otherwise increments size.
  
  if (count <= 0x71C71C7U - *(int *)(this + 0x1c)) {
    *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + count;
    return;
  }
  
  // Overflow: throw "list<T> too long" exception
  uint local_28 = 0xf;
  uint local_2c = 0;
  uint local_3c = local_3c & 0xffffff00;
  FUN_0043f9f0("list<T> too long", 0x10);
  char *local_20 = "unknown";
  undefined **local_24 = &PTR_FUN_00da9810;
  uint local_4 = 0xf;
  uint local_8 = 0;
  uint local_18 = local_18 & 0xffffff00;
  FUN_0043eeb0(local_40, 0, 0xffffffff);
  local_24 = &PTR_FUN_00da9828;
  if (DAT_0113d3a0 != (code *)0x0) {
    (*DAT_0113d3a0)(&local_24);
  }
  (*(code *)local_24[2])();
  std::_Throw((exception *)&local_24);
  local_24 = &PTR_FUN_00da9810;
  if (0xf < local_4) {
    FUN_009c8eb0(local_18);
  }
  local_8 = 0;
  local_18 = local_18 & 0xffffff00;
  local_4 = 0xf;
  local_24 = &PTR_LAB_00e31044;
  if (0xf < local_28) {
    FUN_009c8eb0(local_3c);
    *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + count;
    return;
  }
  *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + count;
  return;
}