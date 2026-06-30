// FUNC_NAME: EAList::incrementSize
// Function at 0x00441540: Increments the size/count of a list container, throwing an exception if the count is a sentinel value (0xAAAAAAA) indicating the list is already locked or too long.
// This is part of EA's STL-like container debugging (debug build).

void __thiscall EAList::incrementSize()
{
	// Check if current count is the sentinel for 'too long' (0xAAAAAAA)
	if (*(int*)(this + 0x1C) == 0xAAAAAAA)
	{
		// Prepare exception message buffer (size 0x10)
		uint32_t maxLength = 0xF;          // Max string length
		uint32_t flags = 0;                 // Construction flags
		uint32_t local_3c = local_3c & 0xFFFFFF00; // Truncate for alignment

		// Build exception text
		FUN_0043f9f0("list<T> too long", 0x10);
		
		char* errorTxt = "unknown";
		void** vtablePtr = &PTR_FUN_00da9810; // VTable for exception
		uint32_t local_4 = 0xF;
		uint32_t local_8 = 0;
		uint32_t local_18 = local_18 & 0xFFFFFF00;
		
		// Initialize exception object with an error code of -1 (0xFFFFFFFF)
		FUN_0043eeb0(local_40, 0, 0xFFFFFFFF);
		
		// Update vtable pointer for actual exception type
		vtablePtr = &PTR_FUN_00da9828;
		
		// Call global exception handler if registered
		if (DAT_0113d3a0 != (code*)0x0)
		{
			(*DAT_0113d3a0)(&vtablePtr);
		}
		
		// Invoke throw via function pointer in vtable
		(*(code*)vtablePtr[2])();
		
		// Standard throw mechanism
		std::_Throw((exception*)&vtablePtr);
		
		// Cleanup temporary allocations
		vtablePtr = &PTR_FUN_00da9810;
		if (0xF < local_4)
		{
			FUN_009c8eb0(local_18);
		}
		local_8 = 0;
		local_18 = local_18 & 0xFFFFFF00;
		local_4 = 0xF;
		vtablePtr = &PTR_LAB_00e31044;
		if (0xF < maxLength)
		{
			FUN_009c8eb0(local_3c);
		}
	}
	
	// Increment the count at offset +0x1C
	*(int*)(this + 0x1C) = *(int*)(this + 0x1C) + 1;
	return;
}