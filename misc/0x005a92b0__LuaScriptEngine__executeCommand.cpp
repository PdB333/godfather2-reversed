// FUNC_NAME: LuaScriptEngine::executeCommand
void __thiscall LuaScriptEngine::executeCommand(uint *this, undefined4 param_2)
{
  undefined4 uVar1;
  int iVar2;
  undefined1 *local_9c;
  undefined1 local_98 [16];
  char local_88 [132];
  
  // Check if this is a "native function" call (bit 15 set indicates native function)
  if ((~(byte)(*this >> 0xf) & 1) == 0) {
    // Dispatch based on command type (lower 15 bits)
    switch(*this & 0x7fff) {
    case 1: // Execute script string
      FUN_005aa9d0(param_2);
      return;
    default: // Unknown command - log error and continue
      FUN_005a7760(param_2);
      FUN_005ae350();
      break;
    case 5: // Execute script file
      FUN_005aa9d0(param_2);
      return;
    case 6: // Get string from buffer (0x80 max)
      FUN_0059fd60(this[1],local_88,0x80);
      FUN_005aa9d0(param_2);
      return;
    case 7: // Get string from buffer (0x80 max)
      FUN_0059fc50(this[1],local_88,0x80);
      FUN_005aa9d0(param_2);
      return;
    case 9: // Get native function address
      iVar2 = FUN_005a7620();
      _sprintf(local_88,"[native function 0x%08x]",*(undefined4 *)(iVar2 + 0x4c));
      FUN_005aa9d0(param_2);
      return;
    case 10: // Execute script string (alternate)
      FUN_005aa9d0(param_2);
      return;
    case 0x15: // Execute script string (alternate)
      FUN_005aa9d0(param_2);
      return;
    case 0x16: // Get and execute native function
      uVar1 = FUN_005a7810();
      FUN_005ab680(uVar1,param_2);
      return;
    case 0x1a: // Execute script string (alternate)
      FUN_005aa9d0(param_2);
      return;
    case 0x1b: // Execute script string (alternate)
      FUN_005aa9d0(param_2);
      return;
    case 0x1e: // Execute script string (alternate)
      FUN_005aa9d0(param_2);
      return;
    }
  }
  else {
    // Native function call - execute the native function
    FUN_005a0980();
    FUN_005a1060();
    // Clean up temporary buffer if allocated
    if ((local_9c != local_98) && (local_9c != (undefined1 *)0x0)) {
      (*DAT_0119caf4)(local_9c);
      return;
    }
  }
  return;
}