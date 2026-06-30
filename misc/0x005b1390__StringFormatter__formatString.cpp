// FUNC_NAME: StringFormatter::formatString
void StringFormatter::formatString(int *this)
{
  char c;
  char *src;
  undefined1 **ppuVar3;
  char local_54;
  undefined1 local_53 [3];
  char local_50;
  undefined1 local_4f [3];
  undefined1 *local_4c;
  char *local_48;
  undefined1 *local_44;
  int local_40 [2];
  undefined8 *local_38;
  undefined8 local_34;
  undefined8 local_2c;
  undefined1 *local_1c;
  undefined1 local_18 [20];
  
  // Initialize output buffer state
  local_40[0] = 0;
  local_40[1] = 0;
  local_38 = &local_34;
  local_34 = 0;
  local_2c = 0;
  
  // Allocate temporary buffer (0x7800 = 30720 bytes)
  FUN_005ab320(0x7800);
  
  // Iterate through format string characters
  // param_1[2] points to format string start, *param_1 is length
  src = (char *)this[2];
  if (src != src + *this) {
    do {
      c = *src;
      if (c == '+') {
        // Handle '+' as space character
        local_44 = (undefined1 *)(local_40[0] + (int)local_38);
        local_4c = local_53;
        ppuVar3 = &local_4c;
        local_54 = ' ';
LAB_005b14a0:
        local_48 = &local_54;
        FUN_005aba20(&local_48,ppuVar3);
      }
      else {
        if (c != '%') {
          // Regular character - copy to output
          local_4c = (undefined1 *)(local_40[0] + (int)local_38);
          local_44 = local_53;
          ppuVar3 = &local_44;
          local_54 = c;
          goto LAB_005b14a0;
        }
        // Handle format specifier: decode next two characters
        local_50 = FUN_005b12b0(src[1],src[2]);
        local_4c = (undefined1 *)(local_40[0] + (int)local_38);
        local_44 = local_4f;
        local_48 = &local_50;
        FUN_005aba20(&local_48,&local_44);
        src = src + 2;
      }
      src = src + 1;
    } while (src != (char *)(*this + this[2]));
  }
  
  // Finalize output
  FUN_005a0a00(local_40);
  FUN_005a1060();
  
  // Free temporary buffers if they were allocated
  if ((local_1c != local_18) && (local_1c != (undefined1 *)0x0)) {
    (*DAT_0119caf4)(local_1c);
  }
  if ((local_38 != &local_34) && (local_38 != (undefined8 *)0x0)) {
    (*DAT_0119caf4)(local_38);
  }
  return;
}