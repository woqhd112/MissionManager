#pragma once
#include <random>

class RandomProcess
{

public:

	RandomProcess()
	{

	}

	~RandomProcess()
	{
	
	}

	int Random(int nMinSeed, int nMaxSeed)
	{
		// random_device 를 통해 난수 생성 엔진을 초기화 한다.
		std::mt19937 gen(rd());

		// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
		std::uniform_int_distribution<int> dis(nMinSeed, nMaxSeed);

		return dis(gen);
	}

private:

	std::random_device rd;


};

