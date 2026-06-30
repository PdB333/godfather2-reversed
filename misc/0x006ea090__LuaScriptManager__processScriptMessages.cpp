// FUNC_NAME: LuaScriptManager::processScriptMessages
void __thiscall LuaScriptManager::processScriptMessages(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  
  FUN_0046c710(param_2); // likely luaL_loadstring or similar
  FUN_0043aff0(param_2,0xa21309a3); // likely lua_pcall with hash
  cVar1 = FUN_0043b120(); // check if lua stack has values
  do {
    if (cVar1 != '\0') {
      puVar4 = (undefined4 *)FUN_0043ab10(); // pop table from lua stack
      *(undefined4 *)(this + 0x50) = *puVar4; // +0x50: scriptResult.x
      *(undefined4 *)(this + 0x54) = puVar4[1]; // +0x54: scriptResult.y
      *(undefined4 *)(this + 0x58) = puVar4[2]; // +0x58: scriptResult.z
      *(undefined4 *)(this + 0x5c) = puVar4[3]; // +0x5c: scriptResult.w
      return;
    }
    FUN_0043b210(); // get next message type
    uVar2 = FUN_0043ab70(); // get message ID
    switch(uVar2) {
    case 0:
      FUN_0043b210(); // get message data
      uVar2 = FUN_0043ab90(); // get string parameter
      FUN_004d3d90(uVar2); // process string message
      break;
    case 1:
      FUN_0043b210(); // get message data
      uVar2 = FUN_0043ab90(); // get string parameter
      FUN_00408980(this + 0x70,uVar2); // +0x70: scriptCallback, set callback function
      break;
    case 2:
      FUN_0043b210(); // get message data
      uVar2 = FUN_0043ab90(); // get string parameter
      FUN_004d9500(uVar2); // process numeric message
      if (local_74 == -0x45245246) { // 0xBABDBABA
        if (((local_70 != -0x41104111) || (local_6c != -0x153ea5ab)) || (local_68 != -0x6eeff6ef)) {
LAB_006ea17d:
          *(int *)(this + 0x78) = local_74; // +0x78: scriptIntResult1
          *(int *)(this + 0x7c) = local_70; // +0x7c: scriptIntResult2
          *(int *)(this + 0x80) = local_6c; // +0x80: scriptIntResult3
          *(int *)(this + 0x84) = local_68; // +0x84: scriptIntResult4
        }
      }
      else if ((((local_74 != 0) || (local_70 != 0)) || (local_6c != 0)) || (local_68 != 0))
      goto LAB_006ea17d;
      break;
    case 3:
      iVar3 = FUN_0043b210(); // get message data
      *(undefined4 *)(this + 0x88) = *(undefined4 *)(iVar3 + 8); // +0x88: scriptObjectRef
    }
    FUN_0043b1a0(); // advance to next message
    cVar1 = FUN_0043b120(); // check for more messages
  } while( true );
}