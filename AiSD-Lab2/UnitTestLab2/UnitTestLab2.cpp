#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab2
{
	TEST_CLASS(UnitTestLab2)
	{
	public:
		
		TEST_METHOD(Test_resultOfCoding)
		{
			const string test = "hello";
			const int length = test.length();
			AlgorithmHaffman check;
			check.Algorithm(test, length);
			string resultOfCoding = "000 001 00 00 01 ";
			Assert::IsTrue(resultOfCoding == check.resultOfCoding(test));
		}
		TEST_METHOD(Test_resultOfEncoding)
		{
			const string test = "hello";
			const int length = test.length();
			AlgorithmHaffman check;
			check.Algorithm(test, length);
			string resultOfCoding = "hello";
			Assert::IsTrue(resultOfCoding == check.resultOfDecoding(check.resultOfCoding(test)));
		}
		TEST_METHOD(Test_encodedSize)
		{
			const string test = "hello";
			const int length = test.length();
			AlgorithmHaffman check;
			check.Algorithm(test, length);
			string resultOfCoding = check.resultOfCoding(test);
			check.resultOfDecoding(check.resultOfCoding(test));
			Assert::IsTrue(check.encodedSize(resultOfCoding) == 12);
		}


	};
}
