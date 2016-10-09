
/*
 * Implementation of Tournament-based algorithm for concurrent
 * control in multi-thread programming.
 * The implementation use POSIX's pthread_mutex_t objects as a
 * 2-process lock.
 * */

#include "locks/tournament.h"

using namespace std;
using namespace SCC;
using namespace SCC::LOCKS;

tournament_lock::tournament_lock() {
	// Do nothing
}

tournament_lock::tournament_lock(int capacity) {
	_locks = new pthread_mutex_t[capacity - 1];
	_num_thrs = capacity;
	_avai_thrs = 0;
	pthread_mutex_init(&_tid_lock, NULL);
}

tournament_lock::~tournament_lock() {
	for (int i = 0; i < _avai_thrs; ++i) {
		pthread_mutex_destroy(&_locks[i]);
	}
	delete [] _locks;
	pthread_mutex_destroy(&_tid_lock);
}

dfid tournament_lock::add_data_flow() {
	dfid id;
	pthread_mutex_lock(&_tid_lock);
	if (_avai_thrs == _num_thrs) {
		id = -1;
	}else{
		pthread_mutex_init(&_locks[_avai_thrs]);
		_avai_thrs++;
		id = _avai_thrs - 1;
	}
	pthread_mutex_unlock(&_tid_lock);
	return id;
}

void tournament_lock::exec(dfid id, function<void (void)> routine) {
	_acquire_lock(id);
	routine();
	_release_lock(id);
}

void tournament_lock::_acquire_lock(dfid id) {
	int node_id = id + _avai_thrs; // We begin with a fake id
	int level = 

}

void tnm_lock::_release_lock(dfid id) {
	
}



