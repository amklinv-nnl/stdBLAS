import sys
import json
from collections import defaultdict

lcov_file = sys.argv[1]
out_file = sys.argv[2]

stats = defaultdict(lambda: {"hit": 0, "total": 0})

current = None

with open(lcov_file) as f:
    for line in f:
        line = line.strip()

        if line.startswith("SF:"):
            current = line[3:]
        elif line.startswith("DA:"):
            stats[current]["total"] += 1
            if line.endswith(",1"):
                stats[current]["hit"] += 1

output = []

for file, s in stats.items():
    if "/include/" not in file:
        continue

    total = s["total"]
    hit = s["hit"]
    coverage = (hit / total * 100) if total else 0

    output.append({
        "file": file,
        "hit": hit,
        "total": total,
        "coverage": round(coverage, 2)
    })

output.sort(key=lambda x: x["coverage"])

with open(out_file, "w") as f:
    json.dump(output, f, indent=2)