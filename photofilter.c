#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

char* findNumbers(const char* input) {
    regex_t regex;
    int ret;

    // Define the regular expression pattern for numbers
    const char* pattern = "[0-9]+";

    // Compile the regular expression
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Failed to compile the regular expression.\n");
        return NULL;
    }

    // Perform the regex match
    regmatch_t matches;
    const char* current = input;
    size_t resultSize = 0;
    char* resultString = NULL;
    while (regexec(&regex, current, 1, &matches, 0) == 0) {
        int numStart = matches.rm_so;
        int numEnd = matches.rm_eo - 1;
        int numLength = numEnd - numStart + 1;
        // Output the matched number
        printf("Match found: %.*s\n", (int)(matches.rm_eo - matches.rm_so), current + matches.rm_so);
        // allocate the memory for result string
        resultString = (char*)realloc(resultString, (resultSize + numLength + 1) * sizeof(char));
        strncpy(resultString + resultSize, &current[numStart], numLength);
        resultSize += numLength;
        resultString[resultSize] = '\0';

        printf("Match start offset: %lld\n", matches.rm_so);
        printf("Match end offset: %lld\n", matches.rm_eo);

        // Move to the next position after the match
        current += matches.rm_eo;
    }
    // Clean up the regex resources
    regfree(&regex);
    return resultString;
}

int main() {
    const char* input = "IMG_2022_08_17";

    char* numbers = findNumbers(input);
    if (numbers) {
        printf("Extracted Numbers: %s\n", numbers);
        free(numbers);
    }
    return 0;
}
