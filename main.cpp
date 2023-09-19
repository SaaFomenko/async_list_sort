#include <iostream>
#include <future>
#include <list>


namespace my
{
	std::list<int>::iterator find_it_min(
		std::list<int>& l, 
		std::list<int>::iterator cur_it
	)
	{
		std::list<int>::iterator end_it = l.end();
		std::list<int>::iterator min_val_it = cur_it;
		for (std::list<int>::iterator it = cur_it; it != end_it; ++it)
		{
			if (*min_val_it > *it)
			{
				min_val_it = it;
			}
		}

		return min_val_it;
	}

	void sort(std::list<int>& l)
	{
		for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
		{
			std::list<int>::iterator min_val_it = find_it_min(l, it); 
			std::swap(*it, *min_val_it);
		}
	}

	void async_find_it_min(
		std::list<int>& l,
		std::list<int>::iterator cur_it,
		std::promise<std::list<int>::iterator> prom
	)
	{
		prom.set_value(find_it_min(l, cur_it));
	}

	void async_sort(std::list<int>& l)
	{
		//std::promise<std::list<int>::iterator> prom;
		//std::future<std::list<int>::iterator> ft_res = prom.get_future();

		for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
		{
			std::promise<std::list<int>::iterator> prom;
			std::future<std::list<int>::iterator> ft_res = prom.get_future();
			std::future<void> ft = std::async(async_find_it_min, std::ref(l), it, std::move(prom));
			//std::list<int>::iterator min_val_it = find_it_min(l, it); 
			std::swap(*it, *ft_res.get());
		}	
	}
}

int main()
{
	std::list<int> l1{7, 89, 3, 5, 67, 8, 1, 9, 23, 55};
	std::list<int> l2{7, 89, 3, 5, 67, 8, 1, 9, 23, 55};

	auto start = std::chrono::steady_clock::now();
	my::sort(l1);
	auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

	for (int el : l1)
	{
		std::cout << el << ' ';
	}
	std::cout << '\n';
	std::cout << "Time elapsed: " << elapsed_seconds.count() << "s\n\n";

	start = std::chrono::steady_clock::now();
	my::async_sort(l2);
	end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;

	for (int el : l2)
	{
		std::cout << el << ' ';
	}
	std::cout << '\n';
	std::cout << "Time elapsed: " << elapsed_seconds.count() << "s\n\n";

	return 0;
}
