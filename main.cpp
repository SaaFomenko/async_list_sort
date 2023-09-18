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



	void async_sort(std::list<int>& l)
	{

	}
}

int main()
{
	std::list<int> l{7, 89, 3, 5, 67, 8, 1, 9, 23, 55};

	my::sort(l);

	for (int el : l)
	{
		std::cout << el << '\n';
	}

	return 0;
}
