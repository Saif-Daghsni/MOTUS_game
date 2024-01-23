#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


int isWordInFile(const char *word, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
        return 0;
    }

    char buffer[100];
    while (fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, word) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
void addWord(const char *filename, int length) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "The file is empty.\n");
        return;
    }

    int n;
    ii:
    printf("\n How many words do you want to add: \n");
    if (scanf("%d", &n) == 1) {

        if (n == 0) {
            printf("\n You can't add 0 words.\n");
        } else {
            char word[100];
            clear_input_buffer();
            printf("\n Enter the %d-letter word(s):\n", length);
            for (int i = 0; i < n; i++) {
                wrt:
                printf("\n Enter word number %d: ", i + 1);
                scanf("%s", word);
                int j = 0;
                while (word[j] != '\0') {
                    if (!isalpha(word[j])) {
                        printf("\n The word must consist of letters only");
                        goto wrt;
                    }
                    j++;
                }
                printf("\n");
                if (strlen(word) == length && !isWordInFile(word, filename)) {
                    fprintf(file, "%s\n", word);
                    printf("The word has been added to the file.\n");
                } else {
                    printf("ERROR: The word already exists in the file or does not have %d letters.\n", length);
                    i--;
                }
            }
        }
    } else {

        printf("You have to write a number \n");
        clear_input_buffer();
        goto ii;
    }
    fclose(file);
}
void displayContent(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("The file is empty.\n");
    }
    fseek(file, 0, SEEK_SET);

    char character;
    while ((character = fgetc(file)) != EOF) {
        putchar(character);
    }

    fclose(file);
}
void deleteWordFromFile(const char *filename, const char *wordToDelete) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fprintf(stderr, "Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    char buffer[100];

    // Read each line from the file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove the trailing newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check if the line (word) matches the word to be deleted
        if (strcmp(buffer, wordToDelete) != 0) {
            // If not, write the word to the temporary file
            fprintf(tempFile, "%s\n", buffer);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Reopen the temporary file to transfer its content back to the original file
    tempFile = fopen("temp.txt", "r");
    file = fopen(filename, "w");

    if (tempFile == NULL || file == NULL) {
        fprintf(stderr, "Error opening files.\n");
        return;
    }

    // Transfer content of temp file back to the original file
    while (fgets(buffer, sizeof(buffer), tempFile) != NULL) {
        fprintf(file, "%s", buffer);
    }

    fclose(file);
    fclose(tempFile);

    // Remove the temporary file
    remove("temp.txt");
}
void clear_input_buffer() {
    while (getchar() != '\n');
}
void deleteContent(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open the file.\n");
        return;
    }

    fclose(file);
    printf("The content of the file has been deleted.\n");
}
void deleteWord(const char *filename) {
    char word[50], line[100];
    int t, found = 0;
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("The file is empty.\n");
        goto kk;
    }
    fseek(file, 0, SEEK_SET);
    printf("\nThe content of the file:\n");
    displayContent(filename);
    ii:
    printf("\nHow many words do you want to delete: ");
    if (scanf("%d", &t) == 1) {
        for (int i = 0; i < t; i++) {
            ou:
            fseek(file, 0, SEEK_END);
            if (ftell(file) == 0) {
                goto kk;
            }
            fseek(file, 0, SEEK_SET);
            wrt:
            printf("\nEnter word %d to delete: ", i + 1);
            scanf("%s", word);
            int j = 0;
            while (word[j] != '\0') {
                if (!isalpha(word[j])) {
                    printf("\nThe word must consist of letters only");
                    goto wrt;
                }
                j++;
            }
            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, word) != NULL) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                deleteWordFromFile(filename, word);
                printf("The word has been deleted.\n");
                if (ftell(file) == 0) {
                    printf("The file is empty.\n");
                    goto kk;
                    fseek(file, 0, SEEK_SET);
                } else {
                    printf("\nThe new content of the file:\n");
                    displayContent(filename);
                }
            } else {
                printf("\nThe word '%s' is not present in the file.\n", word);
                goto ou;
            }
        }
    } else {
        printf("\nYou have to write a number ");
        clear_input_buffer();
        goto ii;
    }
    kk:
    fclose(file);
}
void playInterface(const char *filename, int length) {
    FILE *f1;
    int z;
    char tab[5][100], l[50];

    f1 = fopen(filename, "r");
    if (f1 == NULL) {
        perror("Error opening file");
        return;
    }
    fseek(f1, 0, SEEK_END);
    if (ftell(f1) == 0) {
        printf("The file is empty.\n");
        goto io;
    }
    fseek(f1, 0, SEEK_SET);

    char ch[100];
    int i = 0;
    while (fscanf(f1, "%s", ch) != EOF) {
        strcpy(tab[i], ch);
        i++;
    }
    fclose(f1);

    srand(time(NULL));
    int r = rand() % i;
    l[0]=tab[r][0];
    for (int t = 1; t < strlen(tab[r]); t++) {
        l[t]='*';
    }

    printf("Randomly chosen word: %s (for testing purposes)\n", tab[r]);

    int t;
    char ch2[100];
    char tab2[100];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n\n\n\nFIND THE WORD\n\n\n");

    SetConsoleTextAttribute(hConsole, 12);
    printf("%c", tab[r][0]);
    SetConsoleTextAttribute(hConsole, 7);

    for (t = 1; t < strlen(tab[r]); t++) {
        printf("*");
    }
    printf("\n");

    int som = 50, vrais = 0;

    for (int k = 0; k < 5; k++) {
        if (k != 0) {
            for (int y = 0; y < strlen(tab[r]); y++) {
                if (isalpha(l[y])) {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("%c", l[y]);
                    SetConsoleTextAttribute(hConsole, 7);
                } else {
                    printf("%c", l[y]);
                }
            }
            printf("\n");
        }
    as:
        scanf("%s", &ch2);
        int j = 0;
        while (ch2[j] != '\0') {
            if (!isalpha(ch2[j])) {
                printf("The word must consist of letters only,Try again\n");
                goto as;
            }
            j++;
        }

        deleteWordFromFile(filename, ch2);
        if (strlen(ch2) == strlen(tab[r])) {
            if (strcmp(ch2, tab[r]) == 0) {
                printf("\nCongratulations, you won the game. The score is: %d\n", som);
                return;
            } else if (strcmp(ch2, tab[r]) != 0) {
                for (int i = 0; i < strlen(ch2); i++) {
                    tab2[i] = ch2[i];
                }

                for (int i = 0; i < strlen(tab[r]); i++) {
                    if (tab[r][i] == tab2[i]) {
                        l[i] = tab2[i];
                        SetConsoleTextAttribute(hConsole, 12);
                        printf("%c", tab2[i]);
                        SetConsoleTextAttribute(hConsole, 7);
                        vrais += 1;
                    } else {
                        if (l[i] != tab[r][i]) {
                            l[i] = '*';
                        }
                        int found = 0;
                        for (int j = 0; j < strlen(ch2); j++) {
                            if (tab2[i] == tab[r][j]) {
                                found = 1;
                                break;
                            }
                        }
                        if (found) {
                            SetConsoleTextAttribute(hConsole, 14);
                            printf("%c", tab2[i]);
                            SetConsoleTextAttribute(hConsole, 7);
                        } else {
                            SetConsoleTextAttribute(hConsole, 9);
                            printf("%c", tab2[i]);
                            SetConsoleTextAttribute(hConsole, 7);
                        }
                    }
                }
                if (k == 4) {
                    printf("\nNumber of remaining attempts: %d  The score is: %d\n", 5 - k - 1, som);
                    printf("\nSorry, you have exhausted all your attempts. The word was: %s\n", tab[r]);
                    return;
                }
                printf("\n");
                printf("\nNumber of remaining attempts: %d  The score is: %d\n", 5 - k - 1, som);
                printf("______\n");
            }
        } else {
            printf("The word does not have the specified dimension.\n");
            printf("Number of remaining attempts: %d  The score is: %d\n", 5 - k - 1, som);
            printf("______\n");
        }
        som -= 10;
    }
    io:
}
void playInterface2(const char *filename, int length) {
    FILE *f1;
    int z;
    char tab[5][100], l[50];

    f1 = fopen(filename, "r");
    if (f1 == NULL) {
        perror("Error opening file");
        return;
    }
    fseek(f1, 0, SEEK_END);
    if (ftell(f1) == 0) {
        printf("The file is empty.\n");
    }
    fseek(f1, 0, SEEK_SET);
    char ch[100];
    int i = 0;
    while (fscanf(f1, "%s", ch) != EOF) {
        strcpy(tab[i], ch);
        i++;
    }
    fclose(f1);

    srand(time(NULL));
    int r = rand() % i;
    l[0]=tab[r][0];
    for (int t = 1; t < strlen(tab[r]); t++) {
        l[t]='*';
    }
    printf("Randomly chosen word: %s\n", tab[r]);

    int t, jo;
    char ch2[100];
    char tab2[100];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n\n\n\nFIND THE WORD\n\n\n");

    jo = 2;
    printf("\nPlayer 1 plays\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("%c", tab[r][0]);
    SetConsoleTextAttribute(hConsole, 7);

    for (t = 1; t < strlen(tab[r]); t++) {
        printf("*");
    }
    printf("\n");

    int y[50], vrais = 0;
    y[1] = 50;
    y[2] = 50;
    for (int k = 0; k < 10; k++) {
        if (jo == 1) {
            jo = 2;
        } else if (jo == 2) {
            jo = 1;
        }
        if (k != 0) {
            printf("\nPlayer %d plays\n\n", jo);
        }
        if (k != 0) {
            for (int y = 0; y < strlen(tab[r]); y++) {
                if (isalpha(l[y])) {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("%c", l[y]);
                    SetConsoleTextAttribute(hConsole, 7);
                } else {
                    printf("%c", l[y]);
                }
            }
            printf("\n");
        }
    as:
        scanf("%s", &ch2);
        int j = 0;
        while (ch2[j] != '\0') {
            if (!isalpha(ch2[j])) {
                printf("The word must consist of letters only,Try again\n");
                goto as;
            }
            j++;
        }
        deleteWordFromFile(filename, ch2);
        if (strlen(ch2) == strlen(tab[r])) {
            if (strcmp(ch2, tab[r]) == 0) {
                printf("\nCongratulations, Player %d wins the game. The score is: %d\n", jo, y[jo]);
                return;
            } else if (strcmp(ch2, tab[r]) != 0) {
                for (int i = 0; i < strlen(ch2); i++) {
                    tab2[i] = ch2[i];
                }

                for (int i = 0; i < strlen(tab[r]); i++) {
                    if (tab[r][i] == tab2[i]) {
                        l[i] = tab2[i];
                        SetConsoleTextAttribute(hConsole, 12);
                        printf("%c", tab2[i]);
                        SetConsoleTextAttribute(hConsole, 7);
                        vrais += 1;
                    } else {
                        if (l[i] != tab[r][i]) {
                            l[i] = '*';
                        }
                        int found = 0;
                        for (int j = 0; j < strlen(ch2); j++) {
                            if (tab2[i] == tab[r][j]) {
                                found = 1;
                                break;
                            }
                        }
                        if (found) {
                            SetConsoleTextAttribute(hConsole, 14);
                            printf("%c", tab2[i]);
                            SetConsoleTextAttribute(hConsole, 7);
                        } else {
                            SetConsoleTextAttribute(hConsole, 9);
                            printf("%c", tab2[i]);
                            SetConsoleTextAttribute(hConsole, 7);
                        }
                    }
                }

                if (k == 9) {
                    printf("\nNumber of remaining attempts: %d  Player %d's score is: %d\n", 5 - k - 1, jo, y[jo]);
                    printf("\nSorry, you have exhausted all your attempts. The word was: %s", tab[r]);
                    printf("\nYou two tied \n\n\n");
                    return;
                }
                printf("\n");
                printf("\nNumber of remaining attempts: %d  Player %d's score is: %d\n", 5 - k - 1, jo, y[jo]);
                printf("______\n");
            }
        } else {
            printf("The word does not have the specified dimension.\n");
            printf("Number of remaining attempts: %d  Player %d's score is: %d\n", 5 - k - 1, jo, y[jo]);
            printf("______\n");
        }
        y[jo] -= 10;
    }
}


int main() {
    int x, y, z, q;
    char fn[] = "file1.txt";
    char fa[] = "file2.txt";
    char fb[] = "file3.txt";
    // Creating file1.txt
    FILE *file1 = fopen(fn, "a");
    if (file1 == NULL) {
        fprintf(stderr, "Error creating file1.txt\n");
        return 1;  // Indicate an error
    }
    fclose(file1);

    // Creating file2.txt
    FILE *file2 = fopen(fa, "a");
    if (file2 == NULL) {
        fprintf(stderr, "Error creating file2.txt\n");
        return 1;  // Indicate an error
    }
    fclose(file2);

    // Creating file3.txt
    FILE *file3 = fopen(fb, "a");
    if (file3 == NULL) {
        fprintf(stderr, "Error creating file3.txt\n");
        return 1;  // Indicate an error
    }
    fclose(file3);

    while (1) {
        ee:
        printf("\n ******WELCOME TO MOTUS****** \n\n\n");
        printf("\n Choose:\n 1 Player\n 2 Administrator\n 3 Rules of the game\n 4 Quit \n");
        scanf("%d", &x);
        system("cls");

        if (x == 2) {
            while (1) {
                end:
                printf("\n Choose:\n 1 to add a word\n 2 to display the content of a file\n 3 to delete the entire content of a file\n 4 to delete a word\n 5 To go back\n");
                scanf("%d", &y);
                system("cls");

                switch (y) {
                    case 1:
                        pp:
                        printf("\n Choose:\n 1 to add words the 4 letter file\n 2 to add words the 5 letter file\n 3 to add words the 6 letter file\n 4 to step back\n");
                        scanf("%d", &z);
                        system("cls");

                        switch (z) {
                            case 1:
                                addWord(fn, 4);
                                goto pp;
                                break;
                            case 2:
                                addWord(fa, 5);
                                goto pp;
                                break;
                            case 3:
                                addWord(fb, 6);
                                goto pp;
                                break;
                            case 4:
                                break;
                            default:
                                printf("Invalid choice.\n");
                                goto pp;
                        }
                        break;
                    case 2:
                        ll:
                        printf("\n Enter:\n 1 to display the content of the 4-letter file\n 2 to display the content of the 5-letter file\n 3 to display the content of the 6-letter file\n 4 to go back\n");
                        scanf("%d", &z);
                        system("cls");

                        switch (z) {
                            case 1:
                                displayContent(fn);
                                goto ll;
                                break;
                            case 2:
                                displayContent(fa);
                                goto ll;
                                break;
                            case 3:
                                displayContent(fb);
                                goto ll;
                                break;
                            case 4:
                                break;
                            default:
                                printf("Invalid choice.\n");
                        }
                        break;
                    case 3:
                        ss:
                        printf("\n Enter:\n 1 to delete the 4-letter file\n 2 to delete the 5-letter file\n 3 to delete the 6-letter file\n 4 To go back\n");
                        scanf("%d", &z);
                        system("cls");

                        switch (z) {
                            case 1:
                                deleteContent(fn);
                                goto ss;
                                break;
                            case 2:
                                deleteContent(fa);
                                goto ss;
                                break;
                            case 3:
                                deleteContent(fb);
                                goto ss;
                                break;
                            case 4:
                                goto end;
                                break;
                            default:
                                printf("Invalid choice.\n");
                        }
                        break;
                    case 4:
                        oo:
                        printf("\n Enter:\n 1 to delete a word from the 4-letter file\n 2 to delete a word from the 5-letter file\n 3 to delete a word from the 6-letter file\n 4 To go back\n");
                        scanf("%d", &z);
                        system("cls");

                        switch (z) {
                            case 1:
                                deleteWord(fn);
                                goto oo;
                                break;
                            case 2:
                                deleteWord(fa);
                                goto oo;
                                break;
                            case 3:
                                deleteWord(fb);
                                goto oo;
                                break;
                            case 4:
                                break;
                            default:
                                printf("Invalid choice.\n");
                                goto oo;
                        }
                        break;
                        goto ee;
                    case 5:
                        goto ee;
                    default:
                        printf("Invalid choice.\n");
                }
            }
            goto ee;
        }
        else if (x == 1) {

            wx:
            printf("Enter the mode: \n 1 for 1 player \n 2 for 2 players \n 3 To go back\n");
            scanf("%d",&q);

            switch (q){
                case 1:

                system("cls");
                io:
                printf("Enter: \n 1 for level 1 of 4 letters \n 2 for level 2 of 5 letters \n 3 for level 3 of 6 letters \n 4 To go back\n ");
                scanf("%d", &z);
                system("cls");

                switch (z) {
                    case 1:
                        system("color 07");
                        playInterface(fn, 4);
                        goto ee;
                        break;
                    case 2:
                        system("color 07");
                        playInterface(fa, 5);
                        goto ee;
                        break;
                    case 3:
                        system("color 07");
                        playInterface(fb, 6);
                        goto ee;
                        break;
                    case 4:
                        system("color 07");
                        goto wx;
                        break;
                    default:
                        printf("Invalid choice.\n");
                        goto io;
                }

                break;
                case 2:

                    system("cls");
                    xx:
                    printf("Enter: \n 1 for level 1 of 4 letters \n 2 for level 2 of 5 letters \n 3 for level 3 of 6 letters  \n 4 To go back\n ");
                    scanf("%d", &z);
                    system("cls");
                    switch (z) {
                        case 1:
                            system("color 07");
                            playInterface2(fn, 4);
                            goto ee;
                            break;
                        case 2:
                            system("color 07");
                            playInterface2(fa, 5);
                            goto ee;
                            break;
                        case 3:
                            system("color 07");
                            playInterface2(fb, 6);
                            goto ee;
                            break;
                        case 4:
                            system("color 07");
                            goto wx;
                            break;
                        default:
                            printf("Invalid choice.\n");
                            goto xx;
                    }
                case 3:
                    system("cls");
                    goto ee;
                    break;
                default:
                    printf("Invalid choice.\n");
                    goto wx;
            }
        }
        else if (x==3)
        {
            int n;
            printf("The rules of the game are as follows: \n\n- You choose the game style and difficulty level \n\n- A random word will be chosen based on the chosen level \n\n- Only the first letter will be shown to you, and you must find the rest of the letters \n\n- After entering the word you chose, the correct letter will be colored red, the incorrect letter will be colored blue, and the correct letter but not in its place will be colored yellow \n\n- You have 5 attempts \n\n- You will lose 10 points each time you fail to find the word \n\n-The word you played will be deleted from the file\n\n- In two-player mode, control will switch between you and the winner who finds the word first");
            gg:
            printf("\n\n\n\n Click : 0 to go back");
            scanf("%d",&n);
            if(n==0)
            {
                system("cls");
                goto ee;
            }
            else
            {
                printf("\n \n \n Invalid choice.\n");
                goto gg;
            }
        }
        else if (x==4)
        {
            printf("GOOD BYE\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
            goto ee;
        }

    }
    return 0;
}
