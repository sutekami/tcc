更新：2024/02/19

## 📖 勉強会とは
後期の半年間を使って、一つの課題に取り組んでもらいます！  
この課題がゼミの**期末レポート**となっていますので、頑張りましょう！  
取り組んでもらう課題は、**OpenGL** を使った **TCC** の作成です。  
言語は **C++** (C言語)で、テキストエディターは **Microsoft Visual Studio 2019** となります。（VSCodeではないよ！）  

基本的に勉強会担当の者が課題について説明をし、それに沿ったことを行っていただきますが、  
勉強会の中で**説明されていない部分**を自主的に作成してもらって結構です！  
また毎回の課題を遂行するためにサンプルコードを何度か掲示することがありますが、  
そのコードを**改良**したり、またサンプルを使用せずに**オリジナル**のコーディングをしていただいても結構です！（むしろそっちの方がいいかも）  

最終的に**皆さん自身の開発物**となりますので、ぜひ頑張っていきましょう！

<details><summary>こんな感じの作ってもらいます！（サンプル）</summary>
  
![sampleTCC2D](https://github.com/sutekami/tcc/blob/master/sample_tcc_2d.jpg)  
![sampeTCC3D](https://github.com/sutekami/tcc/blob/master/sample_tcc_3d.jpg)
</details>

> **OpenGLとは？**  
> OpenGL（Open Graphics Library）とは、ハードウェアの持つ3次元コンピュータグラフィックス（3DCG）関連の演算機能をソフトウェアから呼び出すための規約を定めたインターフェース（API）標準の一つ。もともと旧Silicon Graphics社（SGI）が自社ソフトウェア向けに開発していたIRIS GLをオープン化したもので、業界団体のクロノス・グループ（Khronos Group）が仕様の標準化を行っている。
> 
> [OpenGLとは - 意味をわかりやすく](https://e-words.jp/w/OpenGL.html)

<br>

## 🏃 進め方について
勉強会ごとに課題を設定します。  
基本的には勉強会中にその課題を終わるようにし、終わらなかった場合は各自行ってきてください。  
また、勉強会ごとに課題は設定しますが、先に進みたいという方は**遠慮なく**進んでいただいて構いません！  
ただ、最低限**設定された課題**は必ず完了させてください。  
<br>
そして**ゼミの最終日**に、皆さんの制作物の**デモ**をしてもらうことになると思います！

<br>

## 🗓️スケジュール
<details><summary>1. ２次元TCCのサイクルを作成する</summary>

![1](https://github.com/sutekami/tcc/blob/master/schedules_images/1.jpg)
</details>

<details><summary>2. 平行移動、２次元TCCのサイクルを複製する</summary>

![2-1](https://github.com/sutekami/tcc/blob/master/schedules_images/2-1.jpg)
![2-2](https://github.com/sutekami/tcc/blob/master/schedules_images/2-2.jpg)
</details>

<details><summary>3. サイクルとサイクルを接続する</summary>

![3-1](https://github.com/sutekami/tcc/blob/master/schedules_images/3-1.jpg)
![3-2](https://github.com/sutekami/tcc/blob/master/schedules_images/3-2.jpg)
</details>

<details><summary>4. ２次元TCCの座標を表示する</summary>

![4](https://github.com/sutekami/tcc/blob/master/schedules_images/4.jpg)
</details>

<details><summary>5. ３次元TCCのサイクルを作成する、回転、３次元TCCのサイクルを複製する</summary>

![5-1](https://github.com/sutekami/tcc/blob/master/schedules_images/5-1.jpg)
![5-2](https://github.com/sutekami/tcc/blob/master/schedules_images/5-2.jpg)
![5-3](https://github.com/sutekami/tcc/blob/master/schedules_images/5-3.jpg)
</details>

<details><summary>6. サイクルとサイクルを接続する</summary>

![6-1](https://github.com/sutekami/tcc/blob/master/schedules_images/6-1.jpg)
![6-2](https://github.com/sutekami/tcc/blob/master/schedules_images/6-2.jpg)
</details>

<details><summary>7. ３次元TCCの座標を表示する</summary>

![7](https://github.com/sutekami/tcc/blob/master/schedules_images/7.jpg)
</details>

## ✏️ レポート執筆
前年から特に変更がなければ、**レポートの執筆**もすることになっています。  
以下に書き方、その他留意点を記載しますので、各自確認のほどお願いします！  

### 書き方
- 表紙と目次のページを作成する
- 背景や目的を含める
- 図は多めに入れる（図番号と図の説明も必ず加える）
- 関数の説明などを入れる（必要があれば加える）
- 勉強会の範囲外の部分は説明する（構造体、曲線、影、マウス操作など）

<br>

## 🖨️ 最終レポートの提出方法
最終レポートでは以下の2点を用意します。
- 執筆したレポートのPDF
- **編集してきたC++ファイルを、Cファイルに変更したソースコード**

### ⌨️ C++をCファイルに変更する手順
1. C++ファイルのソースコードをコピー(`ctrl + A` + `ctrl + C`)
2. メモ帳やVSCode等のテキストエディタを新規で開き、上記でコピーした内容をペースト(`ctrl + V`)
3. 保存をし(`ctrl + s` or `ctrl + shift + s`)、拡張子を`.c`と設定
4. 保存！

<br>

## 👩‍💻環境構築
勉強会では、最新版ではなく、**VScode2019**を使用します。したがって、面倒ですがインストールをお願いします。  
また、ダウンロードしたファイルは**初期設定でのパスの設定**に使用するので、適切な場所に保存するようにしてください。  
初期設定では freeglut の場合のみ記載しましたが、 glewも同様に設定可能です。

1. VScode2019のインストール  
[https://visualstudio.microsoft.com/ja/vs/older-downloads/](https://visualstudio.microsoft.com/ja/vs/older-downloads/)
2. freeglut_MSVC-3.0.0-2.mp.zip のダウンロード  
[https://www.transmissionzero.co.uk/software/freeglut-devel/](https://www.transmissionzero.co.uk/software/freeglut-devel/)
3. glew-2.1.0-win32.zip のダウンロード  
[https://glew.sourceforge.net/](https://glew.sourceforge.net/)

---
自分用  
初期設定の方法を書く
### 勉強会形態
- 連絡方法
  - **Slack**
  - **Discord**
