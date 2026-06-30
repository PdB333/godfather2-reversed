// FUNC_NAME: EARS::Array::clear
void EARS::Array::clear(void)
{
  // Field offsets:
  // +0x00: mCount (int)
  // +0x04: mCapacity (int)
  // +0x08: mGrowSize (int) // unknown usage, often used for incremental allocation
  // +0x0C: mpData (void*)

  if (this->mpData != NULL) {
    // Zero out the elements (each 4 bytes, typically ints or pointers)
    _memset(this->mpData, 0, this->mCount * 4);
    // Free the dynamically allocated buffer
    _free(this->mpData);
    // Reset all fields
    this->mpData    = NULL;
    this->mCount    = 0;
    this->mCapacity = 0;
    this->mGrowSize = 0;
  }
}