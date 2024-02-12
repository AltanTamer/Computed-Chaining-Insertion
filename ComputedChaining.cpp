#include "ComputedChaining.h"
using namespace std;

ComputedChaining::ComputedChaining(int table_size) {
    for (int i = 0; i < table_size; ++i) {
        data_vec.push_back(entry());
    }
}

int ComputedChaining::hash(int key) {
    return key % data_vec.size();
}

int ComputedChaining::hash2(int key) {
    int step = (key / data_vec.size()) % data_vec.size();
    if (step = data_vec.size()) step = 1;   
    if (step == 0) step = 1;
    return step;
}

bool ComputedChaining::isThisYourHome(int key) {
    return hash(key) == find_index(key);
}

void ComputedChaining::insert(int key) {
    int index = hash(key);
    int l = 0;

    if (data_vec[index].data != -1) { // collision
        if (isThisYourHome(data_vec[index].data)) { 
            int originalIndex = index;
            
            if(data_vec[index].link !=-1){

                while(data_vec[index].link != -1){

                    index = (index + hash2(data_vec[originalIndex].data)*(data_vec[index].link))% data_vec.size() ;
                    
                }
                originalIndex=index;
                while(data_vec[index].data !=-1){
                    index = (index + hash2(data_vec[originalIndex].data))% data_vec.size() ;
                    l++;                    
                }
                data_vec[originalIndex].link = l;
                data_vec[index].data = key;
                data_vec[index].link = -1;            
            }


            else{
                 while (data_vec[index].data != -1) {
                index = (index + hash2(data_vec[originalIndex].data))% data_vec.size() ;
                l++;
            }
            data_vec[originalIndex].link = l;
            data_vec[index].data = key;
            data_vec[index].link = -1;

            }

            /******************************orjinal yerinde değilse************************************************/
        } else {
            int originalIndex = index;
            int swapKey;

            swapKey = data_vec[originalIndex].data;
            

            vector<int> chain = find_chain(swapKey);

            int movedKeyIndex = -1;
            for (int i = 0; i < chain.size(); ++i) {
                if (data_vec[chain[i]].data == swapKey) {
                    movedKeyIndex = i;
                    break;
                }
            }

            int preidx = chain[movedKeyIndex - 1];

            vector<int> remainKey;
            for (int i = movedKeyIndex + 1; i < chain.size(); ++i) {
                remainKey.push_back(data_vec[chain[i]].data);
            }

            data_vec[preidx].link = -1;
            data_vec[originalIndex].data = -1;
            for (int i : remainKey) {
                int idx = find_index(i);
                data_vec[idx].data = -1;
            }
            data_vec[originalIndex].data = key;
            data_vec[originalIndex].link = -1;

            for (int i : remainKey) {
                insert(i);
            }

            insert(swapKey);
        }
    } else { // direct insertion
        data_vec[index].data = key;
        data_vec[index].link = -1;
    }
}


int ComputedChaining::find_index(int key) {
    int idx = hash(key);
    int inc = hash2(key);

    if (data_vec[idx].data == key)
        return idx;
    else {
        while (data_vec[idx].data != -1) {
            if (data_vec[idx].data != key) {
                inc = hash2(data_vec[idx].data);
                idx = (idx + data_vec[idx].link * inc) % data_vec.size();
            } else
                return idx;
        }
    }
    return -1;
}

int ComputedChaining::find_num_probes(int key) {
    vector<int> chain = find_chain(key);
    int numProbes =1;
    for (int i = 0; i < chain.size(); ++i) {
        if (data_vec[chain[i]].data == key) {
            numProbes =i+1;
            break;
        }
    }
    return numProbes;

}

vector<int> ComputedChaining::find_chain(int key) {
    vector<int> chain;
    int index = hash(key);
    int inc;

    while (data_vec[index].data != -1) {
        chain.push_back(index);
        if (data_vec[index].link != -1) {
            inc = hash2(data_vec[index].data);
            index = (index + data_vec[index].link * inc) % data_vec.size();
        } else
            break;
    }
    return chain;
}

int ComputedChaining::first_of_my_chain(int key) {
    return data_vec[hash(key)].data;
}
