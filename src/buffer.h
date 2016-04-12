#include<queue>
#include<semaphore.h>

using namespace std;

class buffer{
	private:
		queue<int> buff;
		sem_t s, n;

	public:
		buffer(){
			sem_init(&s,0,1);
			sem_init(&n,0,0);
		}
	
		void append(int i){
			sem_wait(&s);
			buff.push(i);
			sem_post(&s);
			sem_post(&n);			
		}

		int take(){
			sem_wait(&n);
			sem_wait(&s);
			int i = buff.front();
			buff.pop();
			sem_post(&s);
			return i;
		}
};
