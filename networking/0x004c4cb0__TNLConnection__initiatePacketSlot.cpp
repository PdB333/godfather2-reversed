// FUNC_NAME: TNLConnection::initiatePacketSlot
void __thiscall TNLConnection::initiatePacketSlot(int thisPtr, int connectionPtr, short slotIndex, undefined4 param4, undefined8 *param5)

{
  int slotEntry;
  char hasValidSequence;
  undefined4 sequenceKey;
  undefined8 *slotBuffer;
  int slotOffset;
  
  slotOffset = thisPtr;
  *(short *)(connectionPtr + 0x2a) = (short)thisPtr; // +0x2a slotIndex being set (likely packet sequence)
  slotEntry = thisPtr * 0x20;
  *(int *)(*(int *)(unaff_EDI + 0x10) + 0x10 + slotEntry) = connectionPtr; // store connection ptr in packet slot array
  hasValidSequence = FUN_00441b10(*(undefined4 *)(*(int *)(connectionPtr + 0x54) + 0x30), &slotOffset); // check sequence validity via some table
  if (hasValidSequence == '\0') {
    FUN_00441b10(*(undefined4 *)(*(int *)(slotOffset + 0x54) + 0x34), &slotOffset); // fallback sequence check
  }
  *(int *)(*(int *)(unaff_EDI + 0x10) + 4 + slotEntry) = slotOffset; // store updated slot offset
  *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 8 + slotEntry) =
       *(undefined4 *)(*(int *)(slotOffset + 0x54) + 0x30); // +0x30 sequence value from connection
  *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0x18 + slotEntry) = *(undefined4 *)(slotOffset + 100); // +100 some parameter (timestamp?)
  *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0xc + slotEntry) = param4; // +0xc param4 stored
  sequenceKey = FUN_004c4ae0(); // call to get unique sequence key (likely packet ID)
  *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0x14 + slotEntry) = sequenceKey; // +0x14 packet sequence key
  *(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0x1c + slotEntry) = 0; // +0x1c slot status (0 = free/initialized)
  slotBuffer = (undefined8 *)(thisPtr * 0x10 + *(int *)(unaff_EDI + 4)); // buffer offset for packet data
  *slotBuffer = *param5; // copy first 8 bytes of packet header
  slotBuffer[1] = param5[1]; // copy next 8 bytes
  *(undefined1 *)(*(int *)(unaff_EDI + 8) + thisPtr) = 0xff; // mark slot as used (0xff)
  *(undefined2 *)(*(int *)(unaff_EDI + 0xc) + thisPtr * 2) = param_3; // store the slot index as short
  return;
}