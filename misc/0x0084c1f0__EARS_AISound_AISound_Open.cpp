// Xbox PDB: EARS_AISound_AISound_Open
// FUNC_NAME: createAISoundMessage
void createAISoundMessage(void)
{
  // Register AI sound message type string with the game's message system
  registerString(&DAT_0112dd08, "iMsgAISound");
  
  // Allocate a new instance of the AI sound message object (size 0x5c)
  int allocationResult = allocateMemory(0x5c);
  if (allocationResult != 0) {
    // Call the constructor/initializer for the allocated object
    constructAISoundMessage();
    return;
  }
  return;
}