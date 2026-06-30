// FUN_00482460: PooledObject::PooledObject(byte)
PooledObject::PooledObject(byte allocFlags)
{
	// +0x00: vtable pointer
	this->vtable = &g_PooledObjectVTable; // 0x00e33648
	// +0x04+: base class initialization (likely EAObject or similar)
	EAObjectInit(this); // FUN_0049c640
	// If the low bit of allocFlags is set, the object is heap‑allocated
	// and needs additional registration with the allocator
	if (allocFlags & 1)
	{
		this->registerWithAllocator(); // FUN_009c8eb0
	}
	return this;
}