import os
import re

def fix_list_structure(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except Exception as e:
        print(f"Error reading {filepath}: {e}")
        return False

    new_lines = []
    i = 0
    modified = False
    
    while i < len(lines):
        line = lines[i]
        # リストアイテムの開始を検知
        match = re.match(r'^(\s*)(\d+)\.\s+(.*)', line)
        if match:
            indent, first_num, rest = match.groups()
            
            # このブロックが「1行空きの奇数リスト」かどうかを先読みして判定する
            list_items = []
            curr_idx = i
            is_spaced_odd_list = False
            
            # 一時的にリストの内容を収集
            temp_items = []
            j = i
            while j < len(lines):
                m = re.match(r'^(\s*)(\d+)\.\s+(.*)', lines[j])
                if m:
                    temp_items.append({
                        'line_idx': j,
                        'num': int(m.group(2)),
                        'content': m.group(3),
                        'indent': m.group(1)
                    })
                    # 次の行が空行で、その次が数字リストかチェック
                    if j + 2 < len(lines):
                        next_m = re.match(r'^(\s*)(\d+)\.\s+(.*)', lines[j+2])
                        if lines[j+1].strip() == "" and next_m:
                            j += 2
                            continue
                    break
                else:
                    break
            
            # 収集したアイテムが2つ以上あり、番号が1, 3, 5... と増えているか確認
            if len(temp_items) >= 2:
                nums = [item['num'] for item in temp_items]
                # 奇数連番チェック（1, 3, 5... または 2, 4, 6... など）
                is_spaced_odd_list = all(nums[k] + 2 == nums[k+1] for k in range(len(nums)-1))
            
            if is_spaced_odd_list:
                # 修正：空行を削除し、番号を1, 2, 3... にリセット
                for idx, item in enumerate(temp_items):
                    new_lines.append(f"{item['indent']}{idx + 1}. {item['content']}\n")
                
                # 処理した行までスキップ
                i = temp_items[-1]['line_idx'] + 1
                modified = True
            else:
                new_lines.append(line)
                i += 1
        else:
            new_lines.append(line)
            i += 1
                
    if modified:
        try:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.writelines(new_lines)
            return True
        except Exception as e:
            print(f"Error writing {filepath}: {e}")
            return False
    return False

root_dir = r'e:\VSCodeソース\strange_music_page\site\src\content\livereports'

fixed_count = 0
for root, dirs, files in os.walk(root_dir):
    for name in files:
        if name.endswith('.md'):
            path = os.path.join(root, name)
            if fix_list_structure(path):
                # print(f"Fixed spaced list: {path}")
                fixed_count += 1

print(f"Total fixed (spaced lists): {fixed_count} files.")
