// FUNC_NAME: selectDataTable
void __fastcall selectDataTable(int tableIndex, char flag)
{
    switch (tableIndex)
    {
    case 1:
        g_selectedDataTable = &DAT_01214f70; // +0x0: base data table A
        break;
    case 2:
        if (flag == 0)
            g_selectedDataTable = &DAT_01215740; // +0x0: base data table B (alternate 0)
        else
            g_selectedDataTable = &DAT_01210250; // +0x0: base data table B (alternate 1)
        break;
    case 3:
        if (flag == 0)
            g_selectedDataTable = &DAT_01217750; // +0x0: base data table C (alternate 0)
        else
            g_selectedDataTable = &DAT_01216980; // +0x0: base data table C (alternate 1)
        break;
    case 4:
        g_selectedDataTable = &DAT_01211290; // +0x0: base data table D
        break;
    default:
        g_selectedDataTable = &DAT_012115f0; // +0x0: fallback base data table
        break;
    }
}