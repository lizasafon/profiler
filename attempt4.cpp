#include<iostream>
#include<chrono>
#include<set>
#include<stdlib.h>
#include<ctime>
#include<fstream>

float random_generator(int min, int max){
	float n = float(min+rand()%(max-min)-1);
	float k = float((rand()%1000))/1000;
	return n+k;
}


void insert(std::set<float> s, float obj){
	s.insert(obj);
}
void erase(std::set<float> s, float obj){
	s.erase(obj);
}
void find(std::set<float> s, float obj){
	auto it = s.find(obj);
} 




double time_test(unsigned N){
	float* arr = new float[N];
	for(int i=0; i<N; i++){
		arr[i] = random_generator(-N, N);
	}	
	std::set<float>  s;

	auto start = std::chrono::steady_clock::now();
	for(int i=0; i<N; i++){
		insert(s, arr[i]);// здесь будет одна из трех функций выше
	}
	auto end = std::chrono::steady_clock::now();

	delete[] arr;
	//delete[] s;
 
	std::chrono::duration<double> time = end - start;
	return time.count();
	
};

int main(){
	std::ofstream out;          // поток для записи
	out.open("file.txt"); // окрываем файл для записи
	if (out.is_open()){
		srand(time(NULL));
	        for(unsigned num=1; num<30; num++){
	        	double time = time_test(num);
			out << "N = " << num << '\t' << "elapsed time: " << time << 's'  << std::endl; //запись
		}
	}
	     
	std::cout << "End of program" << std::endl;
	return 0;
	
	//std::cout << "N = " << num << '\t' << "elapsed time: " << time << 's' <<'\n';
	//std::cout << random_generator(-200, 200) << '\n';
	}


