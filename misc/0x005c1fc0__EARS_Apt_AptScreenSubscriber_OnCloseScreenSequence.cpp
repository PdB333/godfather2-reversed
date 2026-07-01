// Xbox PDB: EARS::Apt::AptScreenSubscriber::OnCloseScreenSequence
// FUNC_NAME: UIScreen::closeScreen
undefined4 __thiscall UIScreen::closeScreen(void) {
  char canClose;
  
  // Check if screen can be closed
  canClose = this->canClose();
  if (canClose != '\0') {
    // Perform pre-close actions
    this->preClose();
    // Perform post-close actions
    this->postClose();
  }
  
  // Get screen's fade color from vtable: vtable at +0x10, method at +4
  // The method returns a 32-bit color (likely ARGB or RGBA)
  uVar2 = (*(code **)(this->vtable + 0x10))(this -> +4); // vtable entry at +4 from vtable pointer at +0x10
  // Store color as 4 bytes in big-endian order (global screenFadeColor)
  DAT_01223564 = (undefined1)((uint)uVar2 >> 0x18); // high byte -> R? 
  DAT_01223565 = (undefined1)((uint)uVar2 >> 0x10); // second byte -> G?
  DAT_01223566 = (undefined1)((uint)uVar2 >> 8);    // third byte -> B?
  DAT_01223567 = (undefined1)uVar2;                 // low byte -> A?
  DAT_01223568 = 0;                                  // null terminator or next component
  
  // Fire "OnCloseScreen" event with the color data as argument
  fireEvent("OnCloseScreen", 0, 0, 1, &DAT_01223564);
  
  return 1; // return success
}