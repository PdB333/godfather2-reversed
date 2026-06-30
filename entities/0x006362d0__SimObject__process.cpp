// FUNC_NAME: SimObject::process
// Address: 0x006362d0
// Role: Core update/process method for SimObject with recursion depth checking and child processing.

void __thiscall SimObject::process(SimObject* thisObj, int param2, uint param3)
{
    ushort depth;
    int ret;

    // Increment recursion depth
    thisObj->recursionDepth++;
    depth = thisObj->recursionDepth;

    if (depth > 199) {
        if (depth == 200) {
            // Stack overflow detected, log error
            FUN_00633920(thisObj, "C stack overflow");
        }
        else if (depth > 224) {
            // Too deep, abort this branch
            FUN_00635a80(param2);  // param2 might be some context? Possibly thisObj?
            return;
        }
    }

    ret = FUN_00636050(param3);  // Check if processing is needed
    if (ret == 0) {
        FUN_00634830(thisObj);  // Process children or sub-objects
    }

    FUN_00636260(thisObj);  // Post-processing step

    // Decrement recursion depth
    thisObj->recursionDepth--;

    // Check if pending updates queue has items; if so, flush
    // Offsets: +0x10 points to a data structure, +0x20 is current count? +0x24 is max?
    if (*(uint*)(*(int*)(thisObj + 0x10) + 0x20) <= *(uint*)(*(int*)(thisObj + 0x10) + 0x24)) {
        FUN_00627360();  // Flush pending updates
    }
}