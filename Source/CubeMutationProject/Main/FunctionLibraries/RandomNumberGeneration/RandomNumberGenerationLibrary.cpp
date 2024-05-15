// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomNumberGenerationLibrary.h"

const unsigned int URandomNumberGenerationLibrary::RandomNumber(int positionX, unsigned int seed)
{
	constexpr unsigned int SQ5_BIT_NOISE1 = 0xd2a80a3f;	// 11010010101010000000101000111111
	constexpr unsigned int SQ5_BIT_NOISE2 = 0xa884f197;	// 10101000100001001111000110010111
	constexpr unsigned int SQ5_BIT_NOISE3 = 0x6C736F4B; // 01101100011100110110111101001011
	constexpr unsigned int SQ5_BIT_NOISE4 = 0xB79F3ABB;	// 10110111100111110011101010111011
	constexpr unsigned int SQ5_BIT_NOISE5 = 0x1b56c4f5;	// 00011011010101101100010011110101

	unsigned int mangledBits = (unsigned int)positionX;
	mangledBits *= SQ5_BIT_NOISE1;
	mangledBits += seed;
	mangledBits ^= (mangledBits >> 9);
	mangledBits += SQ5_BIT_NOISE2;
	mangledBits ^= (mangledBits >> 11);
	mangledBits *= SQ5_BIT_NOISE3;
	mangledBits ^= (mangledBits >> 13);
	mangledBits += SQ5_BIT_NOISE4;
	mangledBits ^= (mangledBits >> 15);
	mangledBits *= SQ5_BIT_NOISE5;
	mangledBits ^= (mangledBits >> 17);
	
	return mangledBits;
}

const int URandomNumberGenerationLibrary::RandomNumberInRange(int min, int max, int positionX, unsigned int seed)
{	
	int range = max - min + 1;
	int randomNumberVar = RandomNumber(positionX, seed) % range;

	return randomNumberVar + min;
}

const float URandomNumberGenerationLibrary::RandomFloat(int positionX, unsigned int seed)
{
	constexpr unsigned int SQ5_BIT_NOISE1 = 0xd2a80a3f;    // 11010010101010000000101000111111
	constexpr unsigned int SQ5_BIT_NOISE2 = 0xa884f197;    // 10101000100001001111000110010111
	constexpr unsigned int SQ5_BIT_NOISE3 = 0x6C736F4B;   // 01101100011100110110111101001011
	constexpr unsigned int SQ5_BIT_NOISE4 = 0xB79F3ABB;   // 10110111100111110011101010111011
	constexpr unsigned int SQ5_BIT_NOISE5 = 0x1b56c4f5;   // 00011011010101101100010011110101

	unsigned int mangledBits = (unsigned int)positionX;
	mangledBits *= SQ5_BIT_NOISE1;
	mangledBits += seed;
	mangledBits ^= (mangledBits >> 9);
	mangledBits += SQ5_BIT_NOISE2;
	mangledBits ^= (mangledBits >> 11);
	mangledBits *= SQ5_BIT_NOISE3;
	mangledBits ^= (mangledBits >> 13);
	mangledBits += SQ5_BIT_NOISE4;
	mangledBits ^= (mangledBits >> 15);
	mangledBits *= SQ5_BIT_NOISE5;
	mangledBits ^= (mangledBits >> 17);
    
	// Map the integer range [0, UINT_MAX] to the floating-point range [0, 1]
	float result = static_cast<float>(mangledBits) / static_cast<float>(std::numeric_limits<unsigned int>::max());
    
	return result;
}


const float URandomNumberGenerationLibrary::RandomFloatInRange(float min, float max, int positionX, unsigned int seed)
{
	float range = max - min;
	float randomNumberVar = RandomFloat(positionX, seed);
    
	return (randomNumberVar * range) + min;
}