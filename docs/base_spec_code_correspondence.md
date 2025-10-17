# baseフォルダ仕様書とl_mat.c対応関係分析

## 文書情報
- 分析日: 2025-10-16
- 対象ファイル: base/emfng_l_mat.c
- 仕様書: base/emfng-aa0-50-a/D0emfng-aa0-50-a.doc
- 補助資料: base/emfng-aa0-50-a/document/

## 1. ファイル概要

### 1.1 ソースコード基本情報
- **ファイル名**: emfng_l_mat.c
- **モジュールID**: emfng-pa000-5000-a-M4
- **著作権**: Toyota Motor Corporation
- **目的**: 触媒劣化故障診断部 (Catalyst Deterioration Diagnosis)
- **規格対応**: OBD関連 AND (4気筒 OR 6気筒)

### 1.2 コンパイル環境
- コンパイラ: GHS Version 201355-201400
- ターゲット: R9コンパイル用 (MK32_ID = 0x00000040)

## 2. 主要機能マッピング

### 2.1 触媒診断機能
emfng_l_mat.cは、エンジンの触媒劣化診断を行う主要なモジュールです。

#### コード上の実装箇所:
- **初期化処理**: emfng_pwon() (行544-551)
- **パターン判定**: emfng_mfptn_ann_u1u1u1() (行563-892)
- **65ms周期処理**: emfng_65msl() (行894-1579)
- **16ms周期処理**: emfng_16msl() (行1581-1695)

### 2.2 カウンタ管理

#### 触媒劣化カウンタ (行268-297):
```c
u2 u2g_emfng_ekldmfae;       // EM触媒劣化異常回数累積値
u1 u1g_emfng_ecdmfaotbnk[2]; // 最新気筒別OT触媒異常回数カウンタ
u1 u1g_emfng_ecdmfaot;       // OT触媒劣化全気筒カウンタ
u2 u2g_emfng_ecdmfaoti;      // 触媒劣化全気筒カウンタ
u2 u2g_emfng_ecdmfae2;       // EM触媒劣化全気筒カウンタ
```

これらは仕様書の「触媒劣化診断カウンタ」セクションに対応すると推定されます。

### 2.3 回転数カウンタ (行278-283)

```c
u2 u2g_emfng_ecjmfot;        // OT触媒異常の累積回転数カウンタ
u2 u2g_emfng_ecjmfoti;       // OT触媒アイドル異常の累積回転数カウンタ
u2 u2g_emfng_ecjmfem;        // EM触媒異常の累積回転数カウンタ
u2 u2g_emfng_ekldmfot;       // OT触媒異常回数累積値
```

### 2.4 気筒別カウンタ (行292-297)

```c
u1 u1g_emfng_ecdmfem[u1g_EJCC_NCYL];    // EM触媒劣化気筒別カウンタ
u2 u2g_emfng_ecdmfem2[u1g_EJCC_NCYL];   // EM触媒劣化気筒別カウンタ
u1 u1g_emfng_ecdmfemi[u1g_EJCC_NCYL];   // 触媒劣化気筒別カウンタ
u2 u2g_emfng_ecmfot;                    // 複数気筒カウンタ
u1 u1g_emfng_ecdmfw[u1g_EJCC_NCYL/2];   // 気筒対カウンタ
```

## 3. 関数構造解析

### 3.1 主要関数一覧

| 関数名 | タイミング | 目的 |
|--------|-----------|------|
| emfng_pwon() | 電源ON時 | 初期化処理 |
| emfng_mfptn_ann_u1u1u1() | TDC時 | 触媒パターン判定 |
| emfng_65msl() | 65ms周期 | 触媒診断メイン処理 |
| emfng_16msl() | 16ms周期 | 触媒劣化監視処理 |
| emfng_drvclchg() | 駆動状態変化時 | ドライブサイクル変更処理 |

### 3.2 診断判定関数

#### OT触媒診断 (行2267-2544):
```c
static void emfng_ot_detect_ptptptpt(
    u1 *ptt_xumfot,      // OT触媒正常判定信号
    u1 *ptt_xdmfot,      // OT触媒異常判定信号
    u1 *ptt_xhmfoton,    // OT触媒によるMIL点灯要求信号
    u1 *ptt_xhmfotoff    // OT触媒によるMIL点灯解除要求信号
);
```

#### EM触媒診断 (行2546-2792):
```c
static void emfng_em_detect_u2ptpt(
    u2 u2t_cdmfae2,      // 全気筒の触媒劣化カウンタ
    u1 *ptt_xdmfem,      // EM触媒異常検出信号
    u1 *ptt_xumfem       // EM触媒正常判定保持信号
);
```

### 3.3 デュアルインジェクタ対応 (条件付きコンパイル)

```c
#if (JEEFI == u1g_EJCC_DUAL) && (JEHIPFI_E == u1g_EJCC_USE)
static void emfng_di_detect_ptpt();   // DI異常検出
static void emfng_pfi_detect_ptpt();  // PFI異常検出
#endif
```

## 4. 条件コンパイルスイッチ分析

### 4.1 主要スイッチ

| スイッチ | 意味 | 影響範囲 |
|----------|------|----------|
| JEOOBD | 欧州OBD有効 | 欧州OBD規制対応コード |
| JENCYL | 気筒数 | 4気筒/6気筒切り替え |
| JEMFDTC_D | 触媒OBD DTC有効 | DTC出力機能 |
| JETCORE_D | t-CORE対応有効 | テストモード対応 |
| JEOBDUDS_D | OBDonUDS対応有効 | UDS通信対応 |
| JEMFFC | OT触媒異常時FC有効 | フェールセーフ制御 |
| JEMFHOUKI | 米国法規 | 米国OBD規制対応 |

### 4.2 コンパイルスイッチとコードセクション

```
JEOOBD == USE の場合:
  - 欧州OBD関連RAM処理 (行465-477, 508-531)
  - 1000rev内の積算値計算 (行305-312)
  
JENCYL == 6CYL の場合:
  - 6気筒専用変数定義 (行404-407, 415-418, etc.)
  - 気筒対判定ロジック (行3971-3998)
```

## 5. データ構造とメモリ管理

### 5.1 バックアップRAM

コードは不揮発性メモリ（バックアップRAM）を使用してデータを保存します:

```c
// バックアップRAM-ID配列 (行398-463)
static volatile const u2 u2s_ECDMFEMTV_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFEMMNTL_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFEMMXTL_U2_ID[u1g_EJCC_NCYL];
```

アクセスには以下の関数を使用:
- `s4g_ememctr_read()`: 読み出し
- `s4g_ememctr_write()`: 書き込み

### 5.2 フラグ構造体

```c
stflag8 stg_emfng_flag1;  // グローバルフラグ変数構造体(16msl,65msl,drvclchg)
stflag8 stg_emfng_flag2;  // デュアルINJ用
stflag8 stg_emfng_flag3;  // t-CORE対応用

static stflag8 sts_emfng_flagi1;  // クランク時用内部フラグ
static stflag8 sts_emfng_flagi2;  // 65msl,drvclchg用
static stflag8 sts_emfng_flagi3;  // 65msl用
```

## 6. 外部インターフェース

### 6.1 インクルードファイルと依存関係

主要な依存モジュール:
- `espc/ejcc.h`: エンジン仕様定義
- `emf/emfcc.h`: 触媒診断共通定義
- `emf/emfcnt.h`: 触媒カウンタ定義
- `emf/emfne.h`: 回転数判定定義
- `eserv/emem/ememctr.h`: メモリ制御

### 6.2 公開関数 (他モジュールから呼び出し可能)

```c
void emfng_pwon(void);                              // 電源ON初期化
void emfng_mfptn_ann_u1u1u1(u1, u1, u1);           // パターン判定
void emfng_65msl(void);                             // 65ms周期処理
void emfng_16msl(void);                             // 16ms周期処理
void emfng_drvclchg(void);                          // ドライブサイクル変更
```

### 6.3 公開変数 (他モジュールからアクセス可能)

```c
u2 u2g_emfng_ekldmfae;       // EM触媒劣化異常回数累積値
u1 u1g_emfng_ecdmfaotbnk[2]; // 最新気筒別OT触媒異常回数カウンタ
u1 u1g_emfng_ecdmfaot;       // OT触媒劣化全気筒カウンタ
// ... (その他多数)
```

## 7. 処理フロー概要

### 7.1 初期化フロー (emfng_pwon)

```
電源ON
  ↓
計算値変数の算出 (emfng_mcr_cal)
  ↓
初期化完了
```

### 7.2 周期処理フロー (emfng_65msl)

```
65ms周期起動
  ↓
診断情報クリア要求チェック
  ↓
OT触媒異常検出判定
  ↓
EM触媒異常検出判定
  ↓
カウンタ更新
  ↓
バックアップRAM更新
  ↓
MODE$06対応データ計算
  ↓
処理完了
```

### 7.3 パターン判定フロー (emfng_mfptn_ann_u1u1u1)

```
TDCタイミング
  ↓
回転数カウンタ更新
  ↓
触媒劣化カウンタ判定
  ↓
気筒別カウンタ更新
  ↓
粗さ判定処理
  ↓
処理完了
```

## 8. 仕様書との対応関係推定

### 8.1 仕様書セクション推定マッピング

基本的なドキュメント構造（D0emfng-aa0-50-a.doc）に基づく推定:

| 仕様書想定セクション | コード実装箇所 | 行番号範囲 |
|---------------------|--------------|-----------|
| 機能概要・目的 | ヘッダコメント | 1-11 |
| システム構成図 | インクルードファイル | 13-101 |
| 定数定義 | マクロ定数定義 | 243-260 |
| 変数仕様 | グローバル変数定義 | 266-297 |
| 初期化処理 | emfng_pwon() | 544-551 |
| メイン診断処理 | emfng_65msl() | 894-1579 |
| タイミング処理 | emfng_mfptn_ann_u1u1u1() | 563-892 |
| 異常判定ロジック | emfng_ot_detect_ptptptpt() | 2267-2544 |
| カウンタ処理 | emfng_mf_cnt_u1u1() | 2090-2265 |
| MODE06対応 | emfng_emode06_cal() | 3967-4145 |

### 8.2 補助資料との関連

- **ロジック変更シート_ver9.06_emfng-aa0.xlsx**: 
  - ロジック変更履歴とバージョン管理
  - コード変更点の追跡に使用

- **参照元チェックシート_ver2.07_emfng-aa0-50-a.xlsx**:
  - 変数・関数の参照関係チェック
  - モジュール間依存関係の検証

## 9. コード品質と保守性

### 9.1 コーディング規約準拠

- Toyota Motor Corporationの著作権表示
- 詳細な関数ヘッダコメント（目的、タイミング、引数、戻り値）
- 変数の詳細なコメント（LSB、単位、目的）

### 9.2 保守性の特徴

- 条件コンパイルによる柔軟な機種対応
- バックアップRAMによるデータ永続化
- MODE06対応による診断情報の標準化
- 明確な関数分割による可読性確保

### 9.3 注意点

- ファイルエンコーディング: Non-ISO extended-ASCII (日本語コメント含む)
- コメント内の特殊文字: Shift-JIS等の日本語文字コード使用
- 条件コンパイルの複雑性: 多数のマクロによる分岐

## 10. 今後の解析推奨事項

### 10.1 詳細分析が必要な領域

1. **仕様書の詳細読解**: D0emfng-aa0-50-a.docの内容を完全に解析
2. **Excelシートの活用**: ロジック変更シートと参照元チェックシートの詳細確認
3. **他のソースファイルとの関連**: emfng_4_c_mat.c, emfng_6_c_mat.cとの関係性
4. **ヘッダファイル分析**: emfng.hの詳細構造把握

### 10.2 検証が必要な仮説

1. MODE06データの計算方法と仕様書記載内容の一致性
2. 気筒数による処理分岐の完全性
3. バックアップRAMのデータ整合性保証メカニズム
4. 異常判定閾値の設定根拠

### 10.3 追加ドキュメント作成提案

1. 詳細シーケンス図（UML）
2. 状態遷移図
3. データフロー図
4. エラーハンドリング仕様

## 11. まとめ

emfng_l_mat.cは、Toyota Motor Corporationの触媒劣化診断システムの中核を成すモジュールです。約4400行のコードで以下の機能を実装しています:

- **触媒劣化診断**: OT触媒とEM触媒の両方に対応
- **多気筒対応**: 4気筒/6気筒エンジンに対応
- **規格準拠**: OBD、OBD2、欧州OBD等の各種規制に対応
- **データ永続化**: バックアップRAMによる診断データ保存
- **標準化**: MODE06による診断情報の標準化出力

仕様書との完全な対応関係を確立するには、D0emfng-aa0-50-a.docの詳細な読解が必要ですが、コードの構造から以下が確認できます:

- 明確な関数分割と責任分離
- 詳細なコメントによる自己文書化
- 条件コンパイルによる柔軟な機種対応
- 標準的な組み込みソフトウェア設計パターンの採用

---

**注**: このドキュメントは、ソースコードの静的解析に基づいて作成されています。仕様書（.doc/.docx）の内容との詳細な突合は、ドキュメント解析ツールによる抽出後に行う必要があります。
