#include<map>
#include<vector>
#include<string>
#include<semaphore.h>

using namespace std;

class emails{
	private:
	map<string, vector<string> > emailMap;
	sem_t n;

	public:
		emails(){
			sem_init(&n,0,1);
		}

		void put(string name, string ans){
			sem_wait(&n);
			vector<string> v;
			map<string, vector<string> >::iterator it = emailMap.find(name);
			if(it != emailMap.end()){
				v = it->second;
				v.push_back(ans);
				it->second = v;
			}else{
				v.push_back(ans);
				emailMap[name] = v;
			}
			sem_post(&n);
		}

		vector<string> list(string name){
			sem_wait(&n);
			vector<string> v;
			map<string, vector<string> >::iterator it = emailMap.find(name);
			
			if(it != emailMap.end()){
				v = it->second;
			}
			sem_post(&n);
			return v;
		}

		vector<string> get(string name){
			sem_wait(&n);
			vector<string> v;
			map<string, vector<string> >::iterator it = emailMap.find(name);

			if(it != emailMap.end()){
				v = it->second;
			}
			sem_post(&n);
			return v;
		}

		void clear(){
			sem_wait(&n);
			emailMap.clear();
			sem_post(&n);
		}
};
