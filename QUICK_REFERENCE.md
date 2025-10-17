# Quick Reference Guide / クイックリファレンスガイド

## コンフリクト解決の方法

### 🚀 最も簡単な方法（推奨）

```bash
# スクリプトを実行
./resolve-conflicts.sh
```

### 📋 その他の方法

#### 方法1: マージ時に戦略を指定

```bash
git merge -X ours <branch-name>
```

#### 方法2: Git コマンドで解決

```bash
# すべてのコンフリクトファイルを一括解決
git checkout --ours .
git add .
git commit

# 特定のファイルのみ解決
git checkout --ours <file>
git add <file>
```

## 📝 コマンド一覧

| コマンド | 説明 |
|---------|------|
| `./resolve-conflicts.sh` | スクリプトでコンフリクト解決（推奨） |
| `./resolve-conflicts.sh file1.txt` | 特定のファイルのみ解決 |
| `git merge -X ours <branch>` | マージ時にours戦略を使用 |
| `git checkout --ours .` | すべてのファイルでoursを選択 |
| `git checkout --ours <file>` | 特定のファイルでoursを選択 |
| `git checkout --theirs .` | すべてのファイルでtheirsを選択 |
| `git diff --name-only --diff-filter=U` | コンフリクトファイル一覧 |
| `git status` | マージ状態の確認 |
| `git merge --abort` | マージを中止 |

## 🔍 確認コマンド

```bash
# コンフリクトの状態を確認
git status

# コンフリクトしているファイルを確認
git diff --name-only --diff-filter=U

# コンフリクトの内容を確認
git diff <file>

# ステージングされた変更を確認
git diff --cached
```

## ⚡ フローチャート

```
コンフリクト発生
     ↓
確認: git status
     ↓
┌────────────────────┐
│ すべてCurrent Change? │
└────────────────────┘
     ↓ Yes           ↓ No
./resolve-conflicts.sh   手動編集
     ↓                   ↓
git commit          git add
                        ↓
                   git commit
```

## 🎯 よくあるシナリオ

### シナリオ1: feature ブランチを main にマージ

```bash
git checkout main
git merge feature
# コンフリクト発生
./resolve-conflicts.sh
git commit
```

### シナリオ2: リモートから pull してコンフリクト

```bash
git pull origin main
# コンフリクト発生
./resolve-conflicts.sh
git commit
```

### シナリオ3: 複数のブランチを統合

```bash
git merge branch-A
./resolve-conflicts.sh
git commit

git merge branch-B
./resolve-conflicts.sh
git commit
```

## 📚 詳細ドキュメント

- [CONFLICT_RESOLUTION.md](./CONFLICT_RESOLUTION.md) - 完全なガイド
- [CONFLICT_RESOLUTION_EXAMPLES.md](./CONFLICT_RESOLUTION_EXAMPLES.md) - 詳細な例

---

**ヒント**: 
- コンフリクトの内容を確認してから解決することをお勧めします
- 重要な変更がある場合は手動でマージを検討してください
- 不明な点があれば上記の詳細ドキュメントを参照してください
