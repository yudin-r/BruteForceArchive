#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_password(const char *archive_path, const char *password) {
    char command[512];
    sprintf(command, "7z t -p%s %s > /dev/null 2>&1", password, archive_path);
    int result = system(command);

    if (result == 0) {
        return 1;
    }

    return 0;
}

void bruteforce_password(const char *archive_path) {
    char password[11];
    memset(password, '0', 10);
    password[10] = '\0';

    printf("Брутфорс начат\n");

    while (1) {
        if (check_password(archive_path, password)) {
            printf("Пароль найден: %s\n", password);
            return;
        }

        printf("Попытка: %s\n", password);

        int i = 9;
        while (i >= 0) {
            if (password[i] < '9') {
                password[i]++;
                break;
            } else {
                password[i] = '0';
                i--;
            }
        }

        if (i < 0) {
            break;
        }
    }

    printf("Увы, пароль не найден\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <archive_path>\n", argv[0]);
        return 1;
    }
    const char *archive_path = argv[1];
    printf("Брутфорс архива: %s\n", archive_path);

    bruteforce_password(archive_path);
}
