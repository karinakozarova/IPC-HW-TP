#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#define SIZE 4096

struct buffer_t
{
	volatile uint64_t data[SIZE];
	volatile uint64_t pos;
};

int main()
{
	int sfd = shm_open("temporary", O_CREAT | O_RDWR, S_IRWXU);
	int res = ftruncate(sfd, sizeof(struct buffer_t));

	struct buffer_t* shared = mmap(NULL, sizeof(struct buffer_t), PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);
	shared->pos %= 4096;
	for(int i=0; i<1; i++)
	{ 
		shared->data[shared->pos] = i;
		shared->pos++;
		shared->pos%=4096;
	}	

	munmap(shared, sizeof(struct buffer_t));
	close(sfd);
	return 0;
}

