// FUNC_NAME: GenomeFilter::updateFilter

void __thiscall GenomeFilter::updateFilter(GenomeFilter *this)
{
    char stateFlag;
    uint randomIndex;
    int filterResult;
    int data;
    void *param1;
    void *param2;
    int localFilterResult;
    int freeCount;
    uint freeCount2;
    int *genomeFilter;
    int filterHeader[17];
    int dummy;
    int local_5c;
    ulonglong delayTicks;
    int local_50;
    uint local_4c;
    undefined4 local_48;
    
    // If frames processed < 100, possibly apply probabilistic delay
    if (*(uint *)(this + 0x84) < 100) {
        // Pseudo-random index from static tables
        randomIndex = DAT_010c2678 & DAT_012054b4;  // static counter and mask
        DAT_012054b4 = DAT_012054b4 + 1;            // increment static counter
        // Compute delay ticks from a precomputed waveform table
        delayTicks = (ulonglong)ROUND(*(float *)(&DAT_010c2680 + randomIndex * 4) * DAT_00d5e288);
        if (*(uint *)(this + 0x84) < (uint)delayTicks) {
            return; // Early exit if not enough frames
        }
    }
    // Default values
    randomIndex = 0;
    localFilterResult = 0;
    local_50 = 0;
    local_4c = 0;
    local_48 = 0;
    genomeFilter = (int *)0x0;
    delayTicks = delayTicks & 0xffffffff00000000;  // Clear low 32 bits (unused)
    
    // Branch based on whether an external object (e.g., a loaded sample) exists
    if (*(int *)(this + 0x54) == 0) {
        // No external object: create 'Busy' genome filter
        genomeFilter = (int *)FUN_006b9dc0(this + 0xa0, "Genome Filter (Busy)");
        localFilterResult = FUN_006b9be0(*(undefined4 *)(this + 0x88), *(undefined4 *)(this + 0x8c));
    }
    else {
        // There is an external object: retrieve its translation or state
        data = FUN_006b0ee0(*(int *)(this + 0x54));
        if (((data != 0) &&
             // Check some manager state and a flag via two helper functions
             (int iVar4 = FUN_006b4860(), iVar4 == 0)) &&
            (stateFlag = FUN_006b4440(), stateFlag != '\0')) {
            // Store a 64-bit reference from the external object
            delayTicks = CONCAT44(delayTicks._4_4_, *(undefined4 *)(data + 0x40));
            stateFlag = FUN_006b2ed0();
            if (stateFlag == '\0') {
                // Idle state: use filter data at +0xb0
                genomeFilter = (int *)FUN_006b9dc0(this + 0xb0, "Genome Filter (Idle)");
                param1 = *(undefined4 *)(this + 0x90);
                param2 = *(undefined4 *)(this + 0x94);
            }
            else {
                // Busy state: use filter data at +0xa0
                genomeFilter = (int *)FUN_006b9dc0(this + 0xa0, "Genome Filter (Busy)");
                param1 = *(undefined4 *)(this + 0x88);
                param2 = *(undefined4 *)(this + 0x8c);
            }
            local_5c = FUN_006b9be0(param1, param2);
            localFilterResult = local_5c;
            // If there is a callback (or pending data), push additional filter data
            if (*(int *)(this + 0x60) != 0) {
                FUN_006b9e60(data, &local_50, &local_5c);
                localFilterResult = local_5c;
                randomIndex = local_4c;
            }
        }
    }
    // Free any previously queued elements (release the temporary filters)
    int freeIdx = 0;
    if (randomIndex != 0) {
        do {
            FUN_00791250(this, 0xffffffff);
            freeIdx = freeIdx + 1;
        } while (freeIdx < randomIndex);
    }
    // If a genome filter was created and has results
    if ((genomeFilter != (int *)0x0) && (localFilterResult != 0)) {
        // Check a flag at bit 1 of offset +0x80 and delayTicks
        if (((*(uint *)(this + 0x80) >> 1 & 1) == 0) || ((uint)delayTicks == 0)) {
            // Normal execution: just run the filter
            FUN_006b9d40(genomeFilter, localFilterResult);
        }
        else {
            // Modify filter header to include a delay
            int *dst = filterHeader;
            int *src = genomeFilter;
            for (int i = 0x11; i != 0; i--) {
                *dst++ = *src++;
            }
            filterHeader[0] = 4;   // possibly command code for delay
            filterHeader[1] = 4;   // unused?
            filterHeader[2] = (int)delayTicks; // delay value
            filterHeader[3] = 0;
            FUN_006b9d40(filterHeader, localFilterResult);
            FUN_0078ecf0();  // flush or sync after delay insertion
        }
    }
    // Free temporary data if allocated
    if (local_50 != 0) {
        FUN_009c8f10(local_50);
    }
    return;
}