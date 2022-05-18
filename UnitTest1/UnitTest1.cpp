#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12.9/Lab_12.9.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Node* root = NULL;
			bool found = false;
			for (int i = 0; i < 10; i++)
			{
				found = false;
				BinarySearchInsert(root, i, found);
			}
			BalanceHeight(root);
			Assert::AreEqual(Height(root), 4);
		}
	};
}
