// FUNC_NAME: TNLConnection::processNextPacket
undefined4 __fastcall TNLConnection::processNextPacket(int this)
{
  undefined4 result;
  
  // Check if there is a pending packet in the queue at offset +0x0C
  if (*(int *)(this + 0xc) != 0) {
    // Call the virtual function at vtable+0x14 (likely processPacket or handlePacket)
    // The vtable pointer is dereferenced from the packet object at +0x0C
    result = (**(code **)(**(int **)(this + 0xc) + 0x14))();
    return result;
  }
  
  // No packet to process
  return 0;
}