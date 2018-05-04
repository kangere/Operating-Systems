#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

sem_t agentSem, pusher_sem;

sem_t smokers[3];

char* types[3] = {"tobacco paper","tobacco matches","paper matches"};
 bool table_items[3] = {false,false,false};

 sem_t pushers[3];

 void* smoker(void *arg)
 {
 	int smoker_id = *(int*) arg;
 	int type_id = smoker_id % 3;

 	for(int i =0; i < 3; i++)
 	{
 		printf("Smoker %d Waiting for %s\n",type_id,types[type_id]);

 		sem_wait(&smokers[type_id]);

 		printf("Smoker %d now making cigarette\n",smoker_id );
 		usleep(rand() % 50000);
 		sem_post(&agentSem);

 		printf("Smoker %d now smoking\n", smoker_id);
 		usleep(rand() % 50000);
 	}

 	return NULL;
 }

void* pusher(void* arg)
{
	int pusher_id = *(int*) arg;

	for (int i = 0; i < 12; ++i)
	{
		
		sem_wait(&pushers[pusher_id]);
		sem_wait(&pusher_sem);

		
		if (table_items[(pusher_id + 1) % 3])
		{
			table_items[(pusher_id + 1) % 3] = false;
			sem_post(&smokers[(pusher_id + 2) % 3]);
		}
		else if (table_items[(pusher_id + 2) % 3])
		{
			table_items[(pusher_id + 2) % 3] = false;
			sem_post(&smokers[(pusher_id + 1) % 3]);
		}
		else
		{
			
			table_items[pusher_id] = true;
		}

		sem_post(&pusher_sem);
	}

	return NULL;

}

void* agent(void* arg)
{
	int agent_id = *(int*) arg;

	for (int i = 0; i < 6; ++i)
	{
		usleep(rand() % 200000);

		// Wait for a lock on the agent
		sem_wait(&agentSem);

		// Release the items this agent gives out
		sem_post(&pushers[agent_id]);
		sem_post(&pushers[(agent_id + 1) % 3]);

		// Say what type of items we just put on the table
		printf("Agent %d giving out %s\n",
			agent_id, types[(agent_id + 2) % 3]);
	}

	return NULL;
}

int main(void)
{
	
	srand(time(NULL));

	
	sem_init(&agentSem, 0, 1);

	
	sem_init(&pusher_sem, 0, 1);

	
	for (int i = 0; i < 3; ++i)
	{
		sem_init(&smokers[i], 0, 0);
		sem_init(&pushers[i], 0, 0);
	}



	
	int smoker_ids[6];

	pthread_t smoker_threads[6];

	
	for (int i = 0; i < 6; ++i)
	{
		smoker_ids[i] = i;

		if (pthread_create(&smoker_threads[i], NULL, smoker, &smoker_ids[i]) == EAGAIN)
		{
			perror("Insufficient resources to create thread");
			return 0;
		}
	}

	
	int pusher_ids[6];

	pthread_t pusher_threads[6];

	for (int i = 0; i < 3; ++i)
	{
		pusher_ids[i] = i;

		if (pthread_create(&pusher_threads[i], NULL, pusher, &pusher_ids[i]) == EAGAIN)
		{
			perror("Insufficient resources to create thread");
			return 0;
		}
	}

	
	int agent_ids[6];

	pthread_t agent_threads[6];

	for (int i = 0; i < 3; ++i)
	{
		agent_ids[i] =i;

		if (pthread_create(&agent_threads[i], NULL, agent, &agent_ids[i]) == EAGAIN)
		{
			perror("Insufficient resources to create thread");
			return 0;
		}
	}

	
	for (int i = 0; i < 6; ++i)
	{
		pthread_join(smoker_threads[i], NULL);
	}

	return 0;
}