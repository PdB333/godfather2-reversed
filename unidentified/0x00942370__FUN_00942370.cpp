// FUNC_NAME: SomeClass::findAndProcessEntry
void __thiscall SomeClass::findAndProcessEntry(int thisPtr, int *entryData)
{
  int *currentEntry;
  int counter;
  
  currentEntry = (int *)(thisPtr + 0x78); // +0x78: start of entry array
  counter = 0x40; // 64 entries total
  do {
    // Compare 4 ints (16 bytes) per entry
    if ((((currentEntry[-2] == *entryData) && 
          (currentEntry[-1] == entryData[1])) && 
         (*currentEntry == entryData[2])) && 
        (currentEntry[1] == entryData[3])) {
      // Match found - process it
      FUN_00941ee0(); // processMatchedEntry
    }
    currentEntry = currentEntry + 0x20; // +0x80 bytes per entry (32 ints)
    counter = counter + -1;
  } while (counter != 0);
  return;
}