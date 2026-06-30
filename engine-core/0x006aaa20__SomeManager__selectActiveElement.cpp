// FUNC_NAME: SomeManager::selectActiveElement
void __fastcall SomeManager::selectActiveElement(int this)
{
  uint count;
  int selectedIndex;
  uint i;
  uint j;
  int *elementArray;
  int bestElement;
  uint bestIndex;
  int *currentElement;
  
  count = *(uint *)(this + 0x14);
  if (count != 0) {
    bestIndex = 0xffffffff;
    if (count == 1) {
      // Only one element, check if it's active
      if (*(char *)(**(int **)(this + 0x10) + 0x68) != '\0') {
        FUN_006aa660(0);
        return;
      }
    }
    else {
      elementArray = *(int **)(this + 0x10);
      bestElement = *elementArray;
      i = 0;
      j = i;
      currentElement = elementArray;
      if (count != 0) {
        do {
          // Find first active element
          if (*(char *)(*currentElement + 0x68) != '\0') {
            bestElement = elementArray[j];
            i = j + 1;
            bestIndex = j;
            break;
          }
          i = j + 1;
          j = i;
          currentElement = currentElement + 1;
        } while (i < count);
      }
      // Scan remaining elements for the best active one
      if (i < count) {
        currentElement = elementArray + i;
        do {
          int elem = *currentElement;
          if ((*(char *)(elem + 0x68) != '\0') &&
             ((*(char *)(bestElement + 0x68) == '\0' || (*(uint *)(bestElement + 100) < *(uint *)(elem + 100)))
             )) {
            bestElement = elem;
            bestIndex = i;
          }
          i = i + 1;
          currentElement = currentElement + 1;
        } while (i < count);
      }
    }
    FUN_006aa660(bestIndex);
  }
  return;
}