# LINE POP 2

## 組員

- 112820045 曾怡瑄
- 111820017 陳嘉祥

## 專案簡介

本專案使用 PTSD Framework 與 C++ 製作 LINE POP 2 風格的 2D 三消遊戲。玩家可以在首頁選擇關卡，進入關卡後以滑動方式交換相鄰方塊，形成三個以上相同方塊連線後消除，並透過掉落、補位、連鎖、特殊方塊與道具完成關卡目標。

目前版本已完成第 1 到第 10 關可玩流程，包含：

- 開始畫面與首頁關卡地圖
- 第 1 到第 10 關入口與關卡資料
- 滑動交換相鄰方塊
- 三消、連鎖消除與方塊掉落
- 特殊方塊與特殊方塊組合
- 餅乾障礙物
- Hammer、Magic Stick、Magic Glove 三種道具
- Cheat Mode
- 通關、失敗、暫停與設定頁面
- 方塊交換與掉落的平滑移動動畫

第 11、12 關素材保留，但目前沒有開放為可進入關卡。

## 用 CLion 編譯

這份專案建議直接用 CLion 開啟專案根目錄編譯，不需要另外提供平台專用執行檔。

基本步驟：

1. 用 CLion 選擇 `Open`。
2. 打開本專案資料夾。
3. 等 CLion 載入 CMake。
4. 選擇 `LINEPOP2` target。
5. 按 Build 或 Run。

詳細說明見：

```text
README_CLION.md
```

## 用終端機編譯

```bash
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release --target LINEPOP2
cd cmake-build-release
./LINEPOP2
```

CMake 會優先使用專案內的 `PTSD` 與其 bundled dependencies，不需要額外下載 PTSD。
遊戲圖片、字型與 BGM 會直接從專案內的 `Resources` 資料夾讀取。

## 交給別人時要注意

可以直接壓縮傳給別人，不一定要放 GitHub。請壓縮完整專案資料夾，但不要包含本機編譯產物或 CLion 快取：

```text
不要包含：
cmake-build-*/
build/
.idea/
dist/
```

這些資料夾裡可能有你電腦上的絕對路徑，別人拿到後容易無法執行。對方應該用自己的 CLion 重新載入 CMake、Build、Run。
