// FUNC_NAME: SortUtils::merge_sort_three_way
void merge_sort_three_way(int* start, int* mid, int* end, void* comparator) {
    int elementCount = (end - start) / 3; // Actually 12 bytes per element, so pointer arithmetic is in bytes?
    int count = (end - start) / 12;
    if (count > 40) {
        count++;
        int chunkSize = (count + ((count >> 31) & 7)) >> 3; // Essentially count/8, for positive count
        int* leftEnd = start + chunkSize * 12;             // end of first chunk (8 elements)
        int* rightStart = mid - chunkSize * 12;            // start of chunk before mid
        int* rightEnd = mid + chunkSize * 12;              // end of chunk after mid
        int* thirdStart = end - chunkSize * 24;            // start of third chunk (two chunks before end)
        int* thirdMid = end - chunkSize * 12;              // mid of third chunk
        int* thirdEnd = end;                               // end of third chunk
        
        // Merge first two chunks [start..leftEnd) and [leftEnd..thirdStart?) Wait, need to follow original
        // Actually original calls:
        // FUN_0081ae50(param_1, iVar1, iVar2*0x18+param_1, param_4)
        // iVar2*0x18 = chunkSize*24, so that is start, leftEnd, leftEnd+chunkSize*12? No.
        // Let's recalc: iVar1 = chunkSize*12 + start (start chunk)
        // iVar2*0x18 + param_1 = chunkSize*24 + start (end of two chunks)
        // So first merge: [start, leftEnd) and [leftEnd, leftEnd+chunkSize*12) -- merges two consecutive chunks of 8 each.
        merge_runs(start, leftEnd, leftEnd + chunkSize * 12, comparator);
        
        // Second merge: [mid-chunkSize*12, mid) and [mid, mid+chunkSize*12)
        merge_runs(mid - chunkSize * 12, mid, mid + chunkSize * 12, comparator);
        
        // Third merge: [end-chunkSize*24, end-chunkSize*12) and [end-chunkSize*12, end)
        merge_runs(end - chunkSize * 24, end - chunkSize * 12, end, comparator);
        
        // Final merge of the middle overlapping regions: [leftEnd, mid) and [mid, end-chunkSize*12)
        merge_runs(leftEnd, mid, end - chunkSize * 12, comparator);
    } else {
        // Small run: direct merge
        merge_runs(start, mid, end, comparator);
    }
}