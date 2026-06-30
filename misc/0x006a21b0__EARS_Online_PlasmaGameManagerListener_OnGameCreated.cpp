// Xbox PDB: EARS::Online::PlasmaGameManagerListener::OnGameCreated
// FUNC_NAME: PatchManager::readPatchManifest
undefined4 __thiscall PatchManager::readPatchManifest(int this, undefined4 pXMLData, undefined4 pVersion)
{
    // local buffers for XML parsing
    uint8_t nodeListBuffer1[124];  // local_29c
    int pNodeList1;                // local_220
    uint8_t attrListBuffer1[64];   // local_218
    int pAttrList1;                // local_1d8
    uint8_t attrListBuffer2[64];   // local_1d4
    int pAttrList2;                // local_194
    uint8_t attrListBuffer3[64];   // local_190
    int pNodeList2;                // local_150
    uint8_t attrListBuffer4[64];   // local_14c
    int pNodeList3;                // local_10c
    uint8_t nodeListBuffer2[264];  // local_108

    // Initialize XML parser context
    initXMLParser();  // FUN_006a37a0

    // Register expected element names
    registerElementName(L"patchTargets");  // FUN_006a39e0
    registerElementName(L"patchTarget");
    registerElementName(L"patch");

    // Register expected attribute names
    registerAttributeName(L"PatchContentId");  // FUN_006a39b0
    registerAttributeName(L"Description");
    registerAttributeName(L"Required");
    registerAttributeName(L"Version");

    // Initialize node lists and attribute lists
    initXMLNodeList(nodeListBuffer2, sizeof(nodeListBuffer2));  // FUN_006a3760
    initXMLNodeList(nodeListBuffer1, sizeof(nodeListBuffer1));
    initXMLAttrList(attrListBuffer3, sizeof(attrListBuffer3));  // FUN_006a3780
    initXMLAttrList(attrListBuffer2, sizeof(attrListBuffer2));
    initXMLAttrList(attrListBuffer1, sizeof(attrListBuffer1));
    initXMLAttrList(attrListBuffer4, sizeof(attrListBuffer4));

    // Set up pointers to member storage (offsets from 'this')
    pNodeList2 = this + 0x8;      // +0x8: pointer to node list (patchTargets?)
    pAttrList2 = this + 0x28;     // +0x28: pointer to attribute list?
    pNodeList3 = this + 0x20;     // +0x20: pointer to node list?
    pAttrList1 = this + 0x10;     // +0x10: pointer to attribute list?
    pAttrList3 = this + 0x18;     // +0x18: pointer to attribute list?

    *(undefined4 *)(this + 0x30) = pVersion;  // +0x30: store version info

    // Perform the actual XML parsing using the provided data
    parseXMLDocument(pXMLData);  // FUN_006a3fb0

    // Return status/result from member at +0x34
    return *(undefined4 *)(this + 0x34);
}