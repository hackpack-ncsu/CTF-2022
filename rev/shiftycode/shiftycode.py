
commands = [i for i in range(9)]

ADD = 0 
SUB = 1
MUL = 2
DIV = 3
PRINT = 4
JMP = 5
INPT = 6
CMP = 7
HALT = 8


print(commands)

program = 'INPT 0\n'\
    'INPT 1\n'\
    'INPT 2\n'\
    'INPT 3\n'\
    'INPT 4\n'\
    'INPT 5\n'\
    'INPT 6\n'\
    'INPT 7\n'\
    'INPT 8\n'\
    'INPT 9\n'\
    'INPT 10\n'\
    'INPT 11\n'\
    'INPT 12\n'\
    'INPT 13\n'\
    'INPT 14\n'\
    'INPT 15\n'\
    'INPT 16\n'\
    'INPT 17\n'\
    'INPT 18\n'\
    'INPT 19\n'\
    'INPT 20\n'\
    'INPT 21\n'\
    'INPT 22\n'\
    'INPT 23\n'\
    'INPT 24\n'\
    'INPT 25\n'\
    'INPT 26\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'INPT 255\n'\
    'CMP 1 0 102\n'\
    'JMP 1 END\n'\
    'CMP 3 1 109\n'\
    'JMP 1 END\n'\
    'CMP 4 1 107\n'\
    'JMP 1 END\n'\
    'ADD 30 r 2\n'\
    'ADD 31 r 3\n'\
    'ADD 32 r 3\n'\
    'ADD 31 r 30\n'\
    'SUB 32 r 30\n'\
    'CMP 1 31 200\n'\
    'JMP 1 END\n'\
    'SUB 31 r 32\n'\
    'CMP 1 31 194\n'\
    'JMP 1 END\n'\
    'CMP 1 4 123\n'\
    'JMP 1 END\n'\
    'CMP 1 26 125\n'\
    'JMP 1 END\n'\
    'ADD 33 r 5\n'\
    'ADD 33 r 7\n'\
    'CMP 1 33 204\n'\
    'JMP 1 END\n'\
    'ADD 33 r 6\n'\
    'ADD 34 r 33\n'\
    'SUB 34 100\n'\
    'CMP 1 34 225\n'\
    'JMP 1 END\n'\
    'SUB 33 r 5\n'\
    'CMP 1 33 216\n'\
    'JMP 1 END\n'\
    'ADD 35 r 9\n'\
    'ADD 35 11\n'\
    'CMP 2 8 35\n'\
    'JMP 1 END\n'\
    'ADD 36 r 10\n'\
    'ADD 36 66\n'\
    'CMP 2 8 36\n'\
    'JMP 1 END\n'\
    'ADD 37 r 12\n'\
    'ADD 37 r 11\n'\
    'SUB 37 r 8\n'\
    'CMP 1 37 103\n'\
    'JMP 1 END\n'\
    'ADD 38 r 12\n'\
    'ADD 38 r 10\n'\
    'SUB 38 r 9\n'\
    'ADD 39 r 11\n'\
    'SUB 39 41\n'\
    'CMP 2 38 39\n'\
    'JMP 1 END\n'\
    'ADD 39 41\n'\
    'SUB 39 r 10\n'\
    'CMP 1 39 53\n'\
    'JMP 1 END\n'\
    'CMP 2 14 19\n'\
    'JMP 1 END\n'\
    'CMP 2 15 18\n'\
    'JMP 1 END\n'\
    'CMP 2 16 7\n'\
    'JMP 1 END\n'\
    'ADD 40 r 13\n'\
    'SUB 40 r 18\n'\
    'SUB 40 r 17\n'\
    'CMP 1 40 0\n'\
    'JMP 1 END\n'\
    'CMP 5 17 18\n'\
    'JMP 1 END\n'\
    'CMP 6 17 19\n'\
    'JMP 1 END\n'\
    'ADD 40 r 18\n'\
    'SUB 40 r 19\n'\
    'CMP 1 40 2\n'\
    'JMP 1 END\n'\
    'ADD 41 r 13\n'\
    'SUB 41 54\n'\
    'CMP 2 41 14\n'\
    'JMP 1 END\n'\
    'ADD 42 r 19\n'\
    'MUL 42 2\n'\
    'CMP 2 42 23\n'\
    'JMP 1 END\n'\
    'CMP 2 20 16\n'\
    'JMP 1 END\n'\
    'CMP 2 22 10\n'\
    'JMP 1 END\n'\
    'ADD 43 r 21\n'\
    'MUL 42 2\n'\
    'DIV 43 2\n'\
    'SUB 43 6\n'\
    'CMP 2 43 22\n'\
    'JMP 1 END\n'\
    'ADD 44 r 25\n'\
    'SUB 44 r 24\n'\
    'CMP 1 44 5\n'\
    'JMP 1 END\n'\
    'ADD 45 r 25\n'\
    'SUB 45 r 21\n'\
    'CMP 1 45 11\n'\
    'JMP 1 END\n'\
    'MUL 42 2\n'\
    'DIV 42 2\n'\
    'PRINT 0\n'\
    'PRINT 1\n'\
    'PRINT 2\n'\
    'PRINT 3\n'\
    'PRINT 4\n'\
    'PRINT 5\n'\
    'PRINT 6\n'\
    'PRINT 7\n'\
    'PRINT 8\n'\
    'PRINT 9\n'\
    'PRINT 10\n'\
    'PRINT 11\n'\
    'PRINT 12\n'\
    'PRINT 13\n'\
    'PRINT 14\n'\
    'PRINT 15\n'\
    'PRINT 16\n'\
    'PRINT 17\n'\
    'PRINT 18\n'\
    'PRINT 19\n'\
    'PRINT 20\n'\
    'PRINT 21\n'\
    'PRINT 22\n'\
    'PRINT 23\n'\
    'PRINT 24\n'\
    'PRINT 25\n'\
    'PRINT 26\n'\
    'halt'

program = program.split("\n")
print(program)

opcodes = []

for line in program:
    line = line.split(" ")

    if line[0].upper() == "ADD":
        opcodes.append(commands[ADD])
        commands[ADD] += 1
        if line[2] == "r":
            [opcodes.append(i) for i in (2, int(line[1]), int(line[3]))]
        else:
            [opcodes.append(i) for i in (1, int(line[1]), int(line[2]))]
    elif line[0].upper() == "SUB":
        opcodes.append(commands[SUB])
        commands[SUB] += 1
        if line[2] == "r":
            [opcodes.append(i) for i in (2, int(line[1]), int(line[3]))]
        else:
            [opcodes.append(i) for i in (1, int(line[1]), int(line[2]))]
    elif line[0].upper() == "MUL":
        opcodes.append(commands[MUL])
        commands[MUL] += 1
        if line[2] == "r":
            [opcodes.append(i) for i in (2, int(line[1]), int(line[3]))]
        else:
            [opcodes.append(i) for i in (1, int(line[1]), int(line[2]))]
    elif line[0].upper() == "DIV":
        opcodes.append(commands[DIV])
        commands[DIV] += 1
        if line[2] == "r":
            [opcodes.append(i) for i in (2, int(line[1]), int(line[3]))]
        else:
            [opcodes.append(i) for i in (1, int(line[1]), int(line[2]))]
    elif line[0].upper() == "PRINT":
        opcodes.append(commands[PRINT])
        commands[PRINT]
        opcodes.append(int(line[1]))
    elif line[0].upper() == "JMP":
        opcodes.append(commands[JMP])
        commands[JMP] += 1
        [opcodes.append(i) for i in (int(line[1]), int(line[2]) if line[2] != "END" else b'??')]
    elif line[0].upper() == "INPT":
        opcodes.append(commands[INPT])
        commands[INPT] += 1
        opcodes.append(int(line[1]))
    elif line[0].upper() == "CMP":
        opcodes.append(commands[CMP])
        commands[CMP] += 1
        [opcodes.append(i) for i in (int(line[1]), int(line[2]), int(line[3]))]
    elif line[0].upper() == "HALT":
        opcodes.append(commands[HALT])

for i in range(0, len(opcodes)):
    if opcodes[i] == b'??':
        l = len(opcodes) - i - 2
        if l > 255:
            l = 0
            for j in range(i+3, len(opcodes)):
                if opcodes[j] == b'??':
                    break
                l += 1
        opcodes[i] = l
        print(l)

print("Len:", len(opcodes))
out_str = b''.join([i.to_bytes(1, "big") for i in opcodes])

print(out_str)
open("bin", "wb").write(out_str)