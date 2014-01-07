#include <stdio.h>
#include <stdlib.h>

int pick(int door, int choice) { return choice == door ? 1 : 0; }

int main() {
    int choice, door, revealed, tries, tactic1, tactic2, i;

    tactic1 = tactic2 = 0;
    tries = 10000000;

    srand(time(NULL));

    for (i = 0; i < tries; i++) {
        door = rand() % 3;
        choice = rand() % 3;

        tactic1 += pick(door, choice);

        revealed = door == choice ? (choice + 1) % 3 : 3 - choice - door;
        choice = 3 - choice - revealed;

        tactic2 += pick(door, choice);
    }

    printf("Tactic 1: %.2f\n", (float)tactic1 / tries * 100);
    printf("Tactic 2: %.2f\n", (float)tactic2 / tries * 100);

    return 0;
}
