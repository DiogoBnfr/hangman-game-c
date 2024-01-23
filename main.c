#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 50

typedef struct {
  char data[BUFFER_SIZE];
  int size;
} LETTERS;

void init_letters(LETTERS* g) {
  for (int i = 0; i < BUFFER_SIZE; i++) g->data[i] = '_';
  g->size = 0;
}

int word_size(char* buffer) {
  int size = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (buffer[i] == '\0') break;
    size++;
  }
  return size;
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

int random_word(char* filename, char* buffer) {
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error: file not found.");
    return 1;
  }

  srand(time(NULL));

  // TODO: make reader adaptable to different line numbers files
  int read_line = rand() % 46 + 1;
  int current_line = 1;

  do {
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
      printf("Error: can't read line %d\n", read_line);
      fclose(file);
      return 1;
    }

    if (current_line == read_line) {
      break;
    }

    current_line++;
  } while (true);

  return 0;
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
  char buffer[BUFFER_SIZE];
  int errors = 0;
  char* guess = (char*)malloc(sizeof(char));

  // TODO: make all letter lowercase (file/user input)
  random_word("words.txt", buffer);
  int size = word_size(buffer);
  printf("%s\n", buffer);

  LETTERS letters;
  init_letters(&letters);

  draw_stickman(errors);
  print_letters(&letters, size);
  printf("Errors: %d\n", errors);

  while (true) {
    printf("Guess: ");
    scanf(" %c", guess);

    if (!check_guess(*guess, buffer, &letters)) errors++;

    draw_stickman(errors);
    print_letters(&letters, size);
    printf("Errors: %d\n", errors);

    if (errors == 3) {
      printf("YOU LOSE!\n");
      break;
    }  // TODO: don't recognize win
    if (check_letters(&letters, buffer)) {
      printf("YOU WIN!\n");
      break;
    }
  }

  printf("The word was: %s", buffer);

  return 0;
}
