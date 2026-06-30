// FUNC_NAME: BoneFrameTree::BoneFrameTree
void __thiscall BoneFrameTree::BoneFrameTree(BoneFrameTree *this, ModelSkeleton *skeletonData, uint32_t flags, BoneResource *resource)
{
  bool success;
  Allocator *allocator;
  int boneCount;
  int *nodeArray;
  int *indexArray;
  int currentIndex;
  int iVar9; // offset into resource data
  int iVar10; // counter for root entries
  int childCount;
  int index; // index from FindBoneIndex
  int boneLookup;
  int *resourceData; // pointer to raw data

  // Base class constructor (vtable + basic init)
  BaseClass::BaseClass(this, skeletonData, flags, resource);

  // Set vtable for this class
  this->vtable = &BoneFrameTree_VTABLE;

  // Store resource pointer at offset +0x34
  this->resource = resource;
  this->rootBoneIndex = 0;   // +0x36
  this->nodeArray = nullptr; // +0x38
  this->boneIndices = nullptr; // +0x37

  if (resource != nullptr) {
    // Query resource for skeleton data: return a pointer to the data structure
    success = (resource->vtable->getData(0xae986323, &resourceData) != 0);
    if (success && (skeletonData != nullptr)) {
      // Get bone count offset from skeleton data
      this->rootBoneIndex = *(int *)(skeletonData + 0x218); // +0x36
      if (this->rootBoneIndex != 0) {
        // Get total number of bones from this object
        boneCount = *(int *)(this + 0x1c); // e.g., this->totalBones
        this->rootBoneIndex = boneCount;   // +0x36 = total bones (maybe copy?)

        // Allocate array for bone indices (sized by totalBones * 4)
        allocator = GetAllocator();
        int allocParams[3] = {2, 4, 0}; // alignment, type flags
        indexArray = (int *)allocator->Allocate(boneCount * 4, &allocParams);
        this->indexArray = indexArray; // +0x38

        // Allocate array of bone nodes (each 32 bytes)
        boneCount = *(int *)(this + 0x1c);
        allocator = GetAllocator();
        struct NodeAllocInfo { int zero; } nodeAlloc;
        nodeArray = (int *)allocator->Allocate(boneCount << 5, &nodeAlloc); // boneCount * 32
        this->nodeArray = nodeArray; // +0x37

        // Process resource data: structure at resourceData (offset +0x18 = number of entries, +0x20 = array of ints)
        int *data = resourceData;
        int numEntries = *(int *)(data + 0x18);
        int currentBone = 0; // index into nodeArray
        int dataOffset = 0;   // offset into data array (each entry advances by 4)

        for (iVar10 = 0; iVar10 < numEntries; iVar10++) {
          // Read first entry of the group (size or type)
          int entry = *(int *)(data + 0x20 + dataOffset * 4);

          // Create a new root node for this group
          int nodeBase = currentBone * 0x20;
          int *node = (int *)(this->nodeArray + nodeBase);
          node[0] = 0; node[1] = 0; node[2] = 0; node[3] = 0; // first 16 bytes zero
          node[4] = 0; node[5] = 0; node[6] = 0; node[7] = 0; // next 16 bytes zero
          *(uint16_t *)(node + 0x3) = 0; // at offset +0x0c (3 ints in) = 0
          *(uint8_t *)(node + 0x0e) = (uint8_t)entry; // size/type at +0x0e
          *(uint8_t *)(node + 0x0f) = 1; // flag: root node

          // Look up bone index from skeleton data
          boneLookup = this->rootBoneIndex;
          if ((boneLookup != 0) && (*(int *)(boneLookup + 0x70) != 0)) {
            // Compute bone index from skeleton hierarchy
            index = *(int *)(*(int *)(*(int *)(boneLookup + 0x70) + 0x1c) + 0x14 + *(short *)(boneLookup + 0x74) * 0x18);
            index = FindBoneIndex(*(int *)(data + 0x20 + (dataOffset + 1) * 4), index);
            if ((index == -1) || (index = *(int *)(index + 0x10 + index * 0x14), index == -1)) {
              index = -1;
            }
          } else {
            index = -1;
          }
          *(int *)(this->indexArray + currentBone * 4) = index;

          currentBone++;
          dataOffset += 2; // advance by two entries (first is root, second is children? Actually inner loop)

          // If entry > 1, it has children (entry-1 many)
          if (entry > 1) {
            int remainingChildren = entry - 1; // number of child nodes to create
            int childOffset = currentBone; // offset for children nodes

            for (int j = 0; j < remainingChildren; j++) {
              int childBase = childOffset * 0x20;
              int *childNode = (int *)(this->nodeArray + childBase);
              // Clear child node
              childNode[0] = 0; childNode[1] = 0; childNode[2] = 0; childNode[3] = 0;
              childNode[4] = 0; childNode[5] = 0; childNode[6] = 0; childNode[7] = 0;
              // Set child index (low byte)
              *(uint8_t *)(childNode + 0x1c) = (uint8_t)childOffset; // at +0x1c (7 ints) = index?
              *(uint16_t *)(childNode + 0x03) = 0; // short at +0x0c = 0
              *(uint8_t *)(childNode + 0x0f) = 2; // flag: child node

              // Look up bone index for this child
              boneLookup = this->rootBoneIndex;
              if ((boneLookup != 0) && (*(int *)(boneLookup + 0x70) != 0)) {
                index = *(int *)(*(int *)(*(int *)(boneLookup + 0x70) + 0x1c) + 0x14 + *(short *)(boneLookup + 0x74) * 0x18);
                childIndex = FindBoneIndex(*(int *)(data + 0x20 + (dataOffset + j) * 4), index);
                if ((childIndex == -1) || (childIndex = *(int *)(childIndex + 0x10 + childIndex * 0x14), childIndex == -1)) {
                  childIndex = -1;
                }
              } else {
                childIndex = -1;
              }
              *(int *)(this->indexArray + childOffset * 4) = childIndex;

              childOffset++;
            }
            currentBone = childOffset; // advance currentBone past children
            dataOffset += remainingChildren; // advance data offset by children
          }
        }

        // Set total bones count (difference between current position and start)
        *(uint16_t *)(this->nodeArray + 0x1c) = (uint16_t)(*(uint8_t *)(this + 0x36) - numEntries);
        Finalize(); // FUN_00519b60
        return;
      }
    }
  }

  // Error: set error flag at +0x04
  this->flags |= 1; // offset +0x04
}