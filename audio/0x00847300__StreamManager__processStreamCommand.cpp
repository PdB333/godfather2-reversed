// FUNC_NAME: StreamManager::processStreamCommand
void __thiscall StreamManager::processStreamCommand(int this, int command)
{
  char cVar1;
  undefined4 uVar2;
  
  if ((char)command == '\0') {
    if ((*(byte *)(this + 0x118) & 1) != 0) {
      // +0x118: flags byte, bit 0 = stream active
      // +0xfc: current stream entry pointer
      // +0x04: stream entry field (offset 4)
      // +0x08: stream entry data (offset 8)
      FUN_00846b90(this, *(undefined4 *)(*(int *)(this + 0xfc) + 4),
                   *(int *)(this + 0xfc) + 8);
      return;
    }
  }
  else {
    // Check if next stream entry exists (entries are 0xC bytes each)
    // +0xf0: stream entry array base
    // +0xf4: stream entry count
    if (*(int *)(this + 0xfc) + 0xc != *(int *)(this + 0xf0) + *(int *)(this + 0xf4) * 0xc)
    {
      // Process next stream entry
      // +0x10: next entry field (offset 0x10)
      // +0x14: next entry data (offset 0x14)
      FUN_00846b90(this, *(undefined4 *)(*(int *)(this + 0xfc) + 0x10),
                   *(int *)(this + 0xfc) + 0x14);
      return;
    }
    // No more entries - check for pending command
    uVar2 = FUN_00445ff0(this + 0x8c, 0);  // +0x8c: command queue
    command = 0;
    cVar1 = FUN_004480d0(uVar2, 0x30431d5e, &command);  // Check for specific command hash
    if ((cVar1 != '\0') && (command != 0)) {
      FUN_00847300(0, 0);  // Recursive call with null this? Possibly error handling
      return;
    }
    FUN_00846a50();  // Advance to next stream
  }
  return;
}