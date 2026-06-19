# CLion 編譯說明

這份專案可以用同一包原始碼在 macOS 和 Windows 的 CLion 編譯。

## 使用方式

1. 解壓縮專案資料夾。
2. 用 CLion 選擇 `Open`，打開專案根目錄。
3. 等 CLion 載入 CMake。
4. 選擇 `LINEPOP2` target。
5. 按 Build 或 Run。

## 注意事項

- 請保留 `Resources` 資料夾，圖片、字型與 BGM 都在裡面。
- 請保留 `PTSD` 資料夾，專案會優先使用本機 bundled framework，不需要另外下載 PTSD。
- CLion 會直接讀取專案內的 `Resources`，所以 macOS/Windows 都能用同一份 CMake。
- 本專案以原始碼交付、由老師或同學自行編譯為主，不需要另外產生平台專用執行檔。
- 傳給別人前不要包含 `cmake-build-*`、`build`、`.idea`、`dist`，這些是本機產物。

## Windows

Windows 建議使用 CLion 內建的 CMake + MinGW toolchain，或 Visual Studio toolchain。第一次設定 toolchain 後，CLion 重新載入 CMake，再 Build/Run `LINEPOP2` target 即可。

## 常見問題

如果 CMake 顯示 `Target "LINEPOP2" links to SDL2::SDL2main but the target was not found`，代表拿到的是舊版專案或 CLion 還留著舊的 CMake cache。請確認使用新版專案，然後刪除 `cmake-build-debug` 後重新用 CLion 開啟專案。

如果 Build 顯示找不到 `pch.hpp`、`Util/GameObject.hpp` 或 `glm/vec2.hpp`，通常代表 `PTSD` 資料夾沒有完整解壓，或仍在使用舊的 CMake cache。請確認下面三個檔案都存在：

```text
PTSD/include/pch.hpp
PTSD/include/Util/GameObject.hpp
PTSD/lib/glm/glm/vec2.hpp
```

確認後刪除 `cmake-build-debug`，再重新用 CLion 開啟專案。

## macOS

macOS 直接用 CLion 開專案即可，等待 CMake 載入後 Build/Run `LINEPOP2` target。
