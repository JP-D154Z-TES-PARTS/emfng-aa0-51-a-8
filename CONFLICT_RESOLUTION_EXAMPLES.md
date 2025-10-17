# Conflict Resolution Examples / コンフリクト解決の例

このドキュメントでは、`resolve-conflicts.sh` スクリプトを使用した具体的な例を示します。

## 例1: 通常のマージコンフリクト解決

### シナリオ
feature ブランチを main ブランチにマージする際にコンフリクトが発生した場合

### 手順

```bash
# 1. feature ブランチをマージしようとする
$ git checkout main
$ git merge feature-branch

Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Auto-merging src/main.js
CONFLICT (content): Merge conflict in src/main.js
Automatic merge failed; fix conflicts and then commit the result.

# 2. コンフリクトを確認
$ git status

On branch main
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   README.md
        both modified:   src/main.js

# 3. スクリプトを実行してすべてのコンフリクトを解決
$ ./resolve-conflicts.sh

======================================
  Conflict Resolution Tool
  Current Changes (Ours) を一括受け入れ
======================================

以下のファイルのコンフリクトを解決します:
  - README.md
  - src/main.js

すべてのファイルで Current Change (ours) を受け入れますか？ (y/N): y

コンフリクトを解決中...

処理中: README.md
  ✓ 解決しました
処理中: src/main.js
  ✓ 解決しました

======================================
完了しました！
======================================

# 4. 変更を確認
$ git status

On branch main
All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:
        modified:   README.md
        modified:   src/main.js

# 5. マージをコミット
$ git commit -m "Merge feature-branch with ours strategy"
```

## 例2: 特定のファイルのみ解決

### シナリオ
複数のファイルでコンフリクトが発生したが、README.md のみ現在の変更を受け入れたい場合

```bash
# コンフリクトが発生している状態で
$ ./resolve-conflicts.sh README.md

======================================
  Conflict Resolution Tool
  Current Changes (Ours) を一括受け入れ
======================================

以下のファイルのコンフリクトを解決します:
  - README.md

すべてのファイルで Current Change (ours) を受け入れますか？ (y/N): y

コンフリクトを解決中...

処理中: README.md
  ✓ 解決しました

======================================
完了しました！
======================================

# 他のファイルは手動で解決
$ vim src/main.js
# コンフリクトマーカーを編集...

$ git add src/main.js
$ git commit
```

## 例3: Git コマンドを直接使用

### シナリオ
スクリプトを使わずに Git コマンドで解決したい場合

```bash
# 方法A: マージ時に戦略を指定（コンフリクトが発生する前）
$ git merge -X ours feature-branch

# 方法B: 既にコンフリクトが発生している場合
# すべてのファイルで ours を選択
$ git checkout --ours .
$ git add .
$ git commit

# 方法C: 特定のファイルのみ ours を選択
$ git checkout --ours README.md
$ git add README.md
# 他のファイルは手動で解決
$ vim src/main.js
$ git add src/main.js
$ git commit
```

## 例4: コンフリクトの内容を確認してから解決

### シナリオ
どのような変更がコンフリクトしているか確認してから決めたい場合

```bash
# 1. コンフリクトが発生
$ git merge feature-branch
CONFLICT (content): Merge conflict in config.yml

# 2. コンフリクトの内容を確認
$ git diff config.yml

<<<<<<< HEAD (Current Change)
version: 2.0
database: postgresql
=======
version: 1.5
database: mysql
>>>>>>> feature-branch (Incoming Change)

# 3. Current Change (version: 2.0, postgresql) を採用すると決めた
$ ./resolve-conflicts.sh config.yml

# 4. 確認してコミット
$ git diff --cached config.yml
$ git commit
```

## 例5: 複数ブランチのマージ

### シナリオ
複数のフィーチャーブランチを順次マージする場合

```bash
# branch-A をマージ
$ git merge branch-A
# コンフリクト発生
$ ./resolve-conflicts.sh
$ git commit -m "Merge branch-A"

# branch-B をマージ
$ git merge branch-B  
# コンフリクト発生
$ ./resolve-conflicts.sh
$ git commit -m "Merge branch-B"

# branch-C をマージ
$ git merge branch-C
# コンフリクト発生
$ ./resolve-conflicts.sh
$ git commit -m "Merge branch-C"
```

## ⚠️ 注意が必要なケース

### ケース1: 重要な変更が両方にある場合

```bash
# このような場合は手動で確認することを推奨
$ git diff --name-only --diff-filter=U
important-config.yml
database-schema.sql

# 内容を確認
$ git diff important-config.yml

# 重要な変更がある場合は手動でマージ
$ vim important-config.yml
# 両方の変更を統合...

$ git add important-config.yml
$ git commit
```

### ケース2: バイナリファイルのコンフリクト

```bash
# バイナリファイルの場合は --ours または --theirs のどちらかを選択
$ git checkout --ours image.png
$ git add image.png

# または
$ git checkout --theirs image.png  
$ git add image.png
```

## 🔄 マージを中止したい場合

```bash
# マージを完全に中止
$ git merge --abort

# これで元の状態に戻ります
$ git status
On branch main
nothing to commit, working tree clean
```

## 📝 ベストプラクティス

1. **事前確認**: コンフリクトの内容を `git diff` で確認
2. **バックアップ**: 重要なブランチの場合は事前にバックアップ
3. **段階的マージ**: 大きな変更の場合は小さく分けてマージ
4. **テスト**: マージ後は必ずテストを実行
5. **レビュー**: チームメンバーにレビューを依頼

---

**参考**: [CONFLICT_RESOLUTION.md](./CONFLICT_RESOLUTION.md) で詳細なガイドを確認できます。
