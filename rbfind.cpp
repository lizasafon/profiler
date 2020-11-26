#include<iostream>
#include<chrono>
#include<set>
#include<stdlib.h>
#include<ctime>
#include<fstream>
#include<cmath>
#include<random>
#include<vector>
#include"rbtree.cpp"

int random_generator(int min, int max)
{
	 std::random_device rd; 
    std::mt19937 mersenne(rd());
    int n = (min+mersenne()%(max-min)-1);
    return n;
}

void erase(RedBlackTree &s, int obj){
	s.erase(obj);
}
// set
void erase_set(std::set<int> &s, int obj){
	s.insert(obj);
}



//double expected(double n){
//	return pow(10, -6)*(log(n*10)/50+10);
//}



double time_test(unsigned N){
	std::vector<int> arr;
	RedBlackTree  s;

	for(int i=0; i<N; i++){
		arr.push_back(random_generator(-N, N));
		s.insert(arr[i]);
	}	
	
	auto start = std::chrono::steady_clock::now();
	for(int i=0; i<N; i++){
		erase(s, arr[i]);// здесь будет одна из трех функций выше
	}
	auto end = std::chrono::steady_clock::now();


 
	std::chrono::duration<double> time = end - start;
	return time.count();
	
};

//set

double time_test_set(unsigned N){
	std::vector<int> arr;
	std::set<int>  s;
	for(int i=0; i<N; i++){
		arr.push_back(random_generator(-N, N));
		s.insert(arr[i]);
	}	
	

	auto start = std::chrono::steady_clock::now();
	for(int i=0; i<N; i++){
		erase_set(s, arr[i]);// здесь будет одна из трех функций выше
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
			std::cout << num <<'\n';
	        	double time = time_test(num)/num;
			double expected_time = time_test_set(num)/num;
			out << num << '\t' << time << '\t' << expected_time << std::endl; //запись
			//out << num << '\t' << time << std::endl;
		}
	}
	out.close();
	std::cout << "End of program" << std::endl;
	return 0;
	
	//std::cout << "N = " << num << '\t' << "elapsed time: " << time << 's' <<'\n';
	//std::cout << random_generator(-200, 200) << '\n';
	}

