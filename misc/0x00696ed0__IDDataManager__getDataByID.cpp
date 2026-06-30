// FUNC_NAME: IDDataManager::getDataByID
// Function address: 0x00696ed0
// Returns pointer to data at id + 0x1c (presumably a field within an element)
// Looks up an element by its ID; if not found, creates it via FUN_00696a90

int __thiscall IDDataManager::getDataByID(void* this, uint key)
{
  int id;
  int index;
  int* piVar3;
  char unknownBuffer_8[8];           // temporary buffer for key/hash
  long long unknownBuffer_8b;        // overlapping buffer (8 bytes)
  int tempArray[3];                  // temporary array for function call
  code* functionPtr;                 // function pointer from tempArray[0]? Actually used as (*functionPtr)(tempArray[0])
  long long unknownVar;              // unused?
  int unknownInt;                    // unused?

  // Extract ID from the key (likely an integer or hash)
  id = FUN_00694950(key);

  // Assert if this is null
  if (this == 0) {
    FUN_00b97aea(); // assertion failure
  }

  // If the ID differs from the stored current ID, try to find by index
  if (id != *(int*)((char*)this + 4)) { // this+0x4 : currentID
    index = FUN_004d4b20(id + 0xc); // likely find index in array
    if (index >= 0) {
      goto found; // if found, return early
    }
  }

  // Setup: clear buffer, call some initialisation
  unknownBuffer_8b = 0;
  FUN_004d3b50(key);                 // possibly reset or preprocess key
  unknownVar = unknownBuffer_8b;
  unknownInt = 0;

  // Call the insertion/lookup helper (FUN_00696a90) with buffers
  piVar3 = (int*)FUN_00696a90(unknownBuffer_8, this, id, tempArray);

  // Extract updated this pointer and new ID from result
  this = (void*)*piVar3;
  id = piVar3[1];

  // If there is a stored function pointer, call it
  if (tempArray[0] != 0) {
    (*functionPtr)(tempArray[0]); // likely cleanup or callback
  }

found:
  // Assertions at the jump target
  if (this == 0) {
    FUN_00b97aea();
  }
  if (id == *(int*)((char*)this + 4)) { // this+0x4 : currentID
    FUN_00b97aea();
  }

  // Return pointer to data at offset 0x1c from the ID (i.e., id + 0x1c bytes)
  return id + 0x1c;
}