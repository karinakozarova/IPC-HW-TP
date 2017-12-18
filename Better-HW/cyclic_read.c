#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#define SIZE 4096

struct buffer_t
{
	volatile uint64_t data[SIZE];
	volatile uint64_t pos;
};

int main(){
	int sfd = shm_open("temporary", O_RDONLY, S_IRWXU);
	struct buffer_t* shared = mmap(NULL, sizeof(struct buffer_t), PROT_READ, MAP_SHARED, sfd, 0);
	//sleep(1); 
	uint64_t pos = (shared->pos)%4096;
	while(1)
	{
		if(shared->pos == pos){
			sleep(1);
			continue;
		}
		printf("%d\n", shared->data[pos]);
		++pos %= 4096;
	}
	munmap(shared, sizeof(struct buffer_t));
	close(sfd);
	return 0;
}