# Conflict Resolution Guide / コンフリクト解決ガイド

## 概要

このガイドでは、Git マージコンフリクトが発生した際に、「Current Change（現在の変更）」を一括で受け入れる方法を説明します。

**📄 関連ドキュメント**:
- [クイックリファレンス](./QUICK_REFERENCE.md) - コマンド一覧とよくあるシナリオ
- [使用例](./CONFLICT_RESOLUTION_EXAMPLES.md) - 詳細な使用例とベストプラクティス

## 🚀 クイックスタート

### 方法1: スクリプトを使用（推奨）

```bash
# マージを実行してコンフリクトが発生
git merge <branch-name>

# すべてのコンフリクトでCurrent Change (ours)を受け入れ
./resolve-conflicts.sh

# マージをコミット
git commit
```

### 方法2: Git コマンドを使用

```bash
# マージ戦略でoursを指定（コンフリクトなしでマージ）
git merge -X ours <branch-name>

# または、既にコンフリクトが発生している場合
git checkout --ours .
git add .
git commit
```

## 📖 詳細説明

### スクリプトの機能

`resolve-conflicts.sh` スクリプトは以下の機能を提供します：

1. **自動検出**: コンフリクトしているファイルを自動的に検出
2. **一括解決**: すべてのコンフリクトで現在のブランチの変更を受け入れ
3. **確認プロンプト**: 実行前に確認を求める
4. **カラー出力**: わかりやすい色付き出力
5. **個別指定**: 特定のファイルのみ解決することも可能

### 使用例

#### 例1: すべてのコンフリクトを解決

```bash
$ git merge feature-branch
# コンフリクトが発生...

$ ./resolve-conflicts.sh
======================================
  Conflict Resolution Tool
  Current Changes (Ours) を一括受け入れ
======================================

以下のファイルのコンフリクトを解決します:
  - file1.txt
  - file2.md

すべてのファイルで Current Change (ours) を受け入れますか？ (y/N): y

コンフリクトを解決中...

処理中: file1.txt
  ✓ 解決しました
処理中: file2.md
  ✓ 解決しました

======================================
完了しました！
======================================
```

#### 例2: 特定のファイルのみ解決

```bash
$ ./resolve-conflicts.sh file1.txt
```

#### 例3: Git コマンドで直接解決

```bash
# すべてのファイルでoursを受け入れ
$ git checkout --ours .
$ git add .

# または特定のファイルのみ
$ git checkout --ours file1.txt
$ git add file1.txt
```

## 🔍 戦略の理解

### --ours vs --theirs

- **--ours**: 現在のブランチ（HEAD）の変更を受け入れ
- **--theirs**: マージしようとしているブランチの変更を受け入れ

### マージ戦略

```bash
# マージ時にコンフリクトを自動解決（ours戦略）
git merge -X ours <branch-name>

# マージ時にコンフリクトを自動解決（theirs戦略）  
git merge -X theirs <branch-name>
```

## ⚠️ 注意事項

1. **データ損失の可能性**: `--ours` を使用すると、マージ元のブランチの変更が失われます
2. **慎重な確認**: 重要な変更が含まれる場合は、手動でコンフリクトを確認してください
3. **コミット前の確認**: `git diff --cached` で変更内容を確認してからコミットしてください

## 🛠️ トラブルシューティング

### コンフリクトが検出されない

```bash
$ git status
# マージ中かどうか確認
```

### スクリプトの実行権限エラー

```bash
$ chmod +x resolve-conflicts.sh
```

### 手動でコンフリクトを解決したい場合

```bash
# スクリプトを使わずに手動で解決
$ git status
$ vim <conflicted-file>
# コンフリクトマーカーを編集
$ git add <conflicted-file>
$ git commit
```

## 📚 関連コマンド

```bash
# コンフリクトしているファイルのリスト
git diff --name-only --diff-filter=U

# マージを中止
git merge --abort

# 特定のファイルの変更を確認
git diff <file>

# ステージングされた変更を確認
git diff --cached
```

## 🔗 参考資料

- [Git 公式ドキュメント - マージ戦略](https://git-scm.com/docs/merge-strategies)
- [Git checkout --ours/--theirs](https://git-scm.com/docs/git-checkout#Documentation/git-checkout.txt---ours)

---

**最終更新**: 2025-10-17
