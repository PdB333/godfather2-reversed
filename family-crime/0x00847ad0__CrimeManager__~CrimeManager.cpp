// FUNC_NAME: CrimeManager::~CrimeManager
void __thiscall CrimeManager::destroy(void)
{
  int* ptrList;
  char done;
  int scenePtr;
  int idx;
  int* pp;
  int* pp2;
  int local_sceneCount;
  int local_sceneArray;
  
  // Set vtable pointers to destructor vtables (multiple inheritance)
  *this = &PTR_LAB_00d74c4c;               // +0x00: primary vtable
  *(int**)((char*)this + 0x3C) = &PTR_LAB_00d74c3c;   // +0x3C: second base vtable
  *(int**)((char*)this + 0x48) = &PTR_LAB_00d74c38;   // +0x48: third base vtable
  *(int**)((char*)this + 0x50) = &PTR_LAB_00d74c34;   // +0x50: fourth base vtable

  // If we are registered in the global manager, unregister
  if ((DAT_01129948 != 0) && (*(void**)(DAT_01129948 + 0x38) == this)) {
    CrimeManager::unregisterFromGlobal();  // FUN_00843b60
  }

  // Decrement reference counts or remove from global lists
  GlobalList::remove(&DAT_0112dcec);        // FUN_00408310
  GlobalList::remove(&DAT_0112dce4);        // FUN_00408310

  // Clean up internal buffer at +0x1C (size 8)
  InternalBuffer::clear(*(int*)((char*)this + 0x1C), 8, (int*)((char*)this + 0x3C)); // FUN_004035f0

  // Sub-destructor for child object
  CrimeManager::destroySubComponent();       // FUN_00847060

  // Clean up another buffer at +0x128 (size 0x114)
  InternalBuffer::clear(*(int*)((char*)this + 0x128), 0x114, (int*)((char*)this + 0x3C)); // FUN_004035f0

  *(int*)((char*)this + 0x128) = 0;          // +0x128: buffer pointer cleared
  *(int*)((char*)this + 0x150) = 0;          // +0x150: other member cleared
  *(int*)((char*)this + 0x130) = 0;          // +0x130: other member cleared

  // Clean up seven "DynArray" objects (likely dynamic arrays of scenes/objects)
  // Offsets: +0x54, +0x5C, +0x64, +0x6C, +0x74, +0x7C, +0x84
  DynArray::clear((DynArray*)((char*)this + 0x54));     // FUN_004086d0
  DynArray::remove((DynArray*)((char*)this + 0x54));    // FUN_00408310
  DynArray::clear((DynArray*)((char*)this + 0x5C));
  DynArray::remove((DynArray*)((char*)this + 0x5C));
  DynArray::clear((DynArray*)((char*)this + 0x64));
  DynArray::remove((DynArray*)((char*)this + 0x64));
  DynArray::clear((DynArray*)((char*)this + 0x6C));
  DynArray::remove((DynArray*)((char*)this + 0x6C));
  DynArray::remove((DynArray*)((char*)this + 0x74));
  DynArray::remove((DynArray*)((char*)this + 0x7C));
  DynArray::remove((DynArray*)((char*)this + 0x84));

  // Iterate and clear a global linked list (DAT_0120685c)
  done = GlobalList::read(&DAT_0120685c);    // FUN_00402080
  while (done != '\0') {
    DynArray::clear(&DAT_0120685c);          // FUN_004086d0
    done = GlobalList::read(&DAT_0120685c);
  }
  DynArray::clear(&DAT_012069c4);            // FUN_004086d0

  // If bit 3 of flags at +0x118 is not set, call additional cleanup
  if ((*(unsigned char*)((char*)this + 0x118) & 8) == 0) {
    CrimeManager::destroySceneGroup();        // FUN_00846250
  }

  // Access hash table at +0x8C and look up key 0x30431d5e (likely a hash of "crimeScene" or similar)
  int* hashTable = (int*)((char*)this + 0x8C);
  int tableContent = HashTable::getContent(hashTable, 0); // FUN_00445ff0
  local_sceneCount = 0;
  bool found = HashTable::find((HashTable*)tableContent, 0x30431d5e, &local_sceneCount); // FUN_004480d0

  if ((found) && (local_sceneArray = local_sceneCount, local_sceneCount != 0)) {
    // Process dynamic array of pointers at +0x100 (count at +0x104)
    int* ptrArray = *(int**)((char*)this + 0x100);
    int num = *(int*)((char*)this + 0x104);
    if (ptrArray != ptrArray + num) {
      do {
        int scene = local_sceneArray;
        if (*ptrArray != 0) {
          // Get the dynamic array in the scene object at +0x108 (size) and +0x100 (buffer)
          int* sceneArray = *(int**)(scene + 0x100);
          int size = *(int*)(scene + 0x104);
          int* newArray = (int*)(scene + 0x100);
          if (*(int*)(scene + 0x104) == size) {
            if (size == 0) {
              size = 1;
            } else {
              size = size * 2;
            }
            DynamicArray::reallocate(scene, size); // FUN_00461ea0
          }
          int currentSize = *(int*)(scene + 0x104);
          int* writePtr = (int*)(*((int*)(scene + 0x100)) + currentSize * 4);
          *(int*)(scene + 0x104) = currentSize + 1;
          if (writePtr != (int*)0x0) {
            *writePtr = 0;
            int val = *ptrArray;
            *writePtr = val;
            if (val != 0) {
              *(int**)(val + 8) = writePtr;
              *ptrArray = 0;
            }
          }
        }
        ptrArray = ptrArray + 1;
      } while (ptrArray != (int*)(*(int*)((char*)this + 0x100) + *(int*)((char*)this + 0x104) * 4));
    }

    // Process array of pairs at +0x10C (count at +0x110), each pair is 8 bytes (two ints)
    int* pairArray = *(int**)((char*)this + 0x10C);
    int numPairs = *(int*)((char*)this + 0x110);
    if (pairArray != pairArray + numPairs * 2) {
      do {
        if ((*pairArray != 0) && (int obj = *pairArray + -0x48, obj != 0)) {
          SceneObject::destroy(obj);          // FUN_00847220
        }
        pairArray = pairArray + 2;            // Skip second int (probably unused)
      } while (pairArray != (int*)(*(int*)((char*)this + 0x10C) + *(int*)((char*)this + 0x110) * 8));
    }
  }

  // Clear and free the first dynamic array (pointers)
  int numItems = *(int*)((char*)this + 0x104);
  while (numItems = numItems + -1, -1 < numItems) {
    int* slot = (int*)(*(int*)((char*)this + 0x100) + numItems * 4);
    int val = *slot;
    if (val != 0) {
      *(int*)(val + 8) = 0;
      *slot = 0;
    }
  }
  *(int*)((char*)this + 0x104) = 0;
  Memory::free(*(void**)((char*)this + 0x100)); // FUN_009c8f10
  *(int*)((char*)this + 0x100) = 0;
  *(int*)((char*)this + 0x108) = 0;

  // Additional cleanup
  CrimeManager::destroyInternalList();        // FUN_00846830

  // If there's a matrix/transform at +0x120, copy current transform from +0x8C to it and release it
  int* transform = (int*)((char*)this + 0x120);
  if ((*transform != 0) && (*transform != 0x48)) {
    if (*transform == 0) {
      int dummy = 0;
    } else {
      int dummy = *transform + -0x48;
    }
    *(int*)(*(int*)((char*)this + 0x120) + 0x8C) = *(int*)((char*)this + 0x8C);
    *(int*)(*(int*)((char*)this + 0x120) + 0x90) = *(int*)((char*)this + 0x90);
    *(int*)(*(int*)((char*)this + 0x120) + 0x94) = *(int*)((char*)this + 0x94);
    *(int*)(*(int*)((char*)this + 0x120) + 0x98) = *(int*)((char*)this + 0x98);
  }
  if (*transform != 0) {
    Object::release(transform);               // FUN_004daf90
  }

  // Clear and free the pair array
  int numPairs2 = *(int*)((char*)this + 0x110);
  while (numPairs2 = numPairs2 + -1, -1 < numPairs2) {
    int base = *(int*)((char*)this + 0x10C);
    if (*(int*)(base + numPairs2 * 8) != 0) {
      Object::release((int*)(base + numPairs2 * 8)); // FUN_004daf90
    }
  }
  if (*(int*)((char*)this + 0x10C) != 0) {
    Memory::free(*(void**)((char*)this + 0x10C)); // FUN_009c8f10
  }

  // Final cleaning of first array (again)
  int numItems2 = *(int*)((char*)this + 0x104);
  while (numItems2 = numItems2 + -1, -1 < numItems2) {
    int* slot2 = (int*)(*(int*)((char*)this + 0x100) + numItems2 * 4);
    int val2 = *slot2;
    if (val2 != 0) {
      *(int*)(val2 + 8) = 0;
      *slot2 = 0;
    }
  }
  if (*(int*)((char*)this + 0x100) != 0) {
    Memory::free(*(void**)((char*)this + 0x100)); // FUN_009c8f10
  }
  if (*(int*)((char*)this + 0xF0) != 0) {
    Memory::free(*(void**)((char*)this + 0xF0)); // FUN_009c8f10
  }

  // Set vtable back to base destructor vtable
  *(int**)((char*)this + 0x50) = &PTR_LAB_00e32854;
  GlobalCleanup::reset();                      // FUN_0046c640
  return;
}