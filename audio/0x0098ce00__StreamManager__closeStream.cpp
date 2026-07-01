// FUNC_NAME: StreamManager::closeStream
void __thiscall StreamManager::closeStream(int *this, char param_2)

{
  int aiStack_10 [3];
  code *pcStack_4;
  
  if ((char)this[0x18] != '\0') {
    (**(code **)(*this + 0xc))();  // virtual call - likely stop/prepare for close
    (**(code **)(*this + 4))();    // virtual call - likely release/cleanup
    if (this[0x17] != 0) {
      if (param_2 == '\0') {
        aiStack_10[0] = 0;
        aiStack_10[2] = 0;
        aiStack_10[1] = 0;
        FUN_0098b880(this[0x48],aiStack_10);  // get stream position
        FUN_0098a150(aiStack_10);             // seek to position
        if (aiStack_10[0] != 0) {
          (*pcStack_4)(aiStack_10[0]);        // callback with position
        }
      }
      else {
        FUN_0098cdc0(this[0x48],this[0x17] + 0x18);  // skip to end of stream
      }
      FUN_0098a480(0);  // flush/close
      FUN_0098b950();   // cleanup
      if ((undefined4 *)this[0x17] != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)this[0x17])(1);  // notify completion
      }
      this[0x17] = 0;  // +0x5C - clear stream handle
    }
  }
  *(undefined1 *)(this + 0x18) = 0;  // +0x60 - clear active flag
  this[0x48] = 0;                    // +0x120 - clear buffer pointer
  *(undefined1 *)(this + 0x50) = 0;  // +0x140 - clear another flag
  return;
}