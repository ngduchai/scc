
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "define.h"
#include <pthread.h>
#include <functional>

namespace SCC {
	
namespace LOCKS {

/* Tournament lock */
class tournament_lock {
private:
	tournament_lock(); // Suppress default constructor
	pthread_mutex_t * _locks;
	pthread_mutex_t _tid_lock;
	int _avai_thrs;
	int _num_thrs;
	int _level;
	void _aquire_lock(SCC::dfid id);
	void _release_lock(SCC::dfid id);

public:
	// We need to know the maximum numbers of
	// threads that we can support
	tournament_lock(int capacity);
	
	/* Execute critical section wrapped by locks */
	void exec(SCC::dfid id, std::function<void (void)> routine);
	
	/* Add new data flow. Return the ID of the new data flow */
	SCC::dfid add_data_flow();

	~tournament_lock();
};
	
}

}

#endif

