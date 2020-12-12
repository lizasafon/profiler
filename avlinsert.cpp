#include<iostream>
#include<chrono>
#include<set>
#include<stdlib.h>
#include<ctime>
#include<fstream>
#include<cmath>
#include<random>
#include<vector>
#include"AVL_tree.h"

int random_generator(int min, int max)
{
	 std::random_device rd; 
    std::mt19937 mersenne(rd());
    int n = (min+mersenne()%(max-min)-1);
    return n;
}





double time_test(unsigned N){
	std::vector<int> arr;
	for(int i=0; i<N; i++){
		arr.push_back(random_generator(-N, N));
	}	
	AVL_BinSearchTree<int>  s;

	auto start = std::chrono::steady_clock::now();
	for(int i=0; i<N; i++){
		s.insert(arr[i]);// здесь будет одна из трех функций выше
	}
	auto end = std::chrono::steady_clock::now();


 
	std::chrono::duration<double> time = end - start;
	return time.count();
	
};

//set

double time_test_set(unsigned N){
	std::vector<int> arr;
	for(int i=0; i<N; i++){
		arr.push_back(random_generator(-N, N));
	}	
	std::set<int>  s;

	auto start = std::chrono::steady_clock::now();
	for(int i=0; i<N; i++){
		s.insert(arr[i]);// здесь будет одна из трех функций выше
	}
	auto end = std::chrono::steady_clock::now();


 
	std::chrono::duration<double> time = end - start;
	return time.count();
	
};

int main(){
	std::ofstream out;          // поток для записи
	out.open("file.txt"); // окрываем файл для записи
	if (out.is_open()){
		srand(time(NULL));
	        for(unsigned num=10; num<1000000; num=int(float(num)*1.2)){
			std::cout << num << std::endl;
	        	double time = time_test(num)/num;
			
			double expected_time = time_test_set(num)/num;
			out << num << '\t' << time << '\t' << expected_time << std::endl; //запись
			
		}
	}
	out.close();
	std::cout << "End of program" << std::endl;
	return 0;
	
	//std::cout << "N = " << num << '\t' << "elapsed time: " << time << 's' <<'\n';
	//std::cout << random_generator(-200, 200) << '\n';
	}

