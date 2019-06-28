#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include "socket.h"
#include "queue.h"

/* PARAMETER STRUCT */
typedef struct thread_parameter
{
  int s_socket;
  int c_socket; 
}thread_param;

/* GLOBAL ARRAY */
readyarray socket_array;

pthread_mutex_t mutex_lock      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  thread_cond[3]  = PTHREAD_COND_INITIALIZER;


///////////////////////////////////////////////////////////////////////////////
void * socket_operation_routine3(void * data)
{
  while(1)
  {
    pthread_mutex_lock(&mutex_lock);
    pthread_cond_wait(&thread_cond[2], &mutex_lock);
    printf("[in socket_operation_routine3 wake up !!\n");
    pthread_mutex_unlock(&mutex_lock);
    break;
  }
}
///////////////////////////////////////////////////////////////////////////////
void * socket_operation_routine2(void * data)
{
  while(1)
  {
    pthread_mutex_lock(&mutex_lock);
    pthread_cond_wait(&thread_cond[1], &mutex_lock);
    printf("[in socket_operation_routine2 wake up !!\n");
    pthread_mutex_unlock(&mutex_lock);
    break;
  }
}
///////////////////////////////////////////////////////////////////////////////
void * socket_operation_routine1(void * data)
{
  while(1)
  {
    pthread_mutex_lock(&mutex_lock);
    pthread_cond_wait(&thread_cond[0], &mutex_lock);
    printf("[in socket_operation_routine1 wake up !!\n");
    pthread_mutex_unlock(&mutex_lock);
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
void * accept_check_thread(void * data)
{ 
  thread_param * temp = (thread_param*)data; 
 
  while(1)
  {
    if ((temp->c_socket = socket_accept(&temp->s_socket)) == -1)
    { 
      printf("Accept Error!!");
      return ;
    }
    enqueue(&socket_array, &(temp->c_socket));
  } 
}
///////////////////////////////////////////////////////////////////////////////
void socket_array_setting(socket_state * s_array)
{
  int i; 
  for(i=0;i<BUFFER_SIZE;i++)
  {
    s_array[i].state = SOCKET_NOT_EXIST;
    s_array[i].socket = EMPTY;
  }
}
///////////////////////////////////////////////////////////////////////////////
void main()
{
  int status, count;
  pthread_t thread_ids[4];
  thread_param param;
  socket_state socket_states[BUFFER_SIZE];
 
  count = 0;
 
  socket_array_setting(socket_states);   
  queue_setting(&socket_array, socket_states);
 
  if ((param.s_socket = socket_settings()) == -1)
  {
    printf("Setting Error.\n");
    return;
  } 
 
  /* Accept Check Thread */
  pthread_create(&thread_ids[0], NULL, accept_check_thread, (void*)&param );
 
  /* Socket Operation Threads */
  pthread_create(&thread_ids[1], NULL, socket_operation_routine1, NULL);
  pthread_create(&thread_ids[2], NULL, socket_operation_routine2, NULL);
  pthread_create(&thread_ids[3], NULL, socket_operation_routine3, NULL);
 
  while(1)
  {
    if (( count = getsize(&socket_array)) != 0)
    {
      pthread_mutex_lock(&mutex_lock);
      pthread_cond_signal(&thread_cond[(count - 1)%3]);
      pthread_mutex_unlock(&mutex_lock);     
    }
  }
 
  pthread_join(thread_ids[0], (void **) &status);
  pthread_join(thread_ids[1], (void **) &status);
  pthread_join(thread_ids[2], (void **) &status);
  pthread_join(thread_ids[3], (void **) &status);

  socket_close(&param.s_socket);
}
