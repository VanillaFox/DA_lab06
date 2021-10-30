import sys
import random
import math

if __name__ == '__main__':
    inf = open("test.txt", "w")
    out = open("output.txt", "w")

    try:
        tests = int(sys.argv[1])
    except:
        tests = 100000

    opc = ["+", "-", "*", "<", "=", "^", "/", ">"]
    ops = { '+': lambda a, b: a + b,
            '-': lambda a, b: a - b,
            '*': lambda a, b: a * b,
            '^': lambda a, b: a ** b,
            '/': lambda a, b: a / b,
            '<': lambda a, b: a < b,
            '>': lambda a, b: a > b,
            '=': lambda a, b: a == b }
    opcone = "^"
    for i in range(tests):
        op_ = random.choice(opc)

        l = 500 if op_ == '^' else 10 ** 35
        r = 2000 if op_ == '^' else 10 ** 35

        a = random.randint(0, l)
        b = random.randint(0, r)

        res = ops[op_](a,b)
        if op_ == '<>=':
            res = str(res).lower()

        if op_ == '-' and a < b:
            res = "Error"

        if op_ == '/':
            if b == 0:
                res = "Error"
            else:
                res = math.floor(res)
        inf.write(str(a) + "\n" + str(b) + "\n" + str(op_) + "\n")
        out.write(str(res) + "\n")
    inf.close()
    out.close()