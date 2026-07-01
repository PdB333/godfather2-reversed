// FUNC_NAME: Debug::logFormattedMessage
undefined4 Debug::logFormattedMessage(undefined4 *this, undefined4 formatStr, undefined4 arg3, undefined4 arg4)
{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined1 local_1014 [4112]; // buffer for formatted message
  undefined4 uStack_4;
  
  uStack_4 = 0x8bec5a;
  uVar2 = 0;
  if (*(char *)(DAT_01129904 + 0x3c) != '\0') { // check if logging is enabled (global flag at +0x3c)
    FUN_00604be0(); // enter critical section / lock
    FUN_008bea60(local_1014, formatStr, arg3); // format the message into buffer
    puVar1 = (undefined1 *)*this;
    if (puVar1 == (undefined1 *)0x0) {
      puVar1 = &DAT_0120546e; // default prefix string (e.g., "DEBUG")
    }
    FUN_006038a0(DAT_012234a4, local_1014, arg4, puVar1); // output to log system (file/console)
    FUN_00604c00(); // leave critical section / unlock
    uVar2 = 1;
  }
  return uVar2;
}