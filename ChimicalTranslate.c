#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isPrefix(char *str, char *element) {
    while (*element && *str) {
        if (tolower(*element++) != tolower(*str++))
            return 0;
    }
    return *element == '\0';
}

char *PrefixMatch(int i, char *str, char **elements) {
    if (isPrefix(str, elements[i]))
        return elements[i];
    return NULL;
}

int elementize(char *str, char **elements, char **memo, char *solutie, int dim, FILE *out, int j) {
    if (*str == '\0') {
        fprintf(out, "%s\n", solutie);
        return 1;
    }

    for (int i = 0; i < j; i++) {
        if (strcmp(memo[i], str) == 0 && strlen(memo[i]) == dim) {
            return 2;
        }
    }

    for (int i = 0; i < 115; i++) {
        char *singleElement = PrefixMatch(i, str, elements);
        if (singleElement != NULL) {
            char *reminder = str + strlen(singleElement);
            char solutieNoua[100];
            strcpy(solutieNoua, solutie);
            strcat(solutieNoua, singleElement);
            strcat(solutieNoua, " ");

            elementize(reminder, elements, memo, solutieNoua, dim, out, j);

            strcpy(memo[j], str);
            j++;
        }
    }
}

int main() {
    int j = 0;
    char **memo = (char **)calloc(100, sizeof(char *));
    for (int i = 0; i < 100; i++)
        memo[i] = (char *)calloc(100, sizeof(char)); 
    char *elements[115] = { "Uut", "Uuq", "Uup", "Uuh", "Uus", "Uuo",
                            "He", "Li", "Be", "Ne", "Na", "Mg", "Al",
                            "Si", "Cl", "Ar", "Ca", "Sc", "Ti", "Cr",
                            "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga",
                            "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr",
                            "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd",
                            "Ag", "Cd", "In", "Sn", "Sb", "Te", "Xe",
                            "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm",
                            "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er",
                            "Tm", "Yb", "Lu", "Hf", "Ta", "Re", "Os",
                            "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi",
                            "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
                            "Pa", "Np", "Pu", "Am", "Cm", "Bk", "Cf",
                            "Es", "Fm", "Md", "No", "Lr", "Rf", "Db",
                            "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn",
                            "H", "B", "C", "N", "O", "F", "P",
                            "S", "K", "I", "U" };

    FILE *in = fopen("input.in", "r");
    if (!in) {
        printf("Error opening the input file!");
        return 1;
    }

    char cuv[100], sep[3] = " ";
    char *str = (char *)calloc(100, sizeof(char));
    if (fgets(str, 100, in) == NULL) {
        printf("Error reading from the input file or the file is empty!");
        fclose(in);
        return 1;
    }
    fclose(in);
    
    if (str) {
        int dim;
        FILE *out = fopen("output.txt", "w");
        if (!out) {
            printf("Error opening the output file!");
            return 1;
        }

        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
    
        char *token = strtok(str, sep);
        while (token) {
            dim = strlen(token);
            fprintf(out, "->%s\n", token);
            int filePosition = ftell(out);
            elementize(token, elements, memo, "", dim, out, j);
            if(filePosition == ftell(out)) 
                fprintf(out, "No solutie found\n");
            token = strtok(NULL, sep);
        }
        fclose(out);
    }

    for (int i = 0; i < 100; i++) {
        free(memo[i]);
    }
    free(memo);
    free(str);

    return 0;
}
