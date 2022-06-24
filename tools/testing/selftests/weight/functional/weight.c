#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv)
{
    int current_weight = syscall(451, -1);
    if (errno == EINVAL) {
        printf("Erro ao encontrar usuário!");
        return 1;
    }

    printf("Weight for the current user: %d\n", current_weight);

    return 0;
}
