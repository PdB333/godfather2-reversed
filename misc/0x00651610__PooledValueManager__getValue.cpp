// FUNC_NAME: PooledValueManager::getValue
int PooledValueManager::getValue()
{
	// +0x14: pointer to a node structure
	int* node = *(int**)(this + 0x14);

	// If the 'next' pointer (offset 0x0) is not null, return the stored value (offset 0xC)
	if (node[0] != 0)
	{
		return node[3];
	}

	// If there are no free nodes but the count is positive, allocate a new block
	if (node[3] > 0)
	{
		allocateNewBlock(); // FUN_00651a40 – allocates a new node block, returns head pointer and count via global/stack
		// The allocated node head is stored in local_c, the count in local_8 (Ghidra artifacts).
		// Initialize the node:
		node[0] = local_c; // next pointer
		node[1] = local_c; // prev pointer (same)
		node[2] = local_c; // extra pointer (same)
		node[3] = local_8; // value/count
		return node[3];
	}

	// Otherwise just return the current value (which should be zero or negative)
	return node[3];
}