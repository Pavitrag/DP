/* 
Consider the problem of neatly printing a paragraph with a monospaced font (all
characters having the same width) on a printer. The input text is a sequence of n
words of lengths L1, L2,...,Ln measured in characters. We want to print this paragraph
neatly on a number of lines that hold a maximum of M characters each. 
Our criterion of “neatness” is as follows. 
If a given line contains words i through j , where i <= j , and we leave exactly one space between words, the number of extra
space characters at the end of the line is M - j + i - SUMMATION{k = i to j}(Lk), which must be
nonnegative so that the words fit on the line. We wish to minimize the sum, over
all lines except the last, of the cubes of the numbers of extra space characters at the
ends of lines. Give a dynamic-programming algorithm to print a paragraph of n
words neatly on a printer. Analyze the running time and space requirements of
your algorithm.
*/

#include<iostream>
#include<climits>
#include<string.h>
#include<cstdlib>

using namespace std;

#define CUBE(x) (x)*(x)*(x)

int sumAllWordsLength(int wordlen[], int i, int j)
{
  int sum = 0;
	for(int k = i; k <= j; k++)
		sum += wordlen[k];

	return sum;
}

int *findMaxJ(int words[], int len, int M)
{
	int *Max = (int *)malloc(len*sizeof(int));
	for(int i=0; i< len; i++)
		Max[i] = -1;
	for(int i=0; i<len; i++)
		for(int j=0; j<len; j++)
			if(M >= (j - i + sumAllWordsLength(words, i, j)))
				Max[i] = j;
			else
				break;

	return Max;
}

/* n-element array of costs c,
 * where c[i] is the minimal cost of printing words i through n
**/

#define MAX_SIZE 100

int printNeatly(int *words, int len, int M, char **str)
{
	int minSum=0, retVal=0;
	int fromTo[100] = {0, };
	// lineCost[i] records the min cost of printing line from position i through n.
	int *lineCost = (int *)malloc(len*sizeof(int));
	for(int i=0; i< len; i++)
		lineCost[i] = INT_MAX;
	int *max = findMaxJ(words, len, M);

	for(int i=len-1; i>=0 ; i--)
	{
		if(max[i] == len-1){
			lineCost[i] = 0; //last line cost = 0
			fromTo[i] = len-1;
		}
		else
			for(int j = i; j <= max[i]; j++)
				if((minSum = CUBE(M - j + i - sumAllWordsLength(words, i, j)) + lineCost[j+1]) < lineCost[i])
				{
					lineCost[i] = minSum;
					fromTo[i] = j;
				}
	}
	//Printing the lines...seperate from Algo logic
	int j=0;
	int count = 1;
	for(int i=0; i<len; i=(fromTo[i]+1))
	{
		cout << "Line # "<< count++ << ": words from " << i << " to " << fromTo[i] << endl;
		for(int j = i; j <= fromTo[i]; j++)
			cout << str[j] << " ";
		cout << endl << "====================================" << endl;
	}
	free(max);
	max = NULL;

	retVal = lineCost[0];

	free(lineCost);
	lineCost = NULL;

	return retVal;
}

void printNeatlyDriver()
{
	//int wl[] = {2, 6, 4, 9, 12, 13, 14, 3, 1, 2, 1, 2, 1, 6};
	char *words[] = {"Geeks", "for", "Geeks", "presents", "word", "wrap", "problem"};
	int wl[] = {5, 3, 5, 8, 4, 4, 7};

	int minCost = printNeatly(wl, 7, 15, words);


	cout << "min sum = " << /*total*/minCost << endl;
}
