// FUNC_NAME: SymbolTable::addLocalVariable
// Function at 0x0063de90: Adds a new local variable entry to the symbol table, with a limit of 200.
// Uses implicit this pointer (EAX). Fields:
//   this+0x1c -> m_pTable (pointer to internal symbol table structure)
//   m_pTable+0x34 -> m_localVarCount (current number of local variables)
//   m_pTable+0x2b8 -> m_localVarArray (array of handles/symbols)

void __thiscall SymbolTable::addLocalVariable(undefined4 param_1, int param_2)
{
    int *pTable = *(int **)(this + 0x1c);
    int currentCount = *(int *)(pTable + 0x34);
    
    // Check if adding a new variable would exceed the limit
    if (200 < currentCount + 1 + param_2) {
        undefined4 errorMsg = FUN_00636c00("too many %s (limit=%d)", "local variables", 200);
        FUN_00638b80(errorMsg);
    }
    
    // Allocate or retrieve the symbol handle for the given parameter
    undefined4 symbolHandle = FUN_0063de40(param_1);
    
    // Store the handle in the array at the appropriate index
    int newIndex = currentCount + param_2;
    *(undefined4 *)((int)pTable + 0x2b8 + newIndex * 4) = symbolHandle;
}