// FUNC_NAME: EventScheduler::getValidEventAtTime
int __thiscall EventScheduler::getValidEventAtTime(void* this, float time) {
    // +0x0c: float startTime (filter minimum time)
    // +0x10: char isDisabled (flag, if non-zero, all events are blocked)
    float* thisStart = (float*)((char*)this + 0x0c);
    char* disabled = (char*)this + 0x10;

    // Try primary schedule lookup
    int* primaryEvent = (int*)EventScheduler::findPrimaryEvent(time); // FUN_006f4f80
    if (primaryEvent == nullptr || time < *(float*)(primaryEvent + 8) || time < *thisStart || *disabled != '\0') {
        // Primary failed; try secondary schedule lookup
        int* secondaryEvent = (int*)EventScheduler::findSecondaryEvent(time); // FUN_006f4d60
        if (secondaryEvent == nullptr || time < *(float*)(secondaryEvent + 8) || time < *thisStart || *disabled != '\0') {
            return 0; // No valid event
        }
        return (int)secondaryEvent;
    }
    // Primary succeeded; return primary (but note: function actually uses secondary result if primary condition is false? Wait logic: condition above is if primary fails, then we enter and try secondary. If primary condition is false (i.e. primary is valid), then we skip the if body and return primary? No, see decompiled: the if condition is the OR combination that means 'invalid'. So if primary is valid, the first part of AND is false, so entire AND is false, so we skip the if and iVar1 is the result of the second call (which is still executed because it's part of the condition? Actually the decompiled shows iVar1 = FUN_006f4d60(param_3) inside the second part of the AND, so the second call is always executed. The condition evaluates both sides? In C, && short-circuits? But in decompiler, it might not. Let's re-examine: The decompiled code shows:
    iVar1 = FUN_006f4f80(param_3);
    if (((((iVar1 == 0) || (param_3 < *(float *)(iVar1 + 8))) || (param_3 < *(float *)(param_1 + 0xc))) || (*(char *)(param_1 + 0x10) != '\0')) &&
        (((iVar1 = FUN_006f4d60(param_3), iVar1 == 0) || (param_3 < *(float *)(iVar1 + 8))) || ((param_3 < *(float *)(param_1 + 0xc) || (*(char *)(param_1 + 0x10) != '\0'))))) {
        iVar1 = 0;
    }
    return iVar1;
In C, the && is short-circuit: if the first part (the conditions on the first call) is false (i.e. valid), then it does not evaluate the second part? Wait: If the first part is false, then the entire AND is false, so the if body is not entered, and iVar1 remains what? But note that iVar1 is reassigned inside the second part of the AND condition. Since AND short-circuits, if the first part is false, the second part is not evaluated at all. That means iVar1 is not reassigned via the second call; it still holds the result from the first call. However, the decompiler shows that the second call is inside the condition. In actual x86, the code likely does evaluate both calls regardless due to the way the branches are compiled? But given the decompiler generated this pattern, it may be that the second call is only evaluated if the first part is true. Let's think: The condition for entering the if block is: (firstInvalid) && (secondInvalid). If firstInvalid is false (meaning first is valid), then the entire condition is false, and the if block is skipped. In that case, we never call the second function, and we return the first result. So the function actually returns the first event if it's valid; otherwise returns the second event if it's valid; otherwise returns 0. But the code above only returns second event in the case where first is invalid and second is valid. It never returns first event because after the if, iVar1 is still the first result? Wait: If first is valid, we skip the if, and return iVar1 which is the first result. So yes, it returns the first event if first is valid. But the decompiled code shows the second call inside the condition: that code is executed only when first is invalid (first part true). So the reconstruction should reflect that: first try primary; if primary fails, try secondary; if secondary fails, return 0; else return secondary; if primary valid, return primary. So the logic is:
    primary = FindPrimary(time);
    if (primary valid) return primary;
    secondary = FindSecondary(time);
    if (secondary valid) return secondary;
    return 0;
But note the conditions in the decompiler combine them with AND. The actual assembly probably does the short-circuit correctly. So the reconstructed code should be simple: check primary, if not valid, check secondary. So I'll implement that.

Also param_2 is unused, so I ignore it.
*/

    // +0x08 in event struct: float endTime? (time must be >= eventStart? Actually condition is param_3 < *(float*)(iVar1+8), meaning time is less than field at +8. So field at +8 is a bound that time must be >=. Could be start time? But then they also check time < this+0xc, which is a filter minimum. So event+8 is likely eventEnd? Actually if time < event+8 is invalid, then time must be >= event+8, so event+8 is a lower bound? More logically, event+8 could be startTime and event+? : but there's only one field checked. So event+8 is probably the start time of the event (time must be >= start). The condition 'param_3 < event+8' means time is before start, invalid. And this+0xc is another minimum time (maybe the current schedule window start). So time must be >= both the event's start and the schedule window start. And disabled flag must be clear. So I'll name accordingly.
    return 0; // Placeholder; actual logic below
}

// Actually, let me rewrite the function body correctly.

int* primaryEvent = (int*)EventScheduler::findPrimaryEvent(time); // FUN_006f4f80
if (primaryEvent != nullptr && time >= *(float*)((char*)primaryEvent + 8) && time >= *thisStart && *disabled == '\0') {
    return (int)primaryEvent;
}
int* secondaryEvent = (int*)EventScheduler::findSecondaryEvent(time); // FUN_006f4d60
if (secondaryEvent != nullptr && time >= *(float*)((char*)secondaryEvent + 8) && time >= *thisStart && *disabled == '\0') {
    return (int)secondaryEvent;
}
return 0;