# nuvoton-series

Nuvoton MCU/MPU Series Standard Driver Repository for RT-Thread.

## Architecture Code-Graphs (架構代碼依賴圖)

專案已依據處理器核心架構分類建立完整的架構依賴圖、外設驅動調用鏈與 SCons 建置圖（**已排除 `Scripts/NuMicroSDK` 重複鏡像目錄**）：

- [code-graph/README.md](code-graph/README.md): 全域架構家族對照表、SCons 根調度圖與排除規則說明
- [code-graph/cortex-m.md](code-graph/cortex-m.md): Cortex-M (M2354, M2L31, M3331, M3351, M460, M480, M5531, CMSIS) 分層依賴圖
- [code-graph/cortex-a.md](code-graph/cortex-a.md): Cortex-A (MA35D1 雙核 A35 + M4 子核、異質跨核 IPC、WHC、HWSEM) 分層依賴圖
- [code-graph/arm9.md](code-graph/arm9.md): ARM9 (N9H30, NUC980 內建 DDR、雙 EMAC、2D/JPEG) 分層依賴圖
- [code-graph/generate_code_graph.py](code-graph/generate_code_graph.py): 自動掃描代碼庫依賴與檔案統計腳本
