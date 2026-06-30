// FUNC_NAME: OnlineServices::handleTermsOfServiceResponse
void __thiscall OnlineServices::handleTermsOfServiceResponse(char *termsText)
{
  // Set initial state to 4 (likely "processing" or "received")
  this->m_eulaState = 4;

  // Free any existing terms text
  if (this->m_termsText != (char *)0x0) {
    this->m_termsTextLength = 0;
    free(this->m_termsText);  // FUN_009c8f10 is a free wrapper
  }

  if (termsText == (char *)0x0) {
    // Error case: use default error message
    this->m_termsText = "An error occurred when receiving Terms of Service";
    this->m_termsTextLength = strlen(this->m_termsText);
  } else {
    // Allocate and copy provided text (including null terminator)
    int length = strlen(termsText);
    this->m_termsTextLength = length;
    char *newText = (char *)malloc(length + 1);  // FUN_009c8e80 is a malloc wrapper
    this->m_termsText = newText;
    memcpy(newText, termsText, length + 1);
  }

  // Check flag bit 2 (0x4) to determine if already agreed/acknowledged
  if ((this->m_flags & 4) == 0) {
    // Not acknowledged: transition to substate 2, state 0 (ready/display?)
    this->m_eulaSubstate = 2;
    this->m_eulaState = 0;
  } else {
    // Already acknowledged: clear flag bit 7 (0x80) to mark as ready
    this->m_flags &= ~0x80;
  }
}