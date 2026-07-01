// FUNC_NAME: ResourceData::ResourceData
int __thiscall ResourceData::ResourceData(ResourceData *this, void *resource, int sizeInfo) {
    // Call resource initialization function with the resource pointer
    FUN_004d3bc0(resource);
    
    // Store size/type info
    this->field_0x10 = sizeInfo;       // +0x10: size or type identifier
    this->field_0x14 = 0;              // +0x14: reserved
    this->field_0x18 = 0;              // +0x18: reserved
    this->field_0x1c = 0;              // +0x1c: reserved
    this->field_0x20 = 0;              // +0x20: reserved
    this->field_0x24 = 0;              // +0x24: reserved
    this->field_0x28 = 0;              // +0x28: reserved
    
    return this;
}