// FUNC_NAME: ParameterTable::setFloat(int id, float value)
// Address: 0x00487a50
// Role: Inserts or updates a float entry in a global parameter table. 
// The table is a fixed-size array of (id, float value) pairs, 8 bytes each.
// Only the first insertion is supported; subsequent calls only update existing entries.
// Likely used for global configuration or game setting overrides.

static int g_entryCount = 0;           // DAT_01205430
static struct Entry {
    int   id;                          // +0x00
    float value;                       // +0x04
} g_entries[?];                        // DAT_01163d40, each 8 bytes

void __fastcall ParameterTable::setFloat(void* thisPtr, int id, float value)
{
    int count = g_entryCount;
    int i = 0;

    if (count != 0) {
        do {
            if (g_entries[i].id == id) {
                g_entries[i].value = value;
                break;
            }
            i++;
        } while (i < count);
    }

    // Only add if the table was completely empty before the loop
    if (count == 0) {
        g_entryCount = 1;
        g_entries[0].id    = id;
        g_entries[0].value = value;
    }
}