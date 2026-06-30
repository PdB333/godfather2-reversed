// FUNC_NAME: TraceLogger::logCallEntry
void __thiscall TraceLogger::logCallEntry(TraceLogger* this, uint32_t functionId)
{
  // Global trace manager instance at DAT_012234ac
  TraceManager* pManager = g_pTraceManager; // DAT_012234ac

  // Get the vtable from the manager (offset +4 points to vtable pointer?)
  VTable* pVTable = **(VTable***)((uint8_t*)pManager + 4);

  // Local buffer for trace parameters (3 words)
  uint32_t traceBuffer[3] = {0, 0, 0};

  // Step 1: Retrieve the log context from 'this' object
  LogContext* pCtx = this->getLogContext(); // FUN_004adb70(this)

  // Step 2: Call virtual function on the vtable to fill the trace buffer
  // Returns a value (likely a handle/ID)
  uint32_t handle = pVTable->beginLogEntry(pCtx, traceBuffer); // (*(code*)*puVar1)(uVar3, puVar6)

  // Step 3: Finalize the trace entry and get the trace ID
  uint32_t traceId = this->finalizeTraceEntry(handle); // FUN_004adc20(uVar3)

  // Retrieve the third word from the buffer (the return address maybe?)
  uint32_t returnAddr = traceBuffer[2]; // local_4

  // Check if call stack recording is enabled (flag at offset 0x10 of manager)
  if ((uint32_t)__builtin_return_address(0) != 0 && pManager->callStackEnabled) // unaff_retaddr and *(int*)(iVar2+0x10)
  {
    // Push the return address onto the call stack
    uint32_t* pStackNode = pManager->allocateCallStackNode(); // FUN_00621c10(&stack0x00000000)
    if (pStackNode != nullptr)
    {
      *pStackNode = (uint32_t)__builtin_return_address(0); // unaff_retaddr
    }
  }

  // If call stack recording is enabled, allocate a new trace node
  if (pManager->callStackEnabled)
  {
    TraceNode* pNode = pManager->allocateTraceNode(); // FUN_00621690()
    if (pNode != nullptr)
    {
      // Initialize trace node fields
      pNode->field_0x12 = 0; // *(undefined2*)((int)puVar6+0x12) = 0
      pNode->traceId = traceId; // *puVar6 = uVar4
      pNode->basePointer = (uint32_t)__builtin_frame_address(0); // unaff_EBP
      pNode->returnAddr = returnAddr; // puVar6[2] = uVar3
      pNode->field_0x10 = 1; // *(undefined2*)(puVar6+4) = 1 (short at offset 16)
      pNode->functionId = functionId; // puVar6[3] = param_2
    }
  }
}