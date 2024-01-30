#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 50

int buffer_size(char* buffer) {
  int size = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (buffer[i] == '\0') break;
    size++;
  }
  return size;
}

void tolower_str(char* str) {
  for (int i = 0; i < strlen(str); i++) str[i] = tolower(str[i]);
}

void initialize_guesses(char* guesses, char* word) {
  for (int i = 0; i < buffer_size(word); i++) {
    guesses[i] = '_';
  }
}

bool check_guess(char guess, char* word, char* guesses) {
  for (int i = 0; i < buffer_size(word); i++) {
    if (word[i] == guess) {
      guesses[i] = guess;
      return true;
    }
  }
  return false;
}

bool check_guesses(char guess, char* word, char* guesses) {
  int count = 0;

  for (int i = 0; i < buffer_size(word); i++) {
    for (int j = 0; j < buffer_size(guesses); j++) {
      if (word[i] == guesses[j]) count++;
    }
  }
	
  if (count == buffer_size(word) - 1) return true;
  return false;
}

void display_current_state(char* word, char* guesses) {
  bool printed;

  for (int i = 0; i < buffer_size(word) - 1; i++) {
    printed = false;
    for (int j = 0; j < buffer_size(guesses); j++) {
      if (word[i] == guesses[j]) {
        printf("%c ", word[i]);
        printed = true;
      }
    }
    if (printed == false) printf("_ ");
  }
  printf("\n");
}

int count_lines(const char* filename) {
  FILE* file = fopen(filename, "r");

  while (file == NULL) {
    printf("Error: file %s not found.\n", filename);
    return -1;
  }

  int count = 0;
  int character;

  do {
    character = fgetc(file);
    if (character == '\n') count++;
  } while (character != EOF);

  return count;
}

int random_word(const char* filename, char* word) {
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error: file %s not found.\n", filename);
    return 1;
  }

  srand(time(NULL));

  int upper_bound = count_lines(filename);
  int read_line = rand() % upper_bound + 1;
  int current_line = 1;

  do {
    if (fgets(word, sizeof(word), file) == NULL) {
      printf("Error: can't read line %d.\n", read_line);
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
  char word[BUFFER_SIZE];
  int errors = 0;

  random_word("words.txt", word);
  tolower_str(word);

  char guesses[BUFFER_SIZE];
  initialize_guesses(guesses, word);

  char guess;

  draw_stickman(errors);
  display_current_state(word, guesses);
  printf("Errors: %d\n", errors);

  while (true) {
    printf("Guess: ");
    scanf(" %c", &guess);
    guess = tolower(guess);

    printf("\n");

    if (!check_guess(guess, word, guesses)) errors++;

    fflush(stdin);

    draw_stickman(errors);
    display_current_state(word, guesses);
    printf("Errors: %d\n", errors);

    if (errors == 3) {
      printf("YOU LOSE!\n");
      printf("The word was: %s", word);
      break;
    }
    if (check_guesses(guess, word, guesses) == true) {
      printf("YOU WIN!\n");
      break;
    }
  }

  return 0;
}
