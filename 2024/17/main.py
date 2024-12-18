#!/usr/bin/env python3

import sys

def run_program(registers, program):
    def combo_operand(value):
        match value:
            case 0 | 1 | 2 | 3:
                return value
            case 4:
                return A
            case 5:
                return B
            case 6:
                return C

    A, B, C = registers
    pointer = 0
    outputs = []

    while pointer < len(program):
        opcode = program[pointer]
        operand = program[pointer + 1]

        if opcode == 0:
            A //= 2 ** combo_operand(operand)
        elif opcode == 1:
            B ^= operand
        elif opcode == 2:
            B = combo_operand(operand) % 8
        elif opcode == 3:
            if A != 0:
                pointer = operand
                continue
        elif opcode == 4:
            B ^= C
        elif opcode == 5:
            outputs.append(combo_operand(operand) % 8)
        elif opcode == 6:
            B = A // (2 ** combo_operand(operand))
        elif opcode == 7:
            C = A // (2 ** combo_operand(operand))

        pointer += 2

    return outputs

def doPart1(filename:str):
    registers, program = open(filename,"r").read().strip().split("\n\n")
    registers = [int(x.split(":")[1]) for x in registers.strip().split("\n")]
    program = [int(inst) for inst in program.strip().split(":")[1].strip().split(",")]
    result = run_program(registers, program)
    print(",".join(map(str, result)))

def doPart2(filename:str):
    if filename == "example.dat":
        registers = [2024,0,0]
        program = [0,3,5,4,3,0]
    else:
        registers, program = open(filename,"r").read().strip().split("\n\n")
        registers = [int(x.split(":")[1]) for x in registers.strip().split("\n")]
        program = [int(inst) for inst in program.strip().split(":")[1].strip().split(",")]

    A = 8**(len(program)-1)

    while True:
        result = run_program([A, 0, 0], program)

        if result == program:
            print(A)
            break

        add = 0
        for i in range(len(result) - 1, -1, -1):
            if result[i] != program[i]:
                add = 8**i
                A += add
                break

def main():
    filename = "example.dat"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    doPart1(filename)
    doPart2(filename)

if __name__ == "__main__":
    main()
