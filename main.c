#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LETTERS_SIZE 50

typedef struct {
  char data[50];
  int size;
} LETTERS;

void init_letters(LETTERS* g) {
  for (int i = 0; i < LETTERS_SIZE; i++) g->data[i] = '_';
  g->size = 0;
}

bool check_guess(char guess, const char* word, LETTERS* letters) {
  int count = 0;
  for (int i = 0; i < sizeof(word); i++) {
    if (guess == word[i]) {
      letters->data[i] = guess;
      letters->size++;
      count++;
    }
  }
  if (count > 0) return true;
  return false;
}

bool check_letters(LETTERS* letters, const char* word) {
  for (int i = 0; i < strlen(word); i++) {
    if (letters->data[i] != word[i]) return false;
  }
  return true;
}

void print_letters(LETTERS* l, int word_size) {
  for (int i = 0; i < word_size - 1; i++) {
    printf("%c ", l->data[i]);
  }
  printf("\n");
}

void draw_stickman(int errors) {
  switch (errors) {
    case 0:
      printf("  +---+\n");
      printf("  |   |\n");
      printf("      |\n");
      printf("      |\n");
      printf("      |\n");
      printf("      |\n");
      printf("=========\n\n");
      break;
    case 1:
      printf("  +---+\n");
      printf("  |   |\n");
      printf("  O   |\n");
      printf("      |\n");
      printf("      |\n");
      printf("      |\n");
      printf("=========\n\n");
      break;
    case 2:
      printf("  +---+\n");
      printf("  |   |\n");
      printf("  O   |\n");
      printf(" /|\\  |\n");
      printf("      |\n");
      printf("      |\n");
      printf("=========\n\n");
      break;
    case 3:
      printf("  +---+\n");
      printf("  |   |\n");
      printf("  O   |\n");
      printf(" /|\\  |\n");
      printf(" / \\  |\n");
      printf("      |\n");
      printf("=========\n\n");
      break;
  }
}

int main(int argc, char const* argv[]) {
  char word[] = "create";
  int errors = 0;
  char* guess = (char*)malloc(sizeof(char));

  LETTERS letters;
  init_letters(&letters);

  draw_stickman(errors);
  print_letters(&letters, sizeof(word));
  printf("Errors: %d\n", errors);

  while (true) {
    printf("Guess: ");
    scanf(" %c", guess);

    if (!check_guess(*guess, word, &letters)) errors++;

    draw_stickman(errors);
    print_letters(&letters, sizeof(word));
    printf("Errors: %d\n", errors);

    if (errors == 3) {
      printf("YOU LOSE!\n");
      break;
    }
    if (check_letters(&letters, word)) {
      printf("YOU WIN!\n");
      break;
    }
  }

  return 0;
}
