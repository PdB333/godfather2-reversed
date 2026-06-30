// FUNC_NAME: UIScreen::handleMessage
void __thiscall UIScreen::handleMessage(int this, int* message)
{
  int msgId = *message;
  
  // Message ID 0x0120e93c - Initialize screen
  if (msgId == MST_INIT) {
    FUN_004086d0(&MST_INIT); // Possibly free/unregister message
    int unknown = FUN_006b0ee0(*(int*)(this + 0x148)); // Factory
    this[0x144] = unknown;
    int baseObj = this - 0x3c; // Base object offset (negative)
    FUN_006b5b80(baseObj); // Initialize base
    FUN_006b1560(baseObj); // Another init
    int child = FUN_006b4860(); // Get singleton?
    FUN_006ae040(child); // Attach/register
    FUN_008f6f50(0x14, baseObj); // Start timer (0x14 = 20ms?)
    
    // Setup callback structure
    int* cbStruct = *(int**)(this + 0x144);
    int* ptr = &PTR_LAB_00d5dbb0; // Static callback array
    int* glob = DAT_0112a628; // Global callback list
    int* local_8 = &ptr;
    int local_4 = 0;
    FUN_00408a00(&glob, 0); // Register callback
    FUN_0046efc0(message); // Consume message
    return;
  }
  
  // Handle other message IDs stored at specific offsets
  if (msgId == *(int*)(this + 0x208)) {
    FUN_006b2600(0); // Pause action
    FUN_0046efc0(message);
    return;
  }
  
  if (msgId == *(int*)(this + 0x210)) {
    FUN_006b2600(1); // Resume action
    FUN_0046efc0(message);
    return;
  }
  
  if (msgId == *(int*)(this + 0x200)) {
    FUN_006b68c0(0x637b907, 0, 0, 0); // Send message to entity
    FUN_0046efc0(message);
    return;
  }
  
  if (msgId == *(int*)(this + 0x220)) {
    FUN_006b2c20(); // Reset/clear
    FUN_0046efc0(message);
    return;
  }
  
  if (msgId == *(int*)(this + 0x270)) {
    FUN_006b6680(0x637b907, 0, 0, 0); // Send another message
    FUN_0046efc0(message);
    return;
  }
  
  if (msgId == DAT_0112a600) {
    int value = *(message[1] + 0xc); // Parameter from message
    FUN_006ae040(value);
    FUN_0046efc0(message);
    return;
  }
  
  // Toggle visibility or state
  if (msgId == *(int*)(this + 0x250)) {
    int* flags = (int*)(this[0x144] + 0x34);
    *flags |= 0x400000; // Set visibility flag
    int** local_8 = (int**)(this[0x144]); // Pointer to UI data
    int local_4 = 0; // Show notification
    // Fall through to notify observers
  }
  else if (msgId == *(int*)(this + 600)) {
    int* flags = (int*)(this[0x144] + 0x34);
    *flags &= 0xffbfffff; // Clear visibility flag
    int** local_8 = (int**)(this[0x144]);
    int local_4 = 1; // Hide notification
    // Fall through to notify observers
  }
  else {
    FUN_0046efc0(message);
    return;
  }
  
  // Notify observers about visibility change
  int** local_c = &PTR_LAB_00d5dbb8; // Another static callback
  FUN_0045c400(&DAT_0112a5c4, &local_c, 0);
  FUN_0046efc0(message);
}