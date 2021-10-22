
#define TOTAL_WRITERS 3
#define TOTAL_READERS 5
#define REPEAT_COUNT 5
#define WRITER_WRITE_DELAY 2
#define READER_READ_DELAY 1
#define MAIN_THREAD_PAUSE 60

#include <thread>
#include <mutex>
#include <iostream>
#include <shared_mutex>

std::shared_timed_mutex		g_lock;
int							g_sharedResource = 0;

void writer()
{
	int count = 0;
	while (count < REPEAT_COUNT)
	{
		//Exclusive lock for writers
		{
			std::unique_lock<std::shared_timed_mutex> w(g_lock);

			std::cout << "[Writer:" << std::this_thread::get_id() << "]" << " enters section. SharedResource: " << g_sharedResource << std::endl;
			g_sharedResource++;
			std::cout << "[Writer:" << std::this_thread::get_id() << "]" << " exit section. SharedResource: " << g_sharedResource << std::endl;
		}

		count++;

		std::this_thread::sleep_for(std::chrono::seconds(WRITER_WRITE_DELAY));
	}
}

void reader()
{
	int count = 0;
	while (count < REPEAT_COUNT)
	{
		//Shared lock for readers
		{
			std::shared_lock<std::shared_timed_mutex> r(g_lock);

			std::cout << "[Reader:" << std::this_thread::get_id() << "]" << " enters section. SharedResource: " << g_sharedResource << std::endl;
		}

		count++;

		std::this_thread::sleep_for(std::chrono::seconds(READER_READ_DELAY));
	}
}




int main()
{
	//Run threads in background
	for (int i = 0; i < TOTAL_WRITERS; i++)
	{
		std::thread th = std::thread(writer);
		th.detach();
	}
	for (int i = 0; i < TOTAL_READERS; i++)
	{
		std::thread th = std::thread(reader);
		th.detach();
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(MAIN_THREAD_PAUSE));

	return 0;
}