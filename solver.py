import time
import sys

def get_answer(num1, num2, operation):
    if operation == "+":
        return str(num1 + num2)
    if operation == "-":
        return str(num1 - num2) if num1 >= num2 else "Error"
    if operation == "*":
        return str(num1 * num2)
    if operation == "<":
        return str(num1 < num2).lower()
    if operation == ">":
        return str(num1 > num2).lower()
    if operation == "=":
        return str(num1 == num2).lower()
    if operation == "^":
        if num1 == 0 and num2 == 0:
            return "Error"
        return str(num1 ** num2)
    if operation == "/":
        if num2 == 0:
            return "Error"
        return str(num1 // num2)
    return None

def main():

    with open("testbool.txt") as file:
        lines = file.readlines()
        start = time.perf_counter()
        for i in range(0, len(lines), 3):
            if i + 2 >= len(lines):
                break
            num1 = int(lines[i])
            num2 = int(lines[i+1])
            op = lines[i+2].strip()
            ans = get_answer(num1, num2, op)
            # print(ans)
        end = time.perf_counter()
        print(f"Python time: {end - start}", file=sys.stderr)

if __name__ == "__main__":
    main()