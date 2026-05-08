#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <time.h>

/*
# FakeOS
To run main.exe you need to create : 
AceOS/
│
├── main.c (optional)
├── main.exe
├── files/
├── users/
├── logs/
├── config/
└── ai/
*/
#define MAX 256
#define RAM_TOTAL 512

int running = 1;
int ramUsed = 120;

char username[50] = "Ace";
char currentPath[100] = "AceOS:/";
char theme[20] = "green";

void bootScreen();
void shell();
void help();
void createFile();
void writeFile();
void readFile();
void deleteFile();
void listFiles();
void fileSize();
void calculator();
void ai();
void settings();
void processManager();
void clearScreen();
void systemInfo();
void logEvent(const char *msg);

int main()
{
    system("mkdir files >nul 2>nul");
    system("mkdir logs >nul 2>nul");
    system("mkdir config >nul 2>nul");
    system("mkdir users >nul 2>nul");

    bootScreen();
    shell();

    return 0;
}

void bootScreen()
{
    system("color 0A");

    printf("====================================\n");
    printf("         ACEOS X v3.0\n");
    printf("====================================\n\n");

    printf("Loading kernel...\n");
    Sleep(800);

    printf("Loading filesystem...\n");
    Sleep(800);

    printf("Loading AI engine...\n");
    Sleep(800);

    printf("Loading drivers...\n");
    Sleep(800);

    printf("Boot successful.\n\n");

    logEvent("SYSTEM BOOTED");
}

void shell()
{
    char command[MAX];

    while(running)
    {
        printf("\n%s> ", currentPath);

        fgets(command, MAX, stdin);

        command[strcspn(command, "\n")] = 0;

        if(strcmp(command, "help") == 0)
        {
            help();
        }

        else if(strcmp(command, "create") == 0)
        {
            createFile();
        }

        else if(strcmp(command, "write") == 0)
        {
            writeFile();
        }

        else if(strcmp(command, "read") == 0)
        {
            readFile();
        }

        else if(strcmp(command, "delete") == 0)
        {
            deleteFile();
        }

        else if(strcmp(command, "list") == 0)
        {
            listFiles();
        }

        else if(strcmp(command, "size") == 0)
        {
            fileSize();
        }

        else if(strcmp(command, "calc") == 0)
        {
            calculator();
        }

        else if(strcmp(command, "ai") == 0)
        {
            ai();
        }

        else if(strcmp(command, "settings") == 0)
        {
            settings();
        }

        else if(strcmp(command, "taskmgr") == 0)
        {
            processManager();
        }

        else if(strcmp(command, "sysinfo") == 0)
        {
            systemInfo();
        }

        else if(strcmp(command, "clear") == 0)
        {
            clearScreen();
        }

        else if(strcmp(command, "shutdown") == 0)
        {
            printf("Shutting down AceOS...\n");
            logEvent("SYSTEM SHUTDOWN");
            running = 0;
        }

        else
        {
            printf("Unknown command.\n");
        }
    }
}

void help()
{
    printf("\n===== COMMANDS =====\n");
    printf("help       - Show commands\n");
    printf("create     - Create file\n");
    printf("write      - Write file\n");
    printf("read       - Read file\n");
    printf("delete     - Delete file\n");
    printf("list       - List files\n");
    printf("size       - File size\n");
    printf("calc       - Calculator\n");
    printf("ai         - AI assistant\n");
    printf("settings   - System settings\n");
    printf("taskmgr    - Process manager\n");
    printf("sysinfo    - System info\n");
    printf("clear      - Clear screen\n");
    printf("shutdown   - Shutdown OS\n");
}

void createFile()
{
    char filename[100];
    char path[150];

    printf("Enter filename: ");
    scanf("%s", filename);
    getchar();

    sprintf(path, "files/%s", filename);

    FILE *file = fopen(path, "w");

    if(file == NULL)
    {
        printf("Failed to create file.\n");
        return;
    }

    fclose(file);

    printf("File created successfully.\n");

    logEvent("FILE CREATED");
}

void writeFile()
{
    char filename[100];
    char path[150];
    char text[500];

    printf("Enter filename: ");
    scanf("%s", filename);
    getchar();

    sprintf(path, "files/%s", filename);

    FILE *file = fopen(path, "a");

    if(file == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    fprintf(file, "%s", text);

    fclose(file);

    printf("Data written.\n");

    logEvent("FILE WRITTEN");
}

void readFile()
{
    char filename[100];
    char path[150];
    char line[300];

    printf("Enter filename: ");
    scanf("%s", filename);
    getchar();

    sprintf(path, "files/%s", filename);

    FILE *file = fopen(path, "r");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    printf("\n===== FILE CONTENT =====\n");

    while(fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    printf("\n========================\n");

    fclose(file);
}

void deleteFile()
{
    char filename[100];
    char path[150];

    printf("Enter filename: ");
    scanf("%s", filename);
    getchar();

    sprintf(path, "files/%s", filename);

    if(remove(path) == 0)
    {
        printf("File deleted.\n");
        logEvent("FILE DELETED");
    }
    else
    {
        printf("Delete failed.\n");
    }
}

void listFiles()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("files");

    if(dir == NULL)
    {
        printf("Cannot open folder.\n");
        return;
    }

    printf("\n===== FILES =====\n");

    while((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void fileSize()
{
    char filename[100];
    char path[150];

    printf("Enter filename: ");
    scanf("%s", filename);
    getchar();

    sprintf(path, "files/%s", filename);

    FILE *file = fopen(path, "r");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);

    long size = ftell(file);

    fclose(file);

    printf("File Size: %ld bytes\n", size);
}

void calculator()
{
    int a, b;
    char op;

    printf("Enter calculation: ");
    scanf("%d %c %d", &a, &op, &b);
    getchar();

    switch(op)
    {
        case '+':
            printf("Result: %d\n", a + b);
            break;

        case '-':
            printf("Result: %d\n", a - b);
            break;

        case '*':
            printf("Result: %d\n", a * b);
            break;

        case '/':
            if(b == 0)
            {
                printf("Cannot divide by zero.\n");
            }
            else
            {
                printf("Result: %d\n", a / b);
            }
            break;

        default:
            printf("Invalid operator.\n");
    }
}

void ai()
{
    char input[300];

    printf("\nAceOS AI Started\n");
    printf("Type 'bye' to exit AI\n\n");

    while(1)
    {
        printf("AI> ");

        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        for(int i = 0; input[i]; i++)
        {
            if(input[i] >= 'A' && input[i] <= 'Z')
            {
                input[i] += 32;
            }
        }

        if(strstr(input, "hello"))
        {
            printf("Hello %s.\n", username);
        }

        else if(strstr(input, "time"))
        {
            system("time /t");
        }

        else if(strstr(input, "date"))
        {
            system("date /t");
        }

        else if(strstr(input, "ram"))
        {
            printf("RAM Usage: %dMB / %dMB\n", ramUsed, RAM_TOTAL);
        }

        else if(strstr(input, "your name"))
        {
            printf("I am AceOS AI.\n");
        }

        else if(strcmp(input, "bye") == 0)
        {
            printf("Goodbye.\n");
            break;
        }

        else
        {
            printf("I do not understand.\n");
        }
    }
}

void settings()
{
    int choice;

    printf("\n===== SETTINGS =====\n");
    printf("1. Change Username\n");
    printf("2. Change Theme\n");

    printf("Choice: ");
    scanf("%d", &choice);
    getchar();

    if(choice == 1)
    {
        printf("New Username: ");
        fgets(username, sizeof(username), stdin);

        username[strcspn(username, "\n")] = 0;

        printf("Username updated.\n");
    }

    else if(choice == 2)
    {
        printf("Themes: green blue red white\n");

        printf("Enter theme: ");
        fgets(theme, sizeof(theme), stdin);

        theme[strcspn(theme, "\n")] = 0;

        if(strcmp(theme, "green") == 0)
            system("color 0A");

        else if(strcmp(theme, "blue") == 0)
            system("color 09");

        else if(strcmp(theme, "red") == 0)
            system("color 0C");

        else if(strcmp(theme, "white") == 0)
            system("color 0F");

        printf("Theme updated.\n");
    }
}

void processManager()
{
    printf("\n===== TASK MANAGER =====\n");
    printf("PID   PROCESS       RAM\n");
    printf("1     shell         20MB\n");
    printf("2     ai            50MB\n");
    printf("3     filesystem    35MB\n");
    printf("4     calculator    15MB\n");
}

void systemInfo()
{
    time_t t = time(NULL);

    printf("\n===== SYSTEM INFO =====\n");
    printf("User : %s\n", username);
    printf("Theme: %s\n", theme);
    printf("RAM  : %dMB / %dMB\n", ramUsed, RAM_TOTAL);
    printf("Time : %s", ctime(&t));
}

void clearScreen()
{
    system("cls");
}

void logEvent(const char *msg)
{
    FILE *log = fopen("logs/system.log", "a");

    if(log == NULL)
        return;

    fprintf(log, "%s\n", msg);

    fclose(log);
}
