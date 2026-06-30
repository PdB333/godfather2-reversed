// FUNC_NAME: getControlMapping
// Address: 0x006066e0
// Role: Retrieves two mapped values from a control mapping table based on index and modifier shift.
// Table entries are 0x38 bytes each; offset +0x0c contains flags (bit 0 = use shift on values).
// Values at +0x02 and +0x04 are ushorts; if shift flag is set, they are right-shifted by (shiftParam & 0x1f)
// and clamped to minimum 1. The result is stored in the output pointers passed in ESI and EDI registers.

struct ControlMappingEntry {
    char pad0[0x02];
    unsigned short value1;      // +0x02
    unsigned short value2;      // +0x04
    char pad1[0x06];
    unsigned char flags;        // +0x0c (bit 0 indicates use shift)
    // Total size 0x38
};

static ControlMappingEntry s_controlMappingTable[0x1000] = {};   // at DAT_011a0f28

// Note: Index passed in EAX, shiftParam on stack, output pointers in ESI and EDI registers.
void __fastcall getControlMapping(unsigned int index, unsigned char shiftParam, unsigned short *outVal1_esi, unsigned short *outVal2_edi)
{
    ControlMappingEntry *entry;
    
    if (index < 0x1000) {
        entry = &s_controlMappingTable[index];
    } else {
        entry = (ControlMappingEntry *)0x0;
    }
    
    // Original code assumes entry is valid (no null check)
    if (entry->flags & 1) {
        // Shift values by (shiftParam & 0x1f), with a minimum of 1
        unsigned short temp;
        temp = entry->value1 >> (shiftParam & 0x1f);
        if (temp == 0) {
            temp = 1;
        }
        *outVal1_esi = temp;
        
        temp = entry->value2 >> (shiftParam & 0x1f);
        if (temp == 0) {
            temp = 1;
        }
        *outVal2_edi = temp;
    } else {
        *outVal1_esi = entry->value1;
        *outVal2_edi = entry->value2;
    }
}