#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
class thread{
private:

	int index;
	long long nextStartTime;
public:
	thread(){};
	thread(int i, long long s) :index(i), nextStartTime(s){}
	void setNextStartTime(long long s){ nextStartTime = s; }

	int getIndex(){ return index; }
	long long getNextStartTime(){ return nextStartTime; }


};//0>4,1>4
bool operator<(thread a, thread b){
	if (a.getNextStartTime() != b.getNextStartTime())
		return a.getNextStartTime() < b.getNextStartTime();
	return a.getIndex() < b.getIndex();
}
class priorityQueue{
private:
	vector<thread> threadsQueue;
	void makeMinHeap(int i){
		static int size = threadsQueue.size();
		int  largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < size&&threadsQueue[l] < threadsQueue[largest])
			largest = l;
		if (r < size&&threadsQueue[r] < threadsQueue[largest])
			largest = r;
		if (largest != i){
			swap(threadsQueue[i], threadsQueue[largest]);
			makeMinHeap(largest);
		}
	}
	int parent(int i){ return floor(i / 2); }
	int leftChild(int i){ return 2 * i + 1; }
	int rightChild(int i){ return 2 * i + 2; }
	void shiftUp(int i){
		while (i>0 && threadsQueue[parent(i)] < threadsQueue[i]){
			swap(threadsQueue[parent(i)], threadsQueue[i]);
			i = parent(i);
		}
	}
	void shiftDown(int i){
		int maxIndx = i;
		int l = leftChild(i);
		if (l<threadsQueue.size() && threadsQueue[l] < threadsQueue[maxIndx])
			maxIndx = l;
		int r = rightChild(i);
		if (r<threadsQueue.size() && threadsQueue[r] < threadsQueue[maxIndx])
			maxIndx = r;
		if (i != maxIndx){
			swap(threadsQueue[i], threadsQueue[maxIndx]);
			shiftDown(maxIndx);
		}

	}


public:
	priorityQueue(vector<thread> &threads, int s){

		threads.resize(s);
		threadsQueue = threads;
		/*for (int i = threads.size() / 2 - 1; i >= 0; --i){
		makeMinHeap( i);
		}*/
	}
	void changePriority(int i, long long newFreeTime){
		long long oldTime = threadsQueue[i].getNextStartTime();
		threadsQueue[i].setNextStartTime(newFreeTime);
		shiftDown(i);
	}
	thread getMax(){
		return threadsQueue[0];
	}

};

class JobQueue {
private:
	int num_workers_;
	vector<int> jobs_;

	vector<int> assigned_workers_;
	vector<long long> start_times_;

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() {
		int m ; num_workers_ = 10;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	void AssignJobs() {
		
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		vector<long long> next_free_time(num_workers_, 0);

		//	std::priority_queue<thread>thrds;
		vector<thread>thrds;
		//priorityQueue thrds(ths);
		for (int j = 0; j < num_workers_; ++j) {
			thread t(j, 0);
			thrds.push_back(t);
		}
		priorityQueue threads(thrds, thrds.size());
		for (int i = 0; i < jobs_.size(); ++i) {
			int duration = jobs_[i];

			thread th = threads.getMax();

			//thrds.pop();
			int next_worker = th.getIndex();
			//th.setNextStartTime(long long(th.getNextStartTime() + duration));

			assigned_workers_[i] = next_worker;
			start_times_[i] = next_free_time[next_worker];
			next_free_time[next_worker] += duration;
			long long dr = next_free_time[next_worker];
			threads.changePriority(0, dr);
		}
		
	}

public:
	void Solve() {
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	system("pause");
	return 0;
}
