#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define NULL_1 10000
const int ty = 320;
int d[320];
int page[320];
int p[32]; int que; int time[32];
void create(int leng)
{
	int i; que = 0;
	for (i = 0; i<leng; i++)
	{
		p[i] = NULL_1;
		time[i] = 0;
	}
}
void FIFO(int leng)
{
	int i, j, k;
	int n;
	create(leng); n = 0;
	for (i = 0; i<ty; i++)
	{
		k = 0;
		for (j = 0; j<leng; j++)
		{
			if (p[j] == NULL_1)
			break;
			else if (p[j] == page[i])
			{
				k = 1;
				break;
			}
		}
		if (k == 0)
		{
			que++; p[n] = page[i];
			n++;
		}
		if (n == leng)
			n = 0;
	}
	printf("%-7.3f\t", 1 - (float)que / ty);
}
void LRU(int leng)
{
	int i, j, k; int tmax, t;
	create(leng);
	for (i = 0; i<ty; i++)
	{
		k = 0;
		for (j = 0; j<leng; j++)
		{
			if (p[j] == NULL_1)
			break;
			else if (p[j] == page[i])
			{
				k = 1;
				t = j;
				break;
			}
		}
		if (k == 0)
		{
			que++;
			tmax = time[0];
			t = 0;
			for (j = 0; j<leng; j++)
			{
				if (tmax<time[j])
				{
					tmax = time[j];
					t = j;
				}
			}
			p[t] = page[i];

		}
		for (j = 0; j<leng; j++)
			time[j]++;
		time[t] = 0;
	}
	printf("%-7.3f\t", 1 - (float)que / ty);
}
void main()
{
	int m, i;
	srand(10 * getpid());
	m = (int)((float)(ty - 1)*(rand() / (RAND_MAX + 1.0)));
	for (i = 0; i<ty; i += 4)
	{
		d[i] = m;
		d[i + 1] = d[i] + 1;
		d[i + 2] = (int)((float)d[i] * (rand() / (RAND_MAX + 1.0)));
		d[i + 3] = d[i + 2] + 1;
		m = (int)((float)((ty - 1) - d[i + 2])*(rand() / (RAND_MAX + 1.0))) + d[i + 2];
	}
	for (i = 0; i<ty; i++)
		page[i] = d[i] / 10;
	printf("PAGE\t FIFO\t LRU\t\n");
	for (i = 4; i <= 32; i++)
	{
		printf("%2d\t", i);
		FIFO(i);
		LRU(i);
		printf("\n");

	}
}
