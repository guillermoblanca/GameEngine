#include "gbpch.h"
#include <numeric>
#include "Probabilities.h"

int GB::Probabilities::GetIndexFromRandomRoulette(const std::vector<float>& probabilities)
{
	float previousProb = 0;
	float totalSum = 0;
	int probLenght = probabilities.size();
	
	std::vector<float> probs(probLenght);

	for (size_t i = 0; i < probLenght; i++)
	{
		totalSum += probabilities[i];
	}
	probs[0] = probabilities[0]/totalSum;

	for (size_t i = 1; i < probLenght; i++)
	{
		previousProb = probs[i-1];
		probs[i] = previousProb + probabilities[i]/ totalSum;
	}

	float randNumber = (std::rand() % 100 )/100.0f;

	int resultIndex =0;
	previousProb = -1;
	for (int i = 1; i < probs.size(); i++)
	{
		if (randNumber < probs[i] && randNumber  > probs[i-1])
		{
			resultIndex = i;
		}

	}

	return resultIndex;
}
