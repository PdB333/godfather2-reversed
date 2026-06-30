// FUNC_NAME: HashTableManager::setEntryValueForHash
#include <cstdint>

// Global pointer to a hash table structure, likely part of a game manager.
// Structure layout deduced from access patterns:
// +0x00: unknown (4 bytes?) - not used here
// +0x04: array[256] of uint32_t* (pointers to objects, 4 bytes each)
// +0x1c: uint8_t count - number of valid entries in the table
extern uint8_t* g_hashTableBase; // value from DAT_01223504

struct HashTableHeader {
    uint8_t pad0[0x04];      // +0x00 - unknown
    void* entries[256];      // +0x04 - array of object pointers
    uint8_t pad1[0x1c - 0x04 - 256*4]; // +0x104? Actually +0x104 is beyond, but only +0x1c used
    // Actually the array ends at 0x04+256*4 = 0x404. Offset 0x1c is within the header.
    // So we need a proper structure:
    // Let's define it more accurately:
    // +0x00: unknown (4 bytes)
    // +0x04: pointers[256]  (0x400 bytes)
    // +0x404: ? but count is at +0x1c which is inside the header block.
    // The base pointer points to a block that has header before the array? Let's re-express:
    // Actually from code: the base pointer DAT_01223504 has:
    //   - at +0x1c: byte count
    //   - at +0x04: array of pointers
    // So offset 0x1c is inside the structure, meaning the structure is at least 0x20 bytes,
    // and the array is at offset 4, running from +4 to +0x104 (256*4). So offset 0x1c is within the array zone? No, 0x1c < 0x104, so it's inside the pointer array. That would be weird because the count would be stored in the middle of the pointer array. More likely the base pointer points to a structure where the first 4 bytes are something, then an array of 256 pointers, and then at offset 0x1c from the start is a count? That would be offset 0x1c = 28, which is beyond the array? Actually 256*4=1024=0x400, so offset 0x1c is well within the first 32 bytes. So the array might start at a higher offset? Let's recalc: Code uses "DAT_01223504 + 4 + ((... & 0xff) * 4)". So the array starts at base+4. So entries are at base+4, base+8, ... base+0x404. So the count at base+0x1c is at offset 0x1c = 28 base+28, which is inside the array (since array elements start at base+4, and element 6 would be at base+4+24=base+28). That means the count byte is stored in the middle of the pointer array, which is odd. Possibly the structure is different: maybe the base is a pointer to a hash table object, and the actual data is at base+something else? No, the code reads directly at base+0x1c and base+4+... So base is likely a struct with: at +0x00: something, at +0x04: pointer array?, at +0x1c: count. So the array starts at +4, and +0x1c is inside the array region. That would corrupt an entry. Alternatively, maybe the count is at offset 0x1c from the start of the hash table, but the array is not at offset 4? Let me check: The code says "*(int *)(DAT_01223504 + 4 + ((param_1 ^ 0xad103100) & 0xff) * 4)". So the base address is DAT_01223504, then add 4, then add index*4. So the array starts at base+4. So yes, the count at base+0x1c overlaps with array indices 6,7,8? Actually index = (hash & 0xff) ranges 0-255. Offset = 4 + index*4. For index=6, offset = 4+24=28=0x1c. So that array slot would be used for count? Unless the count is stored as part of the first entry? That seems unlikely. Perhaps the structure is: base points to a struct where the first field is something, then a pointer array of 256 entries, but the count is at offset 0x1c which corresponds to the 7th pointer (index 6) of the array? That would mean the hash table stores pointers and the 7th entry is the count? That is bizarre. More likely, the decompiler's offset is from a different base. DAT_01223504 might point to some larger manager object, not directly to the hash table. The code accesses "DAT_01223504 + 0x1c" and "DAT_01223504 + 4 + ...". So DAT_01223504 could be a pointer to a structure that contains a hash table sub-structure? But the offsets are plain. I'll treat it as a global block: at offset 0x1c is a byte count, and at offset 4 is a pointer array. This is plausible if the structure is like:
struct HashTable {
    uint32_t unknown;   // +0x00
    void* entries[256]; // +0x04 - exactly 1024 bytes
    uint8_t count;      // +0x1c? Wait, that would be +0x1c = 28 bytes from start, but the array ends at 1028 bytes? No, the array occupies bytes 4 to 1027 (0x4 to 0x403). Then count at 0x1c is within the array, as previously noted. So maybe the array size is smaller? Perhaps it's not 256 but something else? The mask is & 0xff, so index up to 255, so array size 256 entries. Unless the count is at the end of the array? Offset 0x1c from start is 28. So the array would be truncated? This is inconsistent.
Alternative interpretation: The base address might be the hash table itself, and the count is at offset 0x1c, but the array starts at a different offset? Let's re-read: "*(int *)(DAT_01223504 + 4 + ((param_1 ^ 0xad103100) & 0xff) * 4)". That is correct. So array at base+4. Count at base+0x1c. So the array overlaps count. Could it be that the count is stored as a byte inside the first few entries? For example, maybe the table uses the first few entries for metadata? But that would be hacky.
Another possibility: The decompiler mistakenly added offset? But the code is clear.
I'll assume the structure is as given, but note the overlap in comments. For reconstruction, we'll define a struct that matches the offsets, even if it looks odd.
Let's continue.

We'll define:
struct HashTableStruct {
    uint32_t unknown;    // +0x00
    void* entries[256];  // +0x04 (0x04 to 0x404)
    uint8_t count;       // +0x1c (inside the entries region) - actually this overlaps with entry[6]! So we cannot have both. The structure might be different: maybe the count is at offset 0x1c from the start of the hash table, but the array starts at a different offset? Let's consider that the code might have a constant offset. For example, if the base pointer points to an object that has a hash table as a member, and that hash table is at some offset, then the offsets seen are relative to the hash table object. But the code directly uses base+ offsets. So base is likely the hash table object itself. I'm going to ignore the weird overlap and just match the offsets literally, commenting the potential issue.

Actually, a common pattern: the hash table header might have a count and then an array of pointers, but the count is at a fixed position in the header, and the array immediately follows. That would place the count before the array. For instance, if count is at offset 0x1c, then the array would start at offset 0x20 to be aligned? But the code says array at offset 4. So perhaps the header size is 0x1c (28 bytes) with the count at the end of the header, and then the array starts at offset 0x1c? No, because the code uses offset 4 for the array.
Let's re-evaluate: maybe the mask is not &0xff but something else? It is &0xff. So index 0-255.
I think there might be a mistake in the decompiler's offset calculation. Perhaps the original C code uses an array index that is multiplied by 4, but the base of the array is at DAT_01223504 + some offset, and the count is at a different offset. The given offsets are literal from the binary. I'll trust them.
Given the lack of clarity, I'll implement the function as exactly described, with comments explaining the offsets.
*/
bool HashTableManager::setEntryValueForHash(uint32_t hashKey, uint32_t value)
{
    // XOR with constant is likely a hash function to scramble the key
    uint32_t hashedIndex = hashKey ^ 0xad103100;
    uint8_t* tableBase = reinterpret_cast<uint8_t*>(g_hashTableBase);

    // Compare the hash to the count stored at offset 0x1c
    if (hashedIndex < static_cast<uint32_t>(*(tableBase + 0x1c)))
    {
        // Get pointer from array at offset 4 + (hashedIndex & 0xff) * 4
        void** entry = reinterpret_cast<void**>(tableBase + 4 + ((hashedIndex & 0xff) * 4));
        if (*entry != nullptr)
        {
            // Write the value to offset 0x68 of the found object
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(*entry) + 0x68) = value;
            return true;
        }
    }
    return false;
}