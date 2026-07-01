// FUNC_NAME: CrimeManager::setCurrentCrime
void __thiscall CrimeManager::setCurrentCrime(CrimeManager* this, Crime* crime)
{
  int crimeType;

  if (this->currentCrime != crime) {
    this->currentCrime = crime;
    
    // Clear crime-related flags if they were set (bit 21 and 22)
    if ((this->flags & 0xffdfffff) != this->flags) {
      (this->vtable->onCrimeChanged)(0x10);
      this->flags &= 0xffdfffff;
    }
    if ((this->flags & 0xffbfffff) != this->flags) {
      (this->vtable->onCrimeChanged)(0x10);
      this->flags &= 0xffbfffff;
    }
    
    if (crime != NULL) {
      crimeType = getCrimeType(crime);
      if (crimeType == 2) {
        debugLogCrime(0x200000);
      }
      else if (crimeType == 3) {
        debugLogCrime(0x400000);
        return;
      }
    }
  }
  return;
}