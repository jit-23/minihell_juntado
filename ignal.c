#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static void handle_it(int x)
{
	if (x == SIGINT)
	{
		printf("\n");
	}
}

int main(void)
{
	struct sigaction sa_ign;
	struct sigaction sa;
	memset(&sa_ign, 0,sizeof(sa_ign));
	memset(&sa, 0,sizeof(sa));
	
	sa_ign.sa_handler = SIG_IGN;
	sa_ign.sa_handler = handle_it;
	sigaction(SIGQUIT, &sa_ign, NULL);
	sigaction(SIGINT, &handle_it, NULL);

	while(1)
	{
		printf(".\n");
		sleep(1);
	}
	return 0;
}
