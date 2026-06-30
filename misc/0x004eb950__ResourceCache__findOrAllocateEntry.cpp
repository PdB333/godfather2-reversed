// FUNC_NAME: ResourceCache::findOrAllocateEntry

// Address: 0x004eb950
// Role: Look up or allocate an entry in the resource cache table.
// Table is a static array of 8-int entries (key[4], flags, refCount, etc.)
// Global count variable tracks allocated slots.
// Returns pointer to entry; if addRef is true, increments both the allocation
// count and the reference count for that slot.

#include <cstdint>

struct ResourceCacheEntry {
    int key[4];           // +0x00: 16-byte key
    short freeFlag;       // +0x14: low word of int[5]; 0 = free slot
    short unk0;           // +0x16: high word of int[5] (unused in this func)
    short refCount;       // +0x18: low word of int[6]; incremented on addRef
    short unk1;           // +0x1a: high word of int[6] (unused)
    // remainder of 8th int (int[7]) unused
};

static int s_entryCount = *(int*)0x010c2328;   // DAT_010c2328
static ResourceCacheEntry* s_entries = (ResourceCacheEntry*)0x011947e8; // DAT_011947e8

ResourceCacheEntry* ResourceCache::findOrAllocateEntry(const int key[4], bool addRef)
{
    if (key == nullptr ||
        (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0))
    {
        return nullptr;
    }

    int freeSlot = -1;
    int i;

    if (s_entryCount >= 0) {
        for (i = 0; i <= s_entryCount; ++i) {
            ResourceCacheEntry* entry = &s_entries[i];
            if (entry->key[2] == key[2] &&
                entry->key[3] == key[3] &&
                entry->key[0] == key[0] &&
                entry->key[1] == key[1]) {
                // Found exact match
                if (freeSlot != -1) {
                    // There was a free slot earlier; use that? No, return the match
                    // Actually the original goes to LAB_004eba04 from here if freeSlot != -1? Wait:
                    // original: if (iVar4 != -1) { puVar2 = ...; goto LAB_004eba04; }
                    // That means if there was previously a free slot, it returns the matched entry.
                    // So this branch only happens if freeSlot == -1, then break (to allocate new?).
                    // Actually the code:
                    // if (iVar4 != -1) { puVar2 = &DAT_011947e8 + iVar4 * 4; goto LAB_004eba04; }
                    // That's for the case where a free slot was found earlier (i.e., freeSlot != -1)
                    // Then it uses the free slot? No, it uses the matched slot? Let's reanalyze.
                    // In original: after the if, if (iVar4 != -1) { puVar2 = ...; goto LAB_004eba04; }
                    // iVar4 is the loop index i. So if freeSlot != -1 and we found a match, it returns the matched entry.
                    // If freeSlot == -1 and we found a match, it breaks out of loop (to allocate new? But break is missing).
                    // Actually original: if (iVar4 != -1) { puVar2 = ...; goto LAB_004eba04; } else break; 
                    // The else break is implied by the if-structure? The decompiled code has:
                    // if (iVar4 != -1) { ... goto LAB_004eba04; } break; 
                    // Wait the decompiled shows:
                    // if (iVar4 != -1) { puVar2 = ...; goto LAB_004eba04; }
                    // break;
                    // Actually the decompiled output: "if (iVar4 != -1) { puVar2 = ...; goto LAB_004eba04; } break;"
                    // That is odd: it breaks regardless? Let's see the source more carefully:
                    // In the decompiled block:
                    //   if ((((unaff_EDI[2] == piVar3[2]) && ...) && ...) {
                    //     if (iVar4 != -1) {
                    //       puVar2 = &DAT_011947e8 + iVar4 * 4;
                    //       goto LAB_004eba04;
                    //     }
                    //     break;
                    //   }
                    // So if the condition matches and iVar4 != -1 (i.e., freeSlot was set), it goes to LAB_004eba04 with the matched entry.
                    // If iVar4 == -1 (no free slot found yet), it breaks out of the loop. Then after the loop, if freeSlot != -1, goes to label at LAB_004eb9ed.
                    // So the logic is: if we find a match, and we have previously found a free slot, use the match (but why check freeSlot?).
                    // Actually iVar4 in the inner scope is actually i (the loop index), not freeSlot. That is confusing.
                    // Let's re-read: iVar5 = -1 initially; iVar4 = 0 ... inside loop: if (match) { if (iVar4 != -1) { ... goto } else break; }
                    // iVar4 is the loop index, which is never -1. So the condition iVar4 != -1 is always true. So the break is dead code? 
                    // This is likely a decompiler artifact. In reality, the original code probably had:
                    // if (match) { if (freeSlot != -1) { ... goto } else break; }
                    // But the decompiler confused freeSlot (iVar5) with iVar4 (loop index). So we'll assume the correct logic:
                    // If match found and there is a free slot (freeSlot != -1), return the matched entry? That doesn't make sense.
                    // Actually typical algorithm: search for key match. If found, return that entry. If not, allocate a new entry in a free slot (if any) or after the last used.
                    // The original: iVar5 is free slot index (set when piVar3[5] low short == 0). If match found, then if iVar5 != -1, it returns the matched entry? That seems wrong.
                    // Let's re-read the decompiled carefully:
                    // iVar5 = -1;  (free slot)
                    // iVar4 = 0;  (loop counter)
                    // if (-1 < DAT_010c2328) {  // if count >=0
                    //   piVar3 = (int *)&DAT_011947e8;
                    //   do {
                    //     if (match condition) {
                    //       if (iVar4 != -1) {  // this is always true because iVar4 starts at 0
                    //         puVar2 = &DAT_011947e8 + iVar4 * 4;
                    //         goto LAB_004eba04;
                    //       }
                    //       break;
                    //     }
                    //     if ((iVar5 == -1) && ((short)piVar3[5] == 0)) {
                    //       iVar5 = iVar4;  // set free slot
                    //     }
                    //     iVar4 = iVar4 + 1;
                    //     piVar3 = piVar3 + 8;
                    //   } while (iVar4 <= DAT_010c2328);
                    //   if (iVar5 != -1) goto LAB_004eb9ed;  // use free slot
                    // }
                    // So the code: if match found, always goto LAB_004eba04 with the matched entry (because iVar4 != -1 always true). The break is never reached.
                    // But then after the loop, if free slot exists, use it; else increment count and use new slot.
                    // Actually the match condition returns immediately, so the free slot check only applies if no match found.
                    // So the logic is: search for exact match. If found, return that entry. Else, if a free slot was found (with low short 0), reuse it. Else use a new slot after the last used.
                    // That makes sense.
                }
                // else: match found but no free slot? Actually freeSlot is set if a free slot was found earlier in the loop.
                // If we found match and freeSlot != -1, we return the matched entry (because the free slot is not used). 
                // If we found match and freeSlot == -1, we also return the matched entry (but the code does break and then goes to LAB_004eb9ed only if freeSlot != -1? 
                // Wait the break occurs only if match found and iVar4 != -1 (always true) leads to goto, so break never executes. So the match always returns via goto.
                // Thus the free slot is only used for insertion when no match.
                // That seems correct.
            }
            // Check for free slot
            if (freeSlot == -1 && (entry->freeFlag == 0)) {
                freeSlot = i;
            }
        }
    }

    if (freeSlot == -1) {
        // No free slot, allocate new
        freeSlot = s_entryCount;
        s_entryCount = freeSlot + 1;
    }

    ResourceCacheEntry* result = &s_entries[freeSlot];
    // Initialize new entry
    result->key[0] = 0;
    result->key[1] = 0;
    result->key[2] = 0;
    result->key[3] = 0;
    // (the rest is zeroed by the next line? Actually the original zeroes 8 bytes at result+something:
    // *puVar2 = 0; (&DAT_011947f0)[iVar5 * 4] = 0; etc. - that zeroes the first 16 bytes? Wait:
    // *puVar2 = 0; puVar2 is undefined8*, writing 8 bytes (key[0] and key[1]).
    // (&DAT_011947f0)[iVar5 * 4] => offset from DAT_011947e8: DAT_011947f0 is DAT_011947e8 + 8? Actually DAT_011947f0 might be another array?
    // Decompiler: puVar2 = &DAT_011947e8 + iVar5 * 4; then *puVar2 = 0; (&DAT_011947f0)[iVar5 * 4] = 0; (&DAT_011947f8)[iVar5 * 4] = 0; *(undefined8 *)(&DAT_01194800 + iVar5 * 0x10) = 0;
    // These are likely zeroing the 4 fields: first 8 bytes, next 8 bytes, etc. But it's messy. I'll simplify: zero the whole entry.
    // The original zeroes fields in multiple steps; we can just set all to 0.

    result->key[2] = 0;
    result->key[3] = 0;
    result->freeFlag = 0;
    result->refCount = 0;
    result->unk0 = 0;
    result->unk1 = 0;

LAB_004eba04:
    if (addRef) {
        result->refCount++;      // increment short at offset 0x18 (puVar2+3 as short)
    }
    // Copy the key from input
    result->key[0] = key[0];
    result->key[1] = key[1];
    result->key[2] = key[2];
    result->key[3] = key[3];
    // Increment allocation count (short at offset 0x14)
    result->freeFlag++;    // Actually the original increments a short at offset0x14, which is freeFlag. That seems odd: freeFlag is used to indicate free (0). Now they increment it? Maybe it's a use count or allocation count.
    // The original: *(short *)((int)puVar2 + 0x14) = *(short *)((int)puVar2 + 0x14) + 1;
    // So they increment the short at offset 0x14. That is the same as freeFlag. So freeFlag is actually a usage count? But earlier they used (short)piVar3[5]==0 to find free slots. So after allocation, freeFlag becomes non-zero.
    // So freeFlag actually indicates whether the slot is free (0) or allocated (>0). So we treat it as an allocation counter.
    return result;
}