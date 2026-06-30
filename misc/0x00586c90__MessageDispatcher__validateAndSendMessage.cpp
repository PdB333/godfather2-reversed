// FUNC_NAME: MessageDispatcher::validateAndSendMessage
// Reconstructed from Ghidra decompilation at 0x00586c90
// This function validates that the object ID matches the dispatcher's owner,
// then builds and dispatches a message structure.

uint __thiscall MessageDispatcher::validateAndSendMessage(int thisPtr, int object, int extraData)
{
  uint result;
  int ownerId;
  int objectId;

  ownerId = *(int *)(thisPtr + 4);          // +0x04: owner ID of this dispatcher
  objectId = *(int *)(object + 0x14);       // +0x14: object ID to check

  // Check if the object matches the expected owner
  if (objectId != ownerId) {
    // Return with low byte masked off (error/invalid)
    return result & 0xffffff00;
  }

  // Build a message structure on the stack
  struct MessageHeader {
    int size;               // 0x00: total message size
    int unknown1;           // 0x04
    int unknown2;           // 0x08
    int type;               // 0x0C: message type? (0x23 = 35)
    int globalData;         // 0x10: from global variable
    int localValue;         // 0x14: from thisPtr+8
    int extraFromObject;    // 0x18: from object+0x18
    int unknown3;           // 0x1C
    int extraFromExtraData; // 0x20: from extraData+0x30
    int padding[7];         // 0x24-0x3C: zeros
  } msg;

  int *msgPtr = &msg.size;  // pointer to message

  // Zero-fill the padding/unknown fields
  msg.unknown1 = 0;
  msg.unknown2 = 0;
  msg.unknown3 = 0;
  for (int i = 0; i < 7; i++) {
    msg.padding[i] = 0;
  }

  // Initialize message fields
  msg.size = 4;                          // Probably header size
  msg.type = 0x23;                       // Command/type identifier
  msg.globalData = DAT_00e2b1a4;         // Global constant or reference
  msg.localValue = *(int *)(thisPtr + 8); // +0x08: local data from dispatcher
  msg.extraFromObject = *(int *)(object + 0x18); // +0x18: extra data from object
  msg.extraFromExtraData = *(int *)(extraData + 0x30); // +0x30: extra data from third param
  msg.unknown1 = -1;                     // 0xFFFFFFFF
  msg.unknown2 = -1;                     // 0xFFFFFFFF
  msg.unknown3 = msg.extraFromObject;    // Copy? (local_3c = local_68)

  // The second parameter to the call is a pointer to a structure that holds the object pointer?
  int objectPtrHolder = object;          // local_74 = object
  // Call the actual message dispatch function
  result = FUN_00579450(object, &objectPtrHolder);
  return result;
}