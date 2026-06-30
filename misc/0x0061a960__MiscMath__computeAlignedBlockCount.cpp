// FUNC_NAME: MiscMath::computeAlignedBlockCount
uint __thiscall computeAlignedBlockCount(int blockType, int alignment)
{
	uint blockSize;
	uint divisionFactor;
	uint result;

	if (((blockType == 0x1e) || (blockType == 0x1f)) || 
		((blockType == 0x20 || (((blockType == 0x21 || (blockType == 0x22)) || (blockType == 0x23)))))) {
		// These block types (30-35) use a factor of 4
		divisionFactor = 4;
		blockSize = 4;
	}
	else {
		divisionFactor = 1;
		blockSize = 1;
	}
	if (((blockType == 0x1e) || (blockType == 0x1f)) || 
		((blockType == 0x20 || (((blockType == 0x21 || (blockType == 0x22)) || (blockType == 0x23)))))) {
		// Redundant check, same range
		blockSize = 4;
	}
	else {
		blockSize = 1;
	}
	result = (((blockSize - 1) + (uint)in_EAX) / blockSize) * (((divisionFactor - 1) + alignment) / divisionFactor);
	// Multiply by base cost from table at 0xf15684[blockType] (offsets +0x0, +0xc, +0x18...)
	return (result * *(int *)(0xf15684 + blockType * 12)) >> 3;
}