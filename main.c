#include <stdbool.h>
#include <stdio.h>

#define sp (registers[SP])
#define ip (registers[IP])
#define STACK_SIZE 256

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F, IP, SP,
    NUM_OF_REGISTERS
} Registers;

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int stack[STACK_SIZE];
static int registers[NUM_OF_REGISTERS];
bool running = true;

int fetch() {
    return program[ip];
}

void eval(int instr) {
    switch (instr) {
        // Braces around the switch statements to have local scope
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = program[++ip];
            break;
        }
        case POP: {
            // Store value then decrement
            int val = stack[sp--];
            printf("Popped %d\n", val);
            break;
        }
        case ADD: {
            int a = stack[sp--];
            int b = stack[sp--];
            int r = b + a;
            sp++;
            stack[sp] = r;
            break;
        }
        case SET: {
            registers[ip + 1] = registers[ip + 2];
            ip = ip + 2;
            break;
        }
    }
}


int main()
{
    while (running) {
        eval(fetch());
        ip++;
    }

    return 0;
}
