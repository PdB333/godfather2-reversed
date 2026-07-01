// FUNC_NAME: DebugManager::createDebugEntry
void __thiscall DebugManager::createDebugEntry(char type, int data1, int data2)
{
    char isDebugEnabled = FUN_00481640(); // checkDebugEnabled()
    if (isDebugEnabled)
    {
        DebugEntry* entry = reinterpret_cast<DebugEntry*>(FUN_009c8e50(0x48)); // allocateMemory(72 bytes)
        if (entry == nullptr)
        {
            entry = nullptr;
        }
        else
        {
            entry = FUN_0089bca0(this); // DebugEntry::constructor(this) – constructs at the allocated memory
        }
        entry->field_0x38 = type;  // +0x38: debug entry type/flag
        entry->field_0x3c = data1; // +0x3c: param3 (maybe x-coordinate)
        entry->field_0x40 = data2; // +0x40: param4 (maybe y-coordinate)
        FUN_00481690(entry);       // registerDebugEntry(entry) – adds to a debug list
    }
}