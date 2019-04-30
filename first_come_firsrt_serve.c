#include <stdio.h>
#include <stdlib.h>

void sort(int t[], int p)
{
	int i, j, temp;	
	for (i=0; i<p-1; i++)
		for (j=i+1; j<p; j++)
			if (t[i]>t[j])
			{
				temp=t[i];
				t[i]=t[j];
				t[j]=temp;
			}	
}

void ganttchart(int t[], int p)
{
	int i, j, k, stime[20];
	stime[0]=0;
	for (k=1; k<=p; k++)
		stime[k]=stime[k-1]+t[k-1];
	
	printf("\n");	
	for (i=0; i<p; i++)
		for (j=0; j<2*t[i]; j++)
			if (j==0)
				printf(" ");
			else
				printf("-");
	printf("\n");
	for (i=0; i<p; i++)
		for (j=0; j<2*t[i]; j++)
			if (j==0)
				printf("|");
			else if (j==t[i]-1)
			{
				printf("P%d", i+1);
				j++;
			}
			else
				printf(" ");
	printf("|\n");			
	for (i=0; i<p; i++)
		for (j=0; j<2*t[i]; j++)
			if (j==0)
				printf(" ");
			else
				printf("-");
	printf("\n");
	for (i=0; i<p; i++)
		for (j=0; j<2*t[i]; j++)
			if (j==0)
			{
				printf("%d", stime[i]);
				j++;
			}
			else
				printf(" ");
	printf("%d\n", stime[p]);
}

int main()
{
	int i, temp, p, t[20], wtime=0;
	printf("\nEnter the number of processes: ");
	scanf("%d", &p);
	printf("\nEnter the burst times: ");
	for (i=0; i<p; i++)
		scanf("%d", &t[i]);

	printf("\nFIRST COME FIRST SERVE");
	for (i=0; i<p-1; i++)
	{
		wtime=wtime+(wtime+t[i]);
	}
	wtime/=p;
	printf("\nAverage waiting time: %d", wtime);	
	ganttchart(t, p);
	
	wtime=0;
	printf("\nSHORTEST JOB FIRST");
	sort(t, p);
	for (i=0; i<p-1; i++)
	{
		wtime=wtime+(wtime+t[i]);
	}
	wtime/=p;
	printf("\nAverage waiting time: %d", wtime);
	ganttchart(t, p);
	
	
	return 0;
	
	
}
