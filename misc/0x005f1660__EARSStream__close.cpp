// FUNC_NAME: EARSStream::close
void EARSStream::close(void)
{
  // Check if object exists and is not already closed (bit 0x40 in flags)
  if ((this != (EARSStream *)0x0) && ((this->flags & 0x40) == 0))
  {
    // If the reference count or stream data count at +0x18 is positive
    if (0 < this->dataCount)
    {
      this->releaseData();  // 0x005f57b0
      this->destroyData();  // 0x005f5730
      this->dataCount = 0;
    }
    // Mark as closed: set bit 0x40 and clear bit 0x20 in 16-bit flags at +0x10
    this->flags = (this->flags & 0xffdf) | 0x40;
  }
}