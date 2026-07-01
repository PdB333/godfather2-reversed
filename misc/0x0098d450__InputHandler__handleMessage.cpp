// FUNC_NAME: InputHandler::handleMessage
// Function address: 0x0098d450
// Handles input messages (key/button presses) for the controller/menu system.
// Offsets: +0x5c = menuActiveFlag (int*), +0x200 = handledFlag (byte)
// Message values: 9 = back, 0xd (13) = confirm, 0x1b (27) = escape

void __thiscall InputHandler::handleMessage(InputHandler* this, int message)
{
  if (message == 9) {
    FUN_0098d250(); // Handle back button (e.g. return to previous menu)
  }
  if (*(int*)(this + 0x5c) != 0) { // Only process if a menu is active
    if (message != 0xd) {
      if (message != 0x1b) {
        FUN_0098a7f0(message); // Forward other messages to default handler
        *(uint8_t*)(this + 0x200) = 1; // Mark as handled
        return;
      }
      // Escape pressed
      FUN_0098ce00(0); // Exit with parameter 0
      return;
    }
    // Confirm pressed
    FUN_0098ce00(1); // Exit with parameter 1
  }
  return;
}