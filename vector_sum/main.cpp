#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>

void partial_sum(const std::vector<int>& vec, int index, long long& result) {
    result = 0;
    for(int i = index; i - index < vec.size()/2; ++i) {
        result+=vec[i];
    }
}

int main() {
    long long sum = 0;
    std::vector<int> rand(100000);
    std::srand(std::time(0));
    for(int& num: rand) {
        num = 1 + std::rand()%10; //мин 1 макс 10
    }
    clock_t start = clock();
    for(int& num: rand) {
        sum+=num;
    }
    clock_t end = clock();
    double dur = double(end-start)/CLOCKS_PER_SEC;
    std::cout << "sum 1: " << sum << "\nwith 1 thread used " << dur << " seconds\n";

    long long res1 = 0, res2 = 0, sum2 = 0;
    int index1 = 0;
    int index2 = 50000;
    clock_t start1 = clock();
    std::thread t1(partial_sum, rand, index1, std::ref(res1));
    std::thread t2(partial_sum, rand, index2, std::ref(res2));
    //std::cout<<"\n\n\n\n\nM"<<res1<<"\nM"<<res2<<"\n";
    t1.join();
    t2.join();
    sum2 = res1 + res2;
    clock_t end1 = clock();
    double dur1 = double(end1-start1)/CLOCKS_PER_SEC;
    std::cout << "sum 2: " << sum2 << "\nwith 2 threads used " << dur1 << " seconds\n";


    return 0;
}
