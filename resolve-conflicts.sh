#!/bin/bash

# Conflict Resolution Script
# このスクリプトは、マージコンフリクトが発生した際に、
# すべてのコンフリクトに対して「Current Change（現在の変更）」を一括で受け入れます。
#
# 使い方:
#   ./resolve-conflicts.sh
#
# または特定のファイルのみ解決する場合:
#   ./resolve-conflicts.sh <file1> <file2> ...

set -e

# 色の定義
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}======================================${NC}"
echo -e "${BLUE}  Conflict Resolution Tool${NC}"
echo -e "${BLUE}  Current Changes (Ours) を一括受け入れ${NC}"
echo -e "${BLUE}======================================${NC}"
echo ""

# コンフリクトが発生しているか確認
if ! git status | grep -q "Unmerged paths:"; then
    echo -e "${YELLOW}コンフリクトが検出されませんでした。${NC}"
    echo ""
    echo "このスクリプトは、マージコンフリクトが発生した時に使用します。"
    echo ""
    echo "使用方法:"
    echo "  1. ブランチをマージしてコンフリクトを発生させる"
    echo "     例: git merge <branch-name>"
    echo "  2. このスクリプトを実行してコンフリクトを解決"
    echo "     ./resolve-conflicts.sh"
    echo "  3. 変更をコミット"
    echo "     git commit"
    exit 0
fi

# コンフリクトしているファイルのリストを取得
if [ $# -eq 0 ]; then
    # 引数がない場合はすべてのコンフリクトファイルを取得
    CONFLICTED_FILES=$(git diff --name-only --diff-filter=U)
else
    # 引数がある場合は指定されたファイルのみ
    CONFLICTED_FILES="$@"
fi

if [ -z "$CONFLICTED_FILES" ]; then
    echo -e "${YELLOW}コンフリクトしているファイルが見つかりませんでした。${NC}"
    exit 0
fi

echo -e "${YELLOW}以下のファイルのコンフリクトを解決します:${NC}"
echo "$CONFLICTED_FILES" | while read file; do
    echo "  - $file"
done
echo ""

# 確認プロンプト
read -p "すべてのファイルで Current Change (ours) を受け入れますか？ (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${RED}キャンセルされました。${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}コンフリクトを解決中...${NC}"
echo ""

# 各ファイルのコンフリクトを解決
SUCCESS_COUNT=0
FAIL_COUNT=0

echo "$CONFLICTED_FILES" | while read file; do
    if [ -n "$file" ]; then
        echo -e "${BLUE}処理中: $file${NC}"
        if git checkout --ours "$file" 2>/dev/null; then
            git add "$file"
            echo -e "${GREEN}  ✓ 解決しました${NC}"
            SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
        else
            echo -e "${RED}  ✗ エラーが発生しました${NC}"
            FAIL_COUNT=$((FAIL_COUNT + 1))
        fi
    fi
done

echo ""
echo -e "${GREEN}======================================${NC}"
echo -e "${GREEN}完了しました！${NC}"
echo -e "${GREEN}======================================${NC}"
echo ""
echo "次のステップ:"
echo "  1. 変更内容を確認: git status"
echo "  2. 必要に応じて追加の変更を行う"
echo "  3. マージをコミット: git commit"
echo ""
echo -e "${YELLOW}注意: このスクリプトは現在のブランチの変更（ours）をすべて受け入れます。${NC}"
echo -e "${YELLOW}      マージ先の変更（theirs）は破棄されます。${NC}"
