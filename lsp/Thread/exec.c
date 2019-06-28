#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("start\n");
	execl("/bin/ls", "ls", "-al",NULL);
	printf("End\n");

	return 0;
}
