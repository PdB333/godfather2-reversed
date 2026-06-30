// FUNC_NAME: WebBrowser::processNavigationResult
void WebBrowser::processNavigationResult(int param_1, char *url, int param_3, char *responseData)
{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  char *pcVar12;
  float local_23c;
  float local_238;
  float local_234;
  float local_230;
  float local_22c;
  float local_228;
  float local_224;
  undefined4 local_220;
  undefined1 local_21c;
  char cStack_21b;
  undefined1 local_21a;
  undefined2 local_218;
  undefined1 local_216;
  float *local_214;
  float *local_210;
  char local_20c [8];
  float *local_204;
  float *local_200;
  undefined1 local_1fc;
  undefined1 local_1fb;
  undefined2 local_1f8;
  undefined1 local_1f6;
  float *local_1f4;
  float *local_1f0;
  undefined1 local_1ec;
  undefined1 local_1eb;
  undefined2 local_1e8;
  undefined1 local_1e6;
  float *local_1e4;
  float *local_1e0;
  undefined1 local_1dc;
  undefined1 local_1db;
  undefined2 local_1d8;
  undefined1 local_1d6;
  float *local_1d4;
  float *local_1d0;
  float local_1cc;
  undefined2 local_1c8;
  undefined1 local_1c6;
  float *local_1c4;
  float *local_1c0;
  undefined1 local_1bc;
  undefined1 local_1bb;
  undefined2 local_1b8;
  undefined1 local_1b6;
  float *local_1b4;
  float *local_1b0;
  undefined1 local_1ac;
  undefined1 local_1ab;
  undefined2 local_1a8;
  undefined1 local_1a6;
  float *local_1a4;
  float *local_1a0;
  undefined1 local_19c;
  undefined1 local_19b;
  undefined2 local_198;
  undefined1 local_196;
  float *local_194;
  float *local_190;
  undefined1 local_18c;
  undefined1 local_18b;
  char acStack_189 [7];
  char acStack_182 [249];
  char cStack_89;
  undefined4 local_88;
  
  pcVar4 = _strstr(responseData,"ok");
  if (((pcVar4 == (char *)0x0) || (pcVar4 + 2 == (char *)0x0)) || (pcVar4[2] != '1')) {
    // Initialize bounding box values from global constants
    local_238 = DAT_00e449b8; // minY
    local_23c = DAT_00e449b8; // minX
    local_230 = DAT_00e449b4; // maxY
    local_234 = DAT_00e449b4; // maxX
    
    local_88._0_1_ = '\0';
    
    // Copy URL to local buffer
    pcVar4 = url;
    do {
      cVar3 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar3 != '\0');
    pcVar12 = &cStack_89;
    do {
      pcVar10 = pcVar12 + 1;
      pcVar12 = pcVar12 + 1;
    } while (*pcVar10 != '\0');
    pcVar10 = url;
    for (uVar7 = (uint)((int)pcVar4 - (int)url) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar12 = pcVar12 + 4;
    }
    pcVar5 = (char *)&local_88;
    for (uVar7 = (int)pcVar4 - (int)url & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar12 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar12 = pcVar12 + 1;
    }
    
    // Extract directory path from URL (strip filename)
    do {
      cVar3 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar3 != '\0');
    for (pcVar5 = pcVar5 + (-1 - ((int)&local_88 + 1)); -1 < (int)pcVar5; pcVar5 = pcVar5 + -1) {
      if (*(char *)((int)&local_88 + (int)pcVar5) == '/') {
        *(char *)((int)&local_88 + (int)(pcVar5 + 1)) = '\0';
        break;
      }
    }
    
    // Parse image data from response - look for up to 10 images
    bVar1 = false;
    local_22c = 1.4013e-45; // image counter
    do {
      // Build search key like "img0", "img1", etc.
      local_220 = DAT_00e3eb64;
      _local_21c = CONCAT11(local_22c._0_1_ + '0',(char)DAT_00e3eb68);
      pcVar4 = (char *)&local_220;
      local_21a = DAT_00e3eb6a;
      do {
        cVar3 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar3 != '\0');
      
      pcVar12 = _strstr(responseData,(char *)&local_220);
      if ((pcVar12 == (char *)0x0) ||
         (pcVar12 + ((int)pcVar4 - ((int)&local_220 + 1)) == (char *)0x0)) break;
      
      // Extract image filename
      _strncpy((char *)&DAT_01223cc0,pcVar12 + ((int)pcVar4 - ((int)&local_220 + 1)),0x40);
      DAT_01223cff = 0;
      pcVar4 = _strchr((char *)&DAT_01223cc0,0x26);
      if (pcVar4 != (char *)0x0) {
        *pcVar4 = '\0';
      }
      
      // Build full path: directory + image filename
      acStack_189[1] = 0;
      pcVar4 = (char *)&local_88;
      do {
        cVar3 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar3 != '\0');
      uVar7 = (int)pcVar4 - (int)&local_88;
      pcVar4 = acStack_189;
      do {
        pcVar12 = pcVar4 + 1;
        pcVar4 = pcVar4 + 1;
      } while (*pcVar12 != '\0');
      pcVar12 = (char *)&local_88;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar4 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar4 = pcVar4 + 4;
      }
      for (uVar7 = uVar7 & 3; pcVar10 = (char *)&DAT_01223cc0, uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar4 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar4 = pcVar4 + 1;
      }
      do {
        pcVar4 = pcVar10;
        pcVar10 = pcVar4 + 1;
      } while (*pcVar4 != '\0');
      pcVar12 = acStack_189;
      do {
        pcVar10 = pcVar12 + 1;
        pcVar12 = pcVar12 + 1;
      } while (*pcVar10 != '\0');
      pcVar10 = (char *)&DAT_01223cc0;
      for (uVar7 = (uint)(pcVar4 + -0x1223cbf) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar7 = (uint)(pcVar4 + -0x1223cbf) & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar12 = pcVar12 + 1;
      }
      
      // Load the image
      cVar3 = FUN_005a03a0(); // loadImageFromFile
      if (cVar3 == '\0') break;
      
      iVar9 = (int)(float)local_1d0; // image width
      iVar11 = (int)local_1cc; // image height
      if (iVar9 == 0) {
        iVar11 = 0;
LAB_005c8f11:
        bVar2 = 0;
      }
      else {
        if ((iVar9 < 1) || (iVar11 < 1)) goto LAB_005c8f11;
        bVar2 = 1;
      }
      bVar1 = (bool)(bVar1 | bVar2);
      
      // Update bounding box
      pcVar4 = acStack_189;
      do {
        pcVar12 = pcVar4 + 1;
        pcVar4 = pcVar4 + 1;
      } while (*pcVar12 != '\0');
      *(undefined **)pcVar4 = PTR_LAB_00e3eb6c;
      FUN_0059fa10(); // drawImage
      
      pcVar4 = acStack_189;
      do {
        pcVar4 = pcVar4 + 1;
      } while (*pcVar4 != '\0');
      pcVar4[-1] = 'y';
      
      if (local_228 < local_23c) {
        local_23c = local_228;
      }
      FUN_0059fa10(); // drawImage
      if (local_224 < local_238) {
        local_238 = local_224;
      }
      if (local_234 < (float)iVar9 + local_228) {
        local_234 = (float)iVar9 + local_228;
      }
      if (local_230 < (float)iVar11 + local_224) {
        local_230 = (float)iVar11 + local_224;
      }
      local_22c = (float)((int)local_22c + 1);
    } while ((int)local_22c < 10);
    
    if (bVar1) {
      // Apply offsets from URL parameters
      FUN_005a04a0("gotoOk",0);
      pcVar4 = _strstr(responseData,"_l=");
      if ((pcVar4 == (char *)0x0) || (pcVar4 == (char *)0xfffffffd)) {
        iVar9 = 0;
      }
      else {
        iVar9 = FUN_005c71e0(); // parseInt
      }
      local_23c = (float)iVar9 + local_23c;
      
      pcVar4 = _strstr(responseData,"_t=");
      if ((pcVar4 == (char *)0x0) || (pcVar4 == (char *)0xfffffffd)) {
        iVar9 = 0;
      }
      else {
        iVar9 = FUN_005c71e0(); // parseInt
      }
      local_238 = (float)iVar9 + local_238;
      
      pcVar4 = _strstr(responseData,"_r=");
      if ((pcVar4 == (char *)0x0) || (pcVar4 == (char *)0xfffffffd)) {
        iVar9 = 0;
      }
      else {
        iVar9 = FUN_005c71e0(); // parseInt
      }
      local_234 = (float)iVar9 + local_234;
      
      pcVar4 = _strstr(responseData,"_b=");
      if ((pcVar4 == (char *)0x0) || (pcVar4 == (char *)0xfffffffd)) {
        iVar9 = 0;
      }
      else {
        iVar9 = FUN_005c71e0(); // parseInt
      }
      local_230 = (float)iVar9 + local_230;
      
      // Calculate final dimensions
      local_228 = local_234 - local_23c;
      local_22c = local_230 - local_238;
      
      // Enforce minimum size
      if (local_228 < DAT_00e2b1a4) {
        local_234 = local_23c + DAT_00e2b1a4;
        local_228 = DAT_00e2b1a4;
      }
      if (local_22c < DAT_00e2b1a4) {
        local_230 = local_238 + DAT_00e2b1a4;
        local_22c = DAT_00e2b1a4;
      }
      
      // Build and execute rendering commands for each image
      local_218 = DAT_00e3eb88;
      local_216 = PTR_LAB_00e3eb8a._0_1_;
      local_214 = &local_23c;
      local_204 = &local_23c;
      local_210 = &local_238;
      local_200 = &local_238;
      local_1f8 = DAT_00e3eb90;
      local_1f6 = DAT_00e3eb92;
      local_1f4 = &local_234;
      local_1f0 = &local_238;
      local_1e6 = PTR_LAB_00e3eb96._0_1_;
      local_1e8 = DAT_00e3eb94;
      local_1e4 = &local_23c;
      local_1d4 = &local_23c;
      local_1e0 = &local_238;
      local_1d0 = &local_238;
      local_1c6 = DAT_00e3eb9e;
      local_1c8 = DAT_00e3eb9c;
      local_1c4 = &local_234;
      local_1c0 = &local_238;
      local_1b8 = DAT_00e3eba0;
      local_1b6 = PTR_LAB_00e3eba2._0_1_;
      local_1b4 = &local_23c;
      local_1b0 = &local_230;
      local_1a4 = &local_23c;
      local_1a0 = &local_230;
      local_198 = DAT_00e3eba8;
      local_20c[0] = '\0';
      local_20c[1] = 0;
      local_20c[4] = 't';
      local_20c[5] = '\0';
      local_20c[6] = 0;
      local_1fc = 1;
      local_1fb = 0;
      local_1ec = 0;
      local_1eb = 0;
      local_1dc = 0;
      local_1db = 1;
      local_1d8 = 0x6d;
      local_1d6 = 0;
      local_1cc = (float)CONCAT22(local_1cc._2_2_,0x101);
      local_1bc = 0;
      local_1bb = 1;
      local_1ac = 0;
      local_1ab = 0;
      local_1a8 = 0x62;
      local_1a6 = 0;
      local_19c = 1;
      local_19b = 0;
      local_196 = DAT_00e3ebaa;
      local_194 = &local_234;
      local_190 = &local_230;
      local_18c = 0;
      local_18b = 0;
      pcVar4 = local_20c + 1;
      local_224 = 1.26117e-44;
      
      // Render each image with proper positioning
      do {
        acStack_189[1] = 0;
        pcVar12 = (char *)&local_88;
        do {
          cVar3 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar3 != '\0');
        uVar7 = (int)pcVar12 - (int)&local_88;
        pcVar12 = acStack_189;
        do {
          pcVar10 = pcVar12 + 1;
          pcVar12 = pcVar12 + 1;
        } while (*pcVar10 != '\0');
        pcVar10 = (char *)&local_88;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar12 = pcVar12 + 4;
        }
        pcVar5 = pcVar4 + -0xd;
        for (uVar7 = uVar7 & 3; pcVar6 = pcVar5, uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar12 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar12 = pcVar12 + 1;
        }
        do {
          cVar3 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar3 != '\0');
        uVar7 = (int)pcVar6 - (int)pcVar5;
        pcVar12 = acStack_189;
        do {
          pcVar10 = pcVar12 + 1;
          pcVar12 = pcVar12 + 1;
        } while (*pcVar10 != '\0');
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar12 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar12 = pcVar12 + 1;
        }
        pcVar12 = acStack_189;
        do {
          pcVar10 = pcVar12;
          pcVar12 = pcVar10 + 1;
        } while (pcVar10[1] != '\0');
        *(undefined2 *)(pcVar10 + 1) = DAT_00e3ebac;
        pcVar10[3] = DAT_00e3ebae;
        pcVar12 = acStack_189 + 1;
        do {
          pcVar10 = pcVar12;
          pcVar12 = pcVar10 + 1;
        } while (*pcVar10 != '\0');
        if (pcVar4[-1] != '\0') {
          *pcVar10 = '\0';
          pcVar5 = acStack_189;
          do {
            pcVar6 = pcVar5;
            pcVar5 = pcVar6 + 1;
          } while (pcVar6[1] != '\0');
          *(undefined4 *)(pcVar6 + 1) = s_width_00e3ebb0._0_4_;
          *(undefined2 *)(pcVar6 + 5) = s_width_00e3ebb0._4_2_;
          FUN_0059ecb0(); // renderText
        }
        if (*pcVar4 != '\0') {
          *pcVar10 = '\0';
          pcVar5 = acStack_189;
          do {
            pcVar6 = pcVar5;
            pcVar5 = pcVar6 + 1;
          } while (pcVar6[1] != '\0');
          *(undefined4 *)(pcVar6 + 1) = s_height_00e3ebb8._0_4_;
          *(undefined2 *)(pcVar6 + 5) = s_height_00e3ebb8._4_2_;
          pcVar6[7] = s_height_00e3ebb8[6];
          FUN_0059ecb0(); // renderText
        }
        *pcVar10 = 'x';
        *pcVar12 = '\0';
        FUN_0059ecb0(); // renderText
        *pcVar10 = 'y';
        *pcVar12 = '\0';
        FUN_0059ecb0(); // renderText
        pcVar4 = pcVar4 + 0x10;
        local_224 = (float)((int)local_224 + -1);
      } while (local_224 != 0.0);
    }
  }
  return;
}