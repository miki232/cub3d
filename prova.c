#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

bool is_map_valid(char map[MAX_ROWS][MAX_COLS], int rows, int cols) {
    // Calculate the maximum width and height of the map
    int max_width = 0;
    for (int i = 0; i < rows; i++) {
        int width = strlen(map[i]);
        if (width > max_width) {
            max_width = width;
        }
    }
    int max_height = rows;

    // Pad the map with dummy cells to make it rectangular
    char padded_map[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < max_height; i++) {
        for (int j = 0; j < max_width; j++) {
            if (i >= rows || j >= strlen(map[i])) {
                padded_map[i][j] = ' ';
            } else {
                padded_map[i][j] = map[i][j];
            }
        }
    }

    // Verify the padded map
    for (int i = 0; i < max_height; i++) {
        // Verify the first and last columns
        if (padded_map[i][0] != '1' || padded_map[i][max_width-1] != '1') {
            return false;
        }
        // Verify the cells in the middle
        for (int j = 1; j < max_width-1; j++) {
            if (i == 0 || i == max_height-1) {
                // Verify the first and last rows
                if (padded_map[i][j] != '1') {
                    return false;
                }
            } else {
                // Verify the cells in the middle
                if (padded_map[i][j] != '0' && padded_map[i][j] != '1') {
                    return false;
                }
            }
        }
    }

    // The map is valid
    return true;
}

int num_spots = 0;
int num_numbers = 0;

void update_probabilities(char *row) {
    bool in_number = false;

    for (int i = 0; i < strlen(row); i++) {
        char c = row[i];
        if (c == ' ') {
            num_spots++;
            in_number = false;
        } else {
            if (!in_number) {
                num_numbers++;
                in_number = true;
            }
        }
    }
}

double calculate_probabilities() {
    double prob_spaces = (double) num_spots / (double) num_numbers;
    double prob_numbers = 1 - prob_spaces;

    return prob_numbers > prob_spaces ? prob_numbers : prob_spaces;
}

int main() {
    char map[MAX_ROWS][MAX_COLS] = {
"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1",
"1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1",
"1 0 1 1 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1",
"1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1",
"1 0 1 1 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1",
"1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 1 1 1 0 1 1 1 1 0 0 0 1",
"1 1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 1 1 0 0 0 0 0 0 1 0 0 0 1",
"1 1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 1 1 0 1 0 1 0 0 1 0 0 0 1",
"1 1 0 0 0 0 0 0 1 1 0 1 0 1 0 1 1 1 0 0 0 0 0 0 1 0 0 0 1",
"1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 1 0 0 0 1",
"1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 2 0 1 0 0 2 0 0 0 1",
"1 1 0 0 0 0 0 0 1 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1",
"1 1 1 1 0 1 1 1 1 1 0 1 0 1 0 0 0 0 0 0 2 0 2 0 0 0 0 0 1",
"1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 1",
"1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0 0 1 0 0 1",
"1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 1",
"1 0 0 0 0 0 0 0 0 0 1 1 0 1 0 0 0 0 0 0 N 0 0 0 0 0 0 0 1",
"1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 1",
"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
    };
    int rows = 14;
    int cols = 6;
    double prob = 0;
    int i = 0;
    while (i < rows)
    {
        update_probabilities(map[i]);
        i++;
    }
    prob = calculate_probabilities();
    printf("The probability of the map is: %f\n", prob);
    bool is_valid = is_map_valid(map, rows, cols);
    if (prob > 1) {
        printf("The map has no spaces.\n");
    } else {
        printf("The map has spaces.\n");
    }
    return 0;
}
// int main() {
//     int rows, cols;
//     rows = 14;
//     cols = 34;
//     char *map[14] = {
//     "        1111111111111111111111111",
//     "        1000000000110000000000001",
//     "        1011000001110000000000001",
//     "        1001000000000000000000001",
//     "111111111011000001110000000000001",
//     "100000000011000001110111111111111",
//     "11110111111111011100000010001",
//     "11110111111111011101010010001",
//     "11000000110101011100000010001",
//     "10000000000000001100000010001",
//     "10000000000000001101010010001",
//     "1100000111010101111101111010111",
//     "11110111 1110101 101111010001",
//     "11111111 1111111 111111111111"
// };
//     if (is_valid_map(map, rows, cols)) {
//         printf("La mappa è valida.\n");
//     } else {
//         printf("La mappa non è valida.\n");
//     }
//     // Liberazione della memoria della mappa
//     // for (int i = 0; i < rows; i++) {
//     //     free(map[i]);
//     // }
//     // free(map);
//     return 0;
// }