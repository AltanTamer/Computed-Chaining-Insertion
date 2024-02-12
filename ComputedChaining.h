#include <vector>

using std::vector;


class entry {
	public:
		int data;
		int link;

		entry() {
			data = -1;
			link = -1;
		}
};
class ComputedChaining {
public:
	vector<entry> data_vec;

public:
	ComputedChaining(int);
    int hash(int);
    int hash2(int);
	void insert(int);
	int find_index(int);
	int find_num_probes(int) ;
	int first_of_my_chain(int key);
	bool isThisYourHome(int key);
	vector<int> find_chain(int key);
	};