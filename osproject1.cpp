#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

struct lock
{
	int lock;
	lock_init(struct lock *lock)
	{
	   lock=NULL;	
	}
	lock_acquire(struct lock *lock)
	{
		lock=NULL;
	}
	lock_release(struct lock *lock)
	{
		lock=1;
	}
	struct condition
   {
	int cond;
	cond_init(struct condition *cond)
	{
		cond=NULL;
	}
	cond_wait(struct condition *cond,struct lock *lock)
    {
    	cond=NULL;
    	lock=NULL;
	}
	cond_signal(struct condition *cond,struct lock *lock)
	{
		cond=1;
		lock=NULL;
	}
	cond_broadcast(struct condition *cond,struct lock *lock)
	{
		cond=1;
		lock=1;
	}
  }s;
}l;
void station_init(struct station *station)
{
  station_out_passengers = 0;
  station_in_passengers = 0;
  pthread_cond_init(&(station_train_arrived_cond), NULL);
  pthread_cond_init(&(station_passengers_seated_cond), NULL);
  pthread_cond_init(&(station_train_is_full_cond), NULL);
}


void station_load_train(struct station *station, int count)
{

  l.lock_acquire(struct lock *lock);

  while ((station_out_passengers > 0) && (count > 0)){
    pthread_cond_signal(&(station_train_arrived_cond));
  	count--;
  	pthread_cond_wait(&(station_passengers_seated_cond), &(station_lock));
  }

  if (station_in_passengers > 0)
  	pthread_cond_wait(&(station_train_is_full_cond), &(station_lock));

  l.lock_release(struct lock *lock);
}

void
station_wait_for_train(struct station *station)
{
  l.lock(struct lock *lock);

  station_out_passengers++;
  pthread_cond_wait(&(station_train_arrived_cond), &(station_lock));
  station_out_passengers--;
  station_in_passengers++;

  l.lock_release(struct lock *lock);
   
  pthread_cond_signal(&(station_passengers_seated_cond));
}


void station_on_board(struct station *station)
{
  l.lock_release(struct lock *lock);

  station_in_passengers--;

  l.lock(struct lock *lock)

  if (station_in_passengers == 0)
  	pthread_cond_broadcast(&(station_train_is_full_cond));

