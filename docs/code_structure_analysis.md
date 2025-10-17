# emfng_l_mat.c コード構造解析レポート

## エグゼクティブサマリー

本ドキュメントは、base/emfng_l_mat.cファイルの詳細なコード構造解析結果を記載しています。このソースファイルは、自動車エンジンの触媒劣化診断機能を実装する重要なモジュールです。

## 1. コードメトリクス

### 1.1 基本統計

- **総行数**: 約4,396行
- **実効コード行数**: 約3,500行（コメント・空行除く）
- **関数数**: 40以上
- **公開関数**: 5個
- **内部関数**: 35個以上
- **グローバル変数**: 20個以上
- **静的変数**: 30個以上

### 1.2 複雑度分析

- **条件コンパイル分岐**: 10種類以上のマクロスイッチ
- **ネスト深度**: 最大5-6レベル
- **関数あたり平均行数**: 約80-100行
- **最大関数サイズ**: 約700行（emfng_65msl）

## 2. アーキテクチャ概要

### 2.1 レイヤー構造

```
┌─────────────────────────────────────┐
│   公開インターフェース層             │
│   (emfng_pwon, emfng_65msl, etc.)  │
├─────────────────────────────────────┤
│   診断ロジック層                     │
│   (検出、判定、カウント)            │
├─────────────────────────────────────┤
│   データ管理層                       │
│   (バックアップRAM、変数管理)       │
├─────────────────────────────────────┤
│   ハードウェア抽象化層              │
│   (メモリアクセス、I/O)             │
└─────────────────────────────────────┘
```

### 2.2 モジュール依存関係

```
emfng_l_mat.c
    ├─ ejcc.h (エンジン仕様定義)
    ├─ emfcc.h (触媒診断共通)
    ├─ emfcnt.h (カウンタ定義)
    ├─ emfne.h (回転数判定)
    ├─ ememctr.h (メモリ制御)
    ├─ wsentivchg.h (OBD関連)
    └─ wmf_fdi.h (DTC関連)
```

## 3. 関数カタログ

### 3.1 初期化・周期処理関数

| 関数名 | アクセス | 行数 | 呼び出し元 | 目的 |
|--------|---------|------|-----------|------|
| emfng_pwon | public | 8 | システム起動時 | 初期化処理 |
| emfng_16msl | public | ~115 | 16ms周期タスク | 短周期監視 |
| emfng_65msl | public | ~685 | 65ms周期タスク | メイン診断処理 |
| emfng_drvclchg | public | ~125 | ドライブサイクル変化時 | サイクル変更処理 |
| emfng_mfptn_ann_u1u1u1 | public | ~330 | TDC割り込み | パターン判定 |

### 3.2 診断判定関数

| 関数名 | アクセス | 行数 | 主要処理 |
|--------|---------|------|---------|
| emfng_ot_detect_ptptptpt | static | ~280 | OT触媒異常検出判定 |
| emfng_em_detect_u2ptpt | static | ~250 | EM触媒異常検出判定 |
| emfng_di_detect_ptpt | static | ~170 | DI異常検出（条件付き） |
| emfng_pfi_detect_ptpt | static | ~170 | PFI異常検出（条件付き） |
| emfng_xottd_cal | static | ~150 | OT触媒異常検出有効信号計算 |

### 3.3 カウンタ管理関数

| 関数名 | アクセス | 行数 | 主要処理 |
|--------|---------|------|---------|
| emfng_mf_cnt_u1u1 | static | ~175 | 触媒カウンタ算出 |
| emfng_cdmfi_reset | static | ~50 | 触媒回数カウンタ（アイドル用）初期化 |
| emfng_mcr_cal | static | ~450 | 計算値変数の算出 |

### 3.4 データ管理関数

| 関数名 | アクセス | 行数 | 主要処理 |
|--------|---------|------|---------|
| emfng_emode06_cal | static | ~180 | MODE$06対応触媒カウンタ計算 |
| emfng_roughjdg_u1u1 | static | ~195 | 粗さ判定関連処理 |
| u1s_emfng_wxreqclr | static | ~130 | 欧州OBD RAM初期化処理 |
| emfng_espdaemclr | static | ~10 | 欧州OBD RAM清掃 |

### 3.5 アクセサ関数群（40個以上）

MODE06対応およびデータ取得のための多数のgetter関数:
- u2g_emfng_ecdmfaemTv(), u2g_emfng_ecdmfaemMntl(), etc.
- u1g_emfng_eocdmfae2mx(), u1g_emfng_eocjrevem(), etc.
- s1g_emfng_eothwem(), s1g_emfng_eothaem(), etc.

## 4. データ構造解析

### 4.1 グローバル変数分類

#### カウンタ変数（14個）
```c
u2 u2g_emfng_ekldmfae;       // EM触媒劣化異常回数累積値
u2 u2g_emfng_ecdmfaoti;      // 触媒劣化全気筒カウンタ
u2 u2g_emfng_ecdmfae2;       // EM触媒劣化全気筒カウンタ
u2 u2g_emfng_ecjmfot;        // OT触媒異常累積回転数カウンタ
u2 u2g_emfng_ecjmfoti;       // OT触媒アイドル異常累積回転数
u2 u2g_emfng_ecjmfem;        // EM触媒異常累積回転数カウンタ
// ... など
```

#### 気筒別配列変数（5個）
```c
u1 u1g_emfng_ecdmfem[u1g_EJCC_NCYL];     // 気筒別カウンタ
u2 u2g_emfng_ecdmfem2[u1g_EJCC_NCYL];    // 気筒別カウンタ2
u1 u1g_emfng_ecdmfemi[u1g_EJCC_NCYL];    // 気筒別カウンタ3
u1 u1g_emfng_ecdmfw[u1g_EJCC_NCYL/2];    // 気筒対カウンタ
u1 u1g_emfng_ecdmfaotbnk[2];             // バンク別カウンタ
```

#### フラグ変数（6個）
```c
stflag8 stg_emfng_flag1;     // グローバルフラグ1
stflag8 stg_emfng_flag2;     // グローバルフラグ2（デュアルINJ用）
stflag8 stg_emfng_flag3;     // グローバルフラグ3（t-CORE用）
static stflag8 sts_emfng_flagi1;  // 内部フラグ1
static stflag8 sts_emfng_flagi2;  // 内部フラグ2
static stflag8 sts_emfng_flagi3;  // 内部フラグ3
```

### 4.2 静的変数分類

#### 診断状態変数（15個）
```c
static u1 u1s_emfng_ecjpmf;         // ゼロクロスカウンタ
static u2 u2s_emfng_ecdtmfwa;       // EM触媒粗さ判定用路上カウンタ
static u1 u1s_emfng_ecxmf1;         // OT触媒異常検出履歴
static u1 u1s_emfng_ecxmf;          // EM触媒異常検出履歴
static u1 u1s_emfng_ecjemrev;       // 初回EM触媒粗さ削除
// ... など
```

#### 欧州OBD用変数（8個、条件付き）
```c
static s4 s4s_emfng_espdaem;        // 1000rev間の車速積算値
static s4 s4s_emfng_eneaem;         // 1000rev間のエンジン回転数積算値
static s4 s4s_emfng_eklsmaem;       // 1000rev間の負荷率積算値
// ... など
```

#### デュアルINJ用変数（10個、条件付き）
```c
static u2 u2s_emfng_ecjmfdi;        // DI側累積回転数カウンタ
static u2 u2s_emfng_ecjmfpfi;       // PFI側累積回転数カウンタ
static u1 u1s_emfng_ecdmfdi[u1g_EJCC_NCYL];   // 気筒別DIカウンタ
static u1 u1s_emfng_ecdmfpfi[u1g_EJCC_NCYL];  // 気筒別PFIカウンタ
// ... など
```

### 4.3 定数配列

#### バックアップRAM ID配列（6種類）
```c
static volatile const u2 u2s_ECDMFEMTV_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFEMMNTL_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFEMMXTL_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFAVTV_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFAVMNTL_U2_ID[u1g_EJCC_NCYL];
static volatile const u2 u2s_ECDMFAVMXTL_U2_ID[u1g_EJCC_NCYL];
```

#### 気筒変換テーブル（6気筒専用、条件付き）
```c
static volatile const u1 u1s_emfng_CYLMODTBL[u1g_EJCC_NCYL];
static volatile const u1 u1s_emfng_CYLWTBL[2][3];
```

## 5. 制御フロー解析

### 5.1 emfng_65msl() メイン処理フロー

```
START
  │
  ├─ 診断情報クリア要求チェック (u1s_emfng_wxreqclr)
  │
  ├─ OT触媒異常検出有効信号計算 (emfng_xottd_cal)
  │
  ├─ OT触媒異常検出判定 (emfng_ot_detect_ptptptpt)
  │   ├─ カウンタ更新
  │   ├─ 閾値判定
  │   └─ MIL点灯判定
  │
  ├─ EM触媒異常検出判定 (emfng_em_detect_u2ptpt)
  │   ├─ カウンタ更新
  │   ├─ 閾値判定
  │   └─ 異常検出
  │
  ├─ DI/PFI異常検出（条件付き）
  │   ├─ emfng_di_detect_ptpt
  │   └─ emfng_pfi_detect_ptpt
  │
  ├─ カウンタ初期化処理 (emfng_cdmfi_reset)
  │
  ├─ 触媒劣化異常カウンタ更新
  │   ├─ OT触媒カウンタ
  │   └─ EM触媒カウンタ
  │
  ├─ バックアップRAM更新
  │   ├─ 欧州OBD RAM（条件付き）
  │   └─ MODE06対応カウンタ
  │
  ├─ DTC出力処理（条件付き）
  │   └─ emfng_wxmf_out
  │
  ├─ MODE06対応データ計算
  │   └─ emfng_emode06_cal
  │
  └─ END
```

### 5.2 emfng_mfptn_ann_u1u1u1() TDC処理フロー

```
START (TDC割り込み)
  │
  ├─ 回転数カウンタ更新
  │   ├─ OT触媒異常累積回転数 (ecjmfot)
  │   ├─ アイドル異常累積回転数 (ecjmfoti)
  │   └─ EM触媒異常累積回転数 (ecjmfem)
  │
  ├─ DI/PFI回転数カウンタ更新（条件付き）
  │   ├─ DI側累積回転数 (ecjmfdi)
  │   └─ PFI側累積回転数 (ecjmfpfi)
  │
  ├─ 触媒劣化カウンタ判定
  │   └─ emfng_mf_cnt_u1u1
  │       ├─ カウンタ種別判定
  │       ├─ 気筒別カウント
  │       └─ 履歴更新
  │
  ├─ 欧州OBD積算値更新（条件付き）
  │   ├─ 車速積算 (espdaem)
  │   ├─ 回転数積算 (eneaem)
  │   └─ 負荷率積算 (eklsmaem)
  │
  ├─ 粗さ判定処理
  │   └─ emfng_roughjdg_u1u1
  │       ├─ 路上カウンタ更新
  │       ├─ 判定フラグ設定
  │       └─ ピーク値更新
  │
  └─ END
```

## 6. 条件コンパイル解析

### 6.1 主要マクロスイッチマトリクス

| スイッチ | USE時の影響 | 追加される機能 | コード増加量 |
|---------|-----------|--------------|-------------|
| JEOOBD | 欧州OBD規制対応 | 欧州OBD RAM管理、1000rev積算 | ~300行 |
| JENCYL == 6CYL | 6気筒対応 | 気筒対判定、6気筒変数 | ~150行 |
| JEMFDTC_D | DTC出力機能 | DTC通知、FDI連携 | ~200行 |
| JETCORE_D | テストモード対応 | DTR設定、テストデータ出力 | ~100行 |
| JEOBDUDS_D | UDS通信対応 | UDS診断サービス | ~50行 |
| JEMFFC | フェールセーフ制御 | FC判定通知 | ~30行 |
| JEMFHOUKI == USAMF | 米国法規対応 | 米国OBD規制ロジック | ~80行 |
| JEEFI == DUAL | デュアルINJ | DI/PFI分離診断 | ~400行 |
| JEHIPFI_E | 高圧PFI | 高圧PFI関連処理 | ~50行 |
| JENGPF_E | GPF対応 | GPF関連診断 | ~50行 |

### 6.2 コンパイル構成パターン

#### 最小構成
```
JEOOBD = NOT_USE
JENCYL = 4CYL
JEMFDTC_D = NOT_USE
JETCORE_D = NOT_USE
→ 基本触媒診断のみ（約2,800行）
```

#### 標準構成
```
JEOOBD = USE
JENCYL = 4CYL or 6CYL
JEMFDTC_D = USE
JETCORE_D = USE
→ 欧州OBD + DTC出力（約3,500行）
```

#### 最大構成
```
全スイッチ = USE
JENCYL = 6CYL
JEEFI = DUAL
→ 全機能有効（約4,400行）
```

## 7. メモリ使用量推定

### 7.1 RAM使用量（最大構成時）

| 分類 | バイト数 | 備考 |
|------|---------|------|
| グローバル変数 | ~80 bytes | カウンタ、フラグ等 |
| グローバル配列 | ~20 bytes | 気筒別変数（6気筒時） |
| 静的変数 | ~100 bytes | 内部状態変数 |
| 静的配列 | ~30 bytes | デュアルINJ用配列等 |
| スタック使用量 | ~200 bytes | 最大関数呼び出し時 |
| **合計** | **~430 bytes** | |

### 7.2 ROM使用量（最大構成時）

| 分類 | バイト数 | 備考 |
|------|---------|------|
| コードサイズ | ~15KB | 最適化レベルO2想定 |
| const配列 | ~50 bytes | バックアップRAM ID等 |
| 文字列リテラル | 0 bytes | エラーメッセージなし |
| **合計** | **~15KB** | |

## 8. パフォーマンス解析

### 8.1 処理時間推定

| 関数 | 周期/条件 | 推定実行時間 | 備考 |
|------|----------|------------|------|
| emfng_pwon | 起動時1回 | <100μs | 初期化のみ |
| emfng_16msl | 16ms周期 | <500μs | 軽量監視処理 |
| emfng_65msl | 65ms周期 | <2ms | メイン診断処理 |
| emfng_mfptn_ann_u1u1u1 | TDC毎 | <200μs | 高速カウント処理 |
| emfng_drvclchg | イベント | <300μs | 状態遷移処理 |

### 8.2 クリティカルパス

最も実行頻度が高く、リアルタイム性が要求される処理:

1. **emfng_mfptn_ann_u1u1u1()** (TDC毎)
   - 6気筒エンジンで6000rpm時: 毎200μs実行
   - カウンタ更新とフラグ設定のみ
   - 処理時間: <200μs（目標: <100μs）

2. **emfng_16msl()** (16ms周期)
   - 監視処理のみ
   - 処理時間: <500μs（目標: <300μs）

## 9. コード品質評価

### 9.1 強み

1. **詳細なコメント**: 全ての変数・関数に目的と単位を記載
2. **型安全性**: 明示的な型キャストと境界チェック
3. **モジュール化**: 機能ごとに関数を分離
4. **可搬性**: 条件コンパイルによる機種対応
5. **トレーサビリティ**: コメントによる仕様追跡可能

### 9.2 改善余地

1. **関数サイズ**: emfng_65msl()が約700行と長大
2. **ネスト深度**: 一部で5-6レベルの深いネスト
3. **マジックナンバー**: 一部にハードコードされた定数
4. **重複コード**: 類似処理の重複（リファクタリング余地）
5. **グローバル変数**: 多数のグローバル変数使用

### 9.3 MISRA-C準拠度（推定）

| カテゴリ | 準拠度 | 備考 |
|---------|-------|------|
| 必須ルール | 95% | ほぼ準拠 |
| 推奨ルール | 80% | 一部違反の可能性 |
| 助言ルール | 70% | 改善余地あり |

主な違反候補:
- グローバル変数の多用
- 関数の複雑度超過（emfng_65msl等）
- マジックナンバーの使用

## 10. テスタビリティ評価

### 10.1 テストのしやすさ

| 項目 | 評価 | コメント |
|------|------|---------|
| 単体テスト | B | 静的関数が多く、直接テスト困難 |
| 統合テスト | A | 公開関数が明確 |
| カバレッジ | B | 条件分岐が多い |
| モック化 | C | 外部依存が多い |

### 10.2 テスト推奨事項

1. **ホワイトボックステスト**: 各判定分岐の網羅
2. **境界値テスト**: カウンタのオーバーフロー確認
3. **状態遷移テスト**: フラグ遷移の検証
4. **長時間テスト**: カウンタ累積動作確認
5. **異常系テスト**: エラー条件での動作確認

## 11. 保守性評価

### 11.1 可読性: B+

- **良い点**: 
  - 詳細なコメント
  - 一貫した命名規則
  - 明確な関数分割

- **改善点**:
  - 長大な関数の分割
  - マジックナンバーの定数化
  - ネストの簡略化

### 11.2 変更容易性: B

- **良い点**:
  - 条件コンパイルによる機種対応
  - モジュール化された構造
  - バックアップRAM抽象化

- **改善点**:
  - グローバル変数の削減
  - 重複コードの共通化
  - インターフェースの明確化

### 11.3 拡張性: B+

- **良い点**:
  - 条件コンパイルで機能追加容易
  - 配列による気筒数対応
  - フラグによる状態管理

- **改善点**:
  - プラグインアーキテクチャ検討
  - コールバック機構の導入
  - 設定データの外部化

## 12. セキュリティ評価

### 12.1 潜在的リスク

1. **バッファオーバーラン**: 配列アクセスの境界チェック要確認
2. **整数オーバーフロー**: カウンタの上限チェック実装済み
3. **未初期化変数**: ほぼ全て初期化されている
4. **型変換エラー**: 明示的キャストで対応

### 12.2 セキュリティレベル: B+

- 組み込みシステムとして標準的なセキュリティレベル
- 外部入力の検証は外部モジュール依存
- メモリ保護は実行環境依存

## 13. 結論

### 13.1 総合評価: B+

emfng_l_mat.cは、Toyota Motor Corporationの高い品質基準に基づいて開発された、成熟した触媒診断モジュールです。

**主な特徴:**
- 詳細なドキュメント化
- 多様な規格への対応
- 堅牢なエラー処理
- 長期運用実績を反映した設計

**主な課題:**
- 一部関数の複雑度が高い
- グローバル変数の多用
- リファクタリングによる更なる改善余地

### 13.2 推奨アクション

1. **短期**: マジックナンバーの定数化、コメントの英語化
2. **中期**: 長大関数の分割、重複コードの共通化
3. **長期**: アーキテクチャのモダン化、テスト自動化

---

**作成日**: 2025-10-16  
**分析対象**: base/emfng_l_mat.c  
**分析者**: 自動コード解析ツール
