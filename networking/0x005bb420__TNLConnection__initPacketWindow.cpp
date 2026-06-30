// FUNC_NAME: TNLConnection::initPacketWindow
void TNLConnection::initPacketWindow(void)
{
  uint uVar1;
  int iVar2;
  uint *this; // unaff_ESI

  // Set flags: clear bits 0-2,4-14, set bits 0,2,4 (0x15 = 00010101b)
  // This initializes the packet window state
  *this = *this & 0xffff8015 | 0x15;
  
  // Clear the packet sequence number (offset +2)
  *(undefined2 *)((int)this + 2) = 0;
  
  // Set the high bit (0x8000) - likely marks window as active
  *this = *this | 0x8000;
  
  // Set the window size to 4 (offset +4)
  *(undefined2 *)(this + 1) = 4;
  
  // Clear the next expected sequence (offset +6)
  *(undefined2 *)((int)this + 6) = 0;
  
  // Initialize the packet buffer pointer to point to the buffer itself (offset +8)
  this[2] = (uint)(this + 3);
  
  // Clear the 64-byte packet buffer (offset +12, size 0x40)
  _memset(this + 3, 0, 0x40);
  
  // Clear the packet count (offset +0x50)
  this[0x14] = 0;
  
  // Get the current time from the system timer
  iVar2 = FUN_005a19c0(); // likely getSystemTime()
  uVar1 = *(uint *)(*(int *)(iVar2 + 8) + 4); // get current tick count
  
  // Clear the last ACK time (offset +0x54)
  this[0x15] = 0;
  
  // Store the current time as the base time (offset +0x4C)
  this[0x13] = uVar1;
  
  return;
}