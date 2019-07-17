#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h> // required for malloc

main()
typedef struct _Queue
{
	unsigned char* buffer; 		// Queue of characters
	unsigned char front; 		// Queue front index
	unsigned char back; 		// Queue back index
	unsigned char num_objects;	// Number of objects in queue
	unsigned char capacity;		// Size of the queue
} *Queue;

Queue QueueInit(unsigned char size) 
{
	Queue Q 		= malloc (sizeof(struct _Queue));
	Q->buffer 		= malloc (size * sizeof(unsigned char));
	Q->front 		= 0;
	Q->back			= 0;
	Q->num_objects	= 0;
	Q->capacity		= size;
	
	return Q;
}

unsigned char QueueIsEmpty(Queue Q) 
{
	return (Q->num_objects == 0);
}

unsigned char QueueIsFull(Queue Q) 
{
	return (Q->num_objects == Q->capacity);
}

void QueueMakeEmpty(Queue Q)
{
	Q->front 		= 0;
	Q->back 		= 0;
	Q->num_objects	= 0;
}

unsigned char QueueEnqueue(Queue Q, unsigned char value) 
{
	if(Q->num_objects < Q->capacity)	// If queue is not full
	{
		Q->buffer[Q->back] = value;		// Place data into correct location
		Q->back++;						// Increment back counter
		Q->back %= Q->capacity;			// Modulate according to queue capacity
		Q->num_objects++;				// Increment number of objects
		return 0;						// Return queue is not full (0)
	}
	return 1;							// Else return queue is full (1)
}

unsigned char QueueDequeue(Queue Q) 
{
	if(Q->num_objects > 0)				// If queue is not empty
	{									// Retrieve data from correct location
		unsigned char tmp = Q->buffer[Q->front];	
		Q->buffer[Q->front] = '\0';		// Clear location with null character
		Q->front++;						// Increment front counter
		Q->front %= Q->capacity;		// Modulate according to queue capacity
		Q->num_objects--;				// Decrement number of objects
		return tmp;						// Return data
	}
	return '\0';						// Else return null to indicate empty
}

f(Q->num_objects > 0)				// If queue is not empty
	{									// Retrieve data from correct location
		unsigned char tmp = Q->buffer[Q->front];	
		Q->buffer[Q->front] = '\0';		// Clear location with null character
		Q->front++;						// Increment front counter
		Q->front %= Q->capacity;		// Modulate according to queue capacity
		Q->num_objects--;				// Decrement number of objects
		return tmp;						// Return data
	}
	return '\0';						// Else return null to indicate empty
}

#endif //QUEUE_Hunsigned char QueueDequeue(Queue Q) 
{
	if(Q->num_objects > 0)				// If queue is not empty
	{									// Retrieve data from correct location
		unsigned char tmp = Q->buffer[Q->front];	
		Q->buffer[Q->front] = '\0';		// Clear location with null character
		Q->front++;						// Increment front counter
		Q->front %= Q->capacity;		// Modulate according to queue capacity
		unsigned char QueueDequeue(Queue Q) 
{
	if(Q->num_objects > 0)				// If queue is not empty
	{									// Retrieve data from correct location
		unsigned char tmp = Q->buffer[Q->front];	
		Q->buffer[Q->front] = '\0';		// Clear location with null character
		Q->front++;						// Increment front counter
		Q->front %= Q->capacity;		// Modulate according to queue capacity
		Q->num_objects--;				// Decrement number of objects
		return tmp;						// Return data
	}
	return '\0';						// Else return null to indicate empty
}

#endif //QUEUE_HQ->num_objects--;				// Decrement number of objects
		return tmp;						// Return data
	}
	return '\0';						// Else return null to indicate empty
}

#endif //QUEUE_H#endif //QUEUE_H
unsigned char QueueDequeue(Queue Q) 
{
	if(Q->num_objects > 0)				// If queue is not empty
	{		// Retrieve data from correct location
		unsigned char tmp = Q->buffer[Q->front];	
		Q->buffer[Q->front] = '\0';		// Clear location with null character
		Q->front++;						// Increment front counter
		Q->front %= Q->capacity;		// Modulate according to queue capacity
		Q->num_objects--;				// Decrement number of objects
		return tmp;						// Return data
	}
	return '\0';						// Else return null to indicate empty
}

#endif //QUEUE_H
