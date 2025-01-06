
import json
import sys

def doit(obj, part2 = False):
    if isinstance(obj, list):
        return sum(map(lambda x: doit(x, part2), obj))
    if isinstance(obj, dict):
        if part2 and "red" in obj.values():
            return 0
        a = 0
        for k, v in obj.items():
            a += doit(k, part2) + doit(v, part2)
        return a
    if isinstance(obj, str):
        return 0
    if isinstance(obj, int):
        return obj
    print(type(obj))


def main():
    j = json.load(sys.stdin)
    print("part1", doit(j, False))
    print("part2", doit(j, True))
    
if __name__ == "__main__":
    main()