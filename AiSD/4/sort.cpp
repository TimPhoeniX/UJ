#include <iostream>
#include <cstdlib>

int* CreateArray(int ArraySize)
{
    int* Array=new int[ArraySize];
    for(int i=0;i<ArraySize;++i)
    {
        std::cin >> Array[i];
    }
    return Array;
}

void PrintArray(int* Array, int ArraySize)
{
	for(int i = 0; i < ArraySize; ++i)
	{
		std::cout << Array[i] << " ";
	}
	std::cout << std::endl;
}

//If a goes before b, return true
bool Ascending(int a, int b)
{
	return a<b;
}

bool Descending(int a, int b)
{
	return a>b;
}

void SelectionSort(int* A, int size, bool(*compare)(int,int))
{
	int index = 0;
	for(int i = 0; i < size-1; ++i)
	{
		index = i;
		for(int j = i+1; j < size; ++j)
		{
			if(compare(A[j],A[index]))
			{
				index = j;
			}
		}
		std::swap(A[i],A[index]);
	}
}

void InsertionSort(int* A, int size, bool(*compare)(int,int))
{
	for(int j = 1; j < size; ++j)
	{
		int key=A[j];
		int i=j-1;
		while( i>=0 && compare(key,A[i]))
		{
			A[i+1]=A[i];
			--i;
		}
		A[i+1]=key;
	}
}

//I could name it MergeSort too. Polymorphism rocks!
void ArrayMerger(int* A,const int a,const int mid,const int b, bool(*compare)(int,int))
{
	if(a==b) return;
	int* Result = new int[(b-a+1)];
	int i = a, j = mid+1, k = 0;
	while( i <= mid && j <= b)
	{
		if(compare(A[i],A[j]))
		{
			Result[k++]=A[i++];
		}
		else
		{
			Result[k++]=A[j++];
		}
	}
	if(i <= mid)
	{
		while(i <= mid)
		{
			Result[k++]=A[i++];
		}
	}
	else
	{
		while(j <= b)
		{
			Result[k++]=A[j++];
		}
	}
	for(int l = 0; (a+l)<=b; ++l)
	{
		A[a+l]=Result[l];
	}
	delete[] Result;
}

void MergeSort(int* A, int a, int b, bool(*compare)(int,int))
{
	if(a<b)
	{
		int mid=(a+b)/2;
	//	std::cerr << "Mid" << std::endl;
		MergeSort(A,a,mid,compare);
	//	std::cerr << "a-mid" << std::endl;
		MergeSort(A,mid+1,b,compare);
	//	std::cerr << "mid+1-b" << std::endl;
		ArrayMerger(A,a,mid,b,compare);
	//	std::cerr << "Merged" << std::endl;
	}
}

//Interface for compatibility with sort function pointer
void MergeSort(int* A, int size, bool(*compare)(int,int))
{
	MergeSort(A,0,size-1,compare);
}

int main(int argc, char* argv[])
{
	bool (*Compare)(int,int) = nullptr;
	void (*Sort)(int*, int, bool (*)(int,int)) = nullptr;
	int SetNum = 0, SetSize = 0, *Set = nullptr;
	if(argc < 3)
	{
		std::cerr << "Not enough arguments\n";
		return -1;
	}
	switch(atoi(argv[1]))
	{
		case 1:
			Sort = SelectionSort;
			break;
		case 2:
			Sort = InsertionSort;
			break;
		case 3: 
			Sort = MergeSort;
			break;
		default:
			std::cerr << "First argument invalid\n";
			return -1;
	}
	switch(atoi(argv[2]))
	{
		case 0:
			Compare = Descending;
			break;
		case 1:
			Compare = Ascending;
			break;
		default:
			std::cerr << "Second argument invalid\n";
			return -1;
	}
	std::cin >> SetNum;
	for(int i = 0; i < SetNum; ++i)
	{
		std::cin >> SetSize;
	//	std::cerr << "ArraySizeRead" << std::endl;
		Set = CreateArray(SetSize);
	//	std::cerr << "ArrayCreated" << std::endl;
		Sort(Set,SetSize,Compare);
	//	std::cerr << "ArraySorted" << std::endl;
		PrintArray(Set,SetSize);
	//	std::cerr << "ArrayPrinted" << std::endl;
		delete[] Set;
	}
	return 0;
}