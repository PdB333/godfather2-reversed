// FUNC_NAME: HashTable::removeByKey
// Address: 0x004ce3c0
// Role: Removes a key-value pair from a hash table by key string (wide character).
// The table uses a doubly linked list of nodes (sentinel at this+0x24).
// Each node contains a pointer to an entry structure (key, value, custom deleter callbacks).
// The function compares wide-character strings (2 bytes per character) and removes the first match.

void __thiscall HashTable::removeByKey(int this, const wchar_t *key)
{
  HashNode *current;         // piVar6
  HashNode *sentinel;        // (this+0x24)
  Entry *entry;              // piVar2
  byte *pKey;                // pbVar3
  byte *pKey2;               // pbVar4
  int cmpResult;             // iVar5
  bool bLess;                // bVar7
  byte ch;                   // bVar1

  sentinel = *(HashNode **)(this + 0x24);        // +0x24: pointer to sentinel node
  current = (HashNode *)**(int **)(this + 0x24); // first actual node

  do {
    // If we have looped back to sentinel, no match found
    if (current == sentinel) {
      return;
    }

    // Integrity check (assertion-like call)
    if (current == sentinel) {
      FUN_00b97aea();
    }

    entry = (Entry *)current->field_2;            // +8: pointer to entry struct
    pKey = (byte *)entry->key;                    // entry->key (wide string)
    pKey2 = (byte *)key;

    // If entry has no key, use a default empty string pointer (DAT_0120546e)
    if (pKey == (byte *)0x0) {
      pKey = (byte *)&DAT_0120546e;
    }

    // Wide character string comparison (2 bytes per character)
    do {
      ch = *pKey2;
      bLess = ch < *pKey;
      if (ch != *pKey) {
        cmpResult = (1 - (int)bLess) - (int)(bLess != 0); // yields -1 or 1
        goto compare_done;
      }
      if (ch == 0) break;                      // null terminator => equal so far
      ch = pKey2[1];
      bLess = ch < pKey[1];
      if (ch != pKey[1]) {
        cmpResult = (1 - (int)bLess) - (int)(bLess != 0);
        goto compare_done;
      }
      pKey += 2;
      pKey2 += 2;
    } while (ch != 0);
    cmpResult = 0;                             // strings are equal

compare_done:
    if (cmpResult == 0) {
      // Found matching key: remove this node

      // Unlink node from doubly linked list
      if ((current != sentinel) || (FUN_00b97aea(), current != sentinel)) {
        *(int *)current->prev = (int)current->next;
        *(int *)(current->next + 4) = (int)current->prev;
      }

      // Free the node itself (using allocator vtable at this+0xc)
      (**(code (***)(int))(**(int **)(this + 0xc) + 4))(current, 0xc);

      // Decrement count in table
      *(int *)(this + 0x28) = *(int *)(this + 0x28) - 1;   // +0x28: table size

      // Cleanup entry: 2 function calls (likely decrement reference counts or free)
      FUN_004086d0(entry + 8);              // entry + 0x8
      FUN_00408310(entry + 8);              // entry + 0x8

      // Call custom destructor for value if exists
      if (entry->value != 0) {
        (*(code *)entry->deleterValue)(entry->value); // entry->deleterValue at +0x1C
      }

      // Call custom destructor for key if exists
      if (entry->key != 0) {
        (*(code *)entry->deleterKey)(entry->key);     // entry->deleterKey at +0x0C
      }

      int parent = *(int *)(this + 0x2c);  // +0x2c: optional parent table
      (*DAT_012059e0)(entry);             // Global deallocator for entry

      // If there is a parent, adjust its size
      if (parent != 0) {
        HashTable *parentTable = *(HashTable **)(parent + 0x10);  // parent+0x10 points to another table?
        parentTable->size -= 0x28;      // Decrease parent's size by 0x28
      }
      return;
    }

    // Move to next node
    if (current == sentinel) {
      FUN_00b97aea();
    }
    current = (HashNode *)current->next;
  } while (true);
}

// Structure definitions (not part of function but provided for clarity)
/*
struct HashNode {
    int prev;       // +0x00
    int next;       // +0x04
    Entry *entry;   // +0x08  (field_2)
};

struct Entry {
    wchar_t *key;           // +0x00
    void *value;            // +0x04
    uint8_t unknown[8];     // +0x08  (used in FUN_004086d0/FUN_00408310)
    void (*deleterKey)(void*); // +0x0C
    uint8_t unknown2[8];    // +0x10 to +0x17
    void (*deleterValue)(void*); // +0x1C
};

// Offsets within this:
// +0x0C: allocator/allocator vtable
// +0x24: sentinel node pointer
// +0x28: table size (int)
// +0x2C: optional parent pointer (used for accounting)
*/