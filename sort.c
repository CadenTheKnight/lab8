//heap sort implemented by by caden henderson

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void Swap(int* arr, int x, int y){
	int tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

void Heapify(int* arr, int n, int i){
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	int max = i;
	
	//if left child is larger than root
	//then set max to the left
	if(l < n && arr[l] > arr[max]){
		max = l;
	}

	if(r < n && arr[r] > arr[max]){
		max = r;
	}
 
	//if the root is not the largest
	//then swap the largest with i
	if(max != i){
		Swap(arr, i, max);

		//heapify the affected subtree
		Heapify(arr, n, max);
	}
}

void BuildMaxHeap(int* arr, int n){
	for(int i = n/2 - 1; i >= 0; i--){
		Heapify(arr, n, i);
	}
	
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int* arr, int n){
	BuildMaxHeap(arr, n);
	
	/*if(n!=0){
		Swap(arr, 0, n);
		Heapify(arr, 0);
		heapSort(arr, n--);
	}*/

	//heap sort?
	//swap root with lowest leaf?
	
	for(int i = n - 1; i >= 0; i--){
		Swap(arr, 0, i);

		//heapify root element 
		//to get highest element
		//at root again
		Heapify(arr, i, 0);
	}

}

//used for mergeSort
void merge(int* pData, int left, int mid, int right){

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	//mergeSort(pData, l, r);

}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}