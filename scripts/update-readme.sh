#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readme="${root_dir}/README.md"

if command -v rg >/dev/null 2>&1; then
  search_cmd="rg"
else
  search_cmd="grep"
fi

mapfile -t problem_readmes < <(
  find "${root_dir}" -maxdepth 2 -type f -name README.md -path "${root_dir}/[0-9][0-9][0-9][0-9]-*/README.md" | sort
)

rows=()
easy=0
medium=0
hard=0

for problem_readme in "${problem_readmes[@]}"; do
  folder="$(basename "$(dirname "${problem_readme}")")"

  title="$(${search_cmd} -m1 -o '<h2><a href="[^"]+">[^<]+' "${problem_readme}" | sed -E 's#<h2><a href="[^"]+">##')"
  url="$(${search_cmd} -m1 -o '<h2><a href="[^"]+"' "${problem_readme}" | sed -E 's#<h2><a href="##; s#"$##')"
  difficulty="$(${search_cmd} -m1 -o '<h3>[^<]+' "${problem_readme}" | sed -E 's#<h3>##')"

  title="${title//×/x}"

  case "${difficulty}" in
    Easy) easy=$((easy + 1)) ;;
    Medium) medium=$((medium + 1)) ;;
    Hard) hard=$((hard + 1)) ;;
  esac

  row="| [${title}](${url}) | ${difficulty} | [\`${folder}\`](${folder}) |"
  rows+=("${folder}|${row}")
done

IFS=$'\n' sorted_rows=($(printf '%s\n' "${rows[@]}" | sort))
unset IFS

table="| Problem | Difficulty | Solution |\n| --- | --- | --- |\n"
for entry in "${sorted_rows[@]}"; do
  table+="${entry#*|}\n"
done

total="${#problem_readmes[@]}"

badges="![Language](https://img.shields.io/badge/language-C%2B%2B-blue)\n"
badges+="![Problems](https://img.shields.io/badge/problems-${total}-brightgreen)\n"
badges+="![Easy](https://img.shields.io/badge/easy-${easy}-success)\n"
badges+="![Medium](https://img.shields.io/badge/medium-${medium}-yellow)\n"
badges+="![Hard](https://img.shields.io/badge/hard-${hard}-red)"

progress="- Total solved: ${total}\n- Easy: ${easy}\n- Medium: ${medium}\n- Hard: ${hard}"

python3 - <<PY
from pathlib import Path

readme = Path(${readme@Q})
text = readme.read_text()

def replace_block(name: str, content: str, text: str) -> str:
    start = f"<!-- README:{name}:START -->"
    end = f"<!-- README:{name}:END -->"
    if start not in text or end not in text:
        raise SystemExit(f"Missing markers for {name}")
    before, rest = text.split(start, 1)
    middle, after = rest.split(end, 1)
    return before + start + "\n" + content.rstrip() + "\n" + end + after

text = replace_block("BADGES", ${badges@Q}, text)
text = replace_block("PROGRESS", ${progress@Q}, text)
text = replace_block("SOLUTIONS", ${table@Q}, text)

readme.write_text(text)
PY

echo "Updated README.md"
