#include "program.c"

#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if(argc < 2) return 1;
    char* directory = argv[1];

    // Read directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (directory)) != NULL) {
        strcat(directory, "/");
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            //Find file format
            uint32_t i = 0;
            while(ent->d_name[i++] != '.');
            if(ent->d_name[i] != 'b') continue; // Only check bin files

            // Execute program
            char binFilePath[1000];
            strcpy(binFilePath, directory);
            strcat(binFilePath, ent->d_name);
            //printf("Binary file: %s\n", binFilePath);
            executeProgram(binFilePath, 0);

            // Check against registry file
            char resFilePath[1000];
            strcpy(resFilePath, directory);
            strncat(resFilePath, ent->d_name, strlen(ent->d_name) - 3);
            strcat(resFilePath, "res");
            
            //printf("Res file: %s\n", resFilePath);

            FILE* file = fopen(resFilePath, "r");
            if(file == NULL) {
                printf("Failed to open %s\n", resFilePath);
                continue;
            }

            int success = 1;

            uint32_t value;
            uint8_t reg = 0;
            while(1) {
                if (fread(&value, 4, 1, file) < 1) break;
                uint32_t ourValue = getRegisterUnsigned(reg++);
                if (value != ourValue) {
                    success = 0;
                    printf("Reg x%d is not correct!\n\tCorrect value=%u\n\tOur value=%u\n", reg - 1, value, ourValue);
                }
            };

            if(success) {
                printf("%s executed correctly!\n", ent->d_name);
            } else {
                printf("%s executed with errors! See registers above\n", ent->d_name);
            } 

            // Reset for next test
            reset();
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    
    
    //executeProgram(argv[1]);
    //reset();
}