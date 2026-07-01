// FUNC_NAME: GameDataTable::getEntry
// Address: 0x007cae60
// Retrieves a pointer to a data entry from a 2D lookup table.
// The table has rows indexed by 'row' and columns indexed by 'col' (unsigned short).
// Returns a pointer to a struct of size 0xC from a data array, or 0 if unavailable.

struct TableEntry {
    // Size 0xC, fields unknown
};

class GameDataTable {
    // +0x14: int m_rowCount                   // Number of rows
    // +0x18: RowEntry* m_rows                  // Array of row descriptors (each 8 bytes)
    // +0x1C: TableEntry* m_dataArray           // Flat array of entries (size 0xC each)
    // +0x30: int m_activeFlag                  // Non-zero if table is active/initialized
public:
    TableEntry* __thiscall getEntry(int row, unsigned short col);
};

// Row descriptor structure (offset +0x18 points to array of these)
struct RowEntry {
    int* m_columnIndices;  // +0x00: Array of indices into m_dataArray (one per column)
    int field_0x4;         // +0x04: Unknown/padding (not used here)
};

TableEntry* __thiscall GameDataTable::getEntry(int row, unsigned short col)
{
    int index = 0;

    // Check if table is active and row is non-negative
    if (m_activeFlag != 0 && row >= 0)
    {
        if (m_rows != 0 && row < m_rowCount)
        {
            // Get the column index array for this row
            // Each row entry is 8 bytes; first 4 bytes is a pointer to column indices
            int* colIndices = *reinterpret_cast<int**>(reinterpret_cast<char*>(m_rows) + row * 8);
            // Fetch the index for the given column
            index = colIndices[col];  // col is promoted to uint for indexing
        }

        // If the data array exists, return the appropriate entry
        if (m_dataArray != 0)
        {
            return &m_dataArray[index];
        }
    }

    return 0;
}