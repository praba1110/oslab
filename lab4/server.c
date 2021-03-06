#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE     27
void die(char *s)
{
perror(s);
exit(1);
}
int main()
{
int shmid,i;
key_t key;
char *shm, *s;
key = 5682;
if ((shmid = shmget(key, 50, IPC_CREAT | 0666)) < 0)
die("shmget");
struct shmid_ds * info = malloc(sizeof(struct shmid_ds));
int ab = shmctl(shmid,IPC_STAT,info);
pid_t p = info->shm_cpid;
time_t t = info -> shm_atime;
printf("shmid %d \n%d\n",shmid,ab);
printf("process %d\n",p);
printf("Last attach time %d \n",t);
if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
die("shmat");
while(1){
	s = shm;
	printf("Server Process: ");
	char a[50];
	scanf("%s",a);
	s++;
	for (i = 0; a[i]!='\0'; i++)
	*s++ = a[i];
	*s = '\0';
	*shm = '#';
	/*
	* Wait until the other process
	* changes the first character of our memory
	* to '*', indicating that it has read what
	* we put there.
	*/
	while (*shm != '*')
	sleep(1);
	printf("Client Process: ");
	for (s = shm+1; *s != '\0'; s++)
	putchar(*s);
	putchar('\n');
}
shmdt(shm);
shmctl(shmid,IPC_RMID,NULL);
exit(0);
}
