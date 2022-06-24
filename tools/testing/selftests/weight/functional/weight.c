#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define USER_UID 1000
#define INVALID_UID_1 -7
#define INVALID_UID_2 123456
#define INVALID_WEIGHT -327

// Get / Set current user
// Esperado:
// Root:     Peso = 10/4 -> Peso = 8 -> Peso = 4
// Not-root: Peso = 10/? -> Erro de acesso
int teste1()
{
	int current_weight = syscall(451, -1);
	printf("Testando com o UID %d\n", getuid());
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 2;
	}

	printf("Peso do usuário atual: %d\n", current_weight);

	int ret = syscall(452, -1, 8);
	if (ret == -1 && errno == EACCES) {
		printf("Erro ao setar peso do usuário: Apenas o root tem permissão para tal!\n");
		return 3;
	} else if (ret == -1 && errno == EINVAL) {
		printf("Erro ao setar peso do usuário: Peso inválido!\n");
		return 4;
	} else if (ret != 0) {
		printf("Retorno errado da syscall!\n");
		return 9;
	}

	current_weight = syscall(451, -1);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 5;
	}

	printf("Peso do usuário atual: %d\n", current_weight);

	ret = syscall(452, -1, 4);
	if (ret == -1 && errno == EACCES) {
		printf("Erro ao setar peso do usuário: Apenas o root tem permissão para tal!\n");
		return 6;
	} else if (ret == -1 && errno == EINVAL) {
		printf("Erro ao setar peso do usuário: Peso inválido!\n");
		return 7;
	}

	if (ret != 0) {
		printf("Retorno errado da syscall!\n");
		return 9;
	}

	current_weight = syscall(451, -1);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 8;
	}

	printf("Peso do usuário atual: %d\n", current_weight);

	return 0;
}



// Get / Set another user
int teste2()
{
	int user_weight = syscall(451, USER_UID);

	printf("Testando com o UID %d\n", USER_UID);
	if (user_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 2;
	}

	int current_weight = syscall(451, getuid());

	printf("Peso do usuário atual: %d\n", current_weight);
	printf("Peso do usuário de UID %d: %d\n", USER_UID, user_weight);

	int ret = syscall(452, USER_UID, 8);
	if (ret == -1 && errno == EACCES) {
		printf("Erro ao setar peso do usuário: Apenas o root tem permissão para tal!\n");
		return 3;
	} else if (ret == -1 && errno == EINVAL) {
		printf("Erro ao setar peso do usuário: Peso inválido!\n");
		return 4;
	} else if (ret != 0) {
		printf("Retorno errado da syscall!\n");
		return 9;
	}

	user_weight = syscall(451, USER_UID);
	if (user_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 5;
	}
	current_weight = syscall(451, getuid());

	printf("Peso do usuário atual: %d\n", current_weight);
	printf("Peso do usuário de UID %d: %d\n", USER_UID, user_weight);

	return 0;
}



// Invalid UID 1
int teste3()
{
	int current_weight = syscall(451, INVALID_UID_1);
	printf("Testando com o UID %d\n", INVALID_UID_1);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 2;
	}

	printf("Peso do usuário de UID %d: %d\n", USER_UID, current_weight);

	int ret = syscall(452, USER_UID, 8);
	if (ret == -1 && errno == EACCES) {
		printf("Erro ao setar peso do usuário: Apenas o root tem permissão para tal!\n");
		return 3;
	} else if (ret == -1 && errno == EINVAL) {
		printf("Erro ao setar peso do usuário: Peso inválido!\n");
		return 4;
	} else if (ret != 0) {
		printf("Retorno errado da syscall!\n");
		return 9;
	}

	current_weight = syscall(451, USER_UID);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 5;
	}

	printf("Peso do usuário de UID %d: %d\n", USER_UID, current_weight);

	return 0;
}



// Invalid UID 2
int teste4()
{
	int current_weight = syscall(451, INVALID_UID_2);
	printf("Testando com o UID %d\n", INVALID_UID_2);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 2;
	}

	printf("Peso do usuário de UID %d: %d\n", USER_UID, current_weight);

	int ret = syscall(452, USER_UID, 8);
	if (ret == -1 && errno == EACCES) {
		printf("Erro ao setar peso do usuário: Apenas o root tem permissão para tal!\n");
		return 3;
	} else if (ret == -1 && errno == EINVAL) {
		printf("Erro ao setar peso do usuário: Peso inválido!\n");
		return 4;
	} else if (ret != 0) {
		printf("Retorno errado da syscall!\n");
		return 9;
	}

	current_weight = syscall(451, USER_UID);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 5;
	}

	printf("Peso do usuário de UID %d: %d\n", USER_UID, current_weight);

	return 0;
}



// Invalid weight
int teste5()
{
	int current_weight = syscall(451, getuid());
	printf("Testando com o UID %d\n", getuid());
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 2;
	}

	printf("Peso do usuário de UID %d: %d\n", getuid(), current_weight);

	int ret = syscall(452, getuid(), INVALID_WEIGHT);
	if (ret == -1 && errno == EACCES) {
		printf("Erro ao setar peso do usuário: Apenas o root tem permissão para tal!\n");
		return 3;
	} else if (ret == -1 && errno == EINVAL) {
		printf("Erro ao setar peso do usuário: Peso inválido!\n");
		return 4;
	} else if (ret != 0) {
		printf("Retorno errado da syscall!\n");
		return 9;
	}

	current_weight = syscall(451, USER_UID);
	if (current_weight == -1 && errno == EINVAL) {
		printf("Erro ao encontrar usuário!\n");
		return 5;
	}

	printf("Peso do usuário de UID %d: %d\n", USER_UID, current_weight);

	return 0;
}



int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Uso: ./run.sh {número do teste}\n");
		return 1;
	}

	int num = atoi(argv[1]);
	switch (num) {
	default:
	case 1:
		return teste1();
	case 2:
		return teste2();
	case 3:
		return teste3();
	case 4:
		return teste4();
	case 5:
		return teste5();
	}

	return 0;
}
