// FUNC_NAME: AggregateData::mergeFrom
// Function address: 0x00570790
// Role: Merges data from this object into a target buffer. Iterates over an array of value pairs, calls
//       FUN_00573200 to add each pair. Then, if a single-entry field is present, calls FUN_005732d0.
//       Finally, ensures the target's maximum field (offset +0x34) is at least this object's +0x20 field.
// Structure fields:
//   this+0x20 : uint - some maximum or capacity value
//   this+0x24 : int  - count of pairs in array
//   this+0x28 : int* - pointer to array of pointers to pairs (each pair: two uint32 values)
//   this+0x34 : int  - non-zero if a single-entry is present
//   this+0x38 : uint - value for the single-entry
//   target+0x34: uint - field updated to the max of current and this+0x20

void __thiscall AggregateData::mergeFrom(int target)
{
    int i;
    int *pairPtr;
    int pairCount = *(int *)(this + 0x24);
    int *pairArray = *(int **)(this + 0x28);

    if (pairCount > 0) {
        for (i = 0; i < pairCount; i++) {
            pairPtr = *(int **)(pairArray + i);
            // Call to process a pair (two uint32 values)
            FUN_00573200(target, *pairPtr, *(pairPtr + 1));
        }
    }

    if (*(int *)(this + 0x34) != 0) {
        // Call to process a single-entry (handle + data)
        FUN_005732d0(target, *(int *)(this + 0x38), *(int *)(this + 0x34));
    }

    if (*(unsigned int *)(target + 0x34) < *(unsigned int *)(this + 0x20)) {
        *(unsigned int *)(target + 0x34) = *(unsigned int *)(this + 0x20);
    }
}