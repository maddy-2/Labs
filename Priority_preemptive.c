#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void at_sort(int arr[][7], int n)
{
   int i, j,temp;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
		{
           if ((arr[j][1] > arr[j+1][1]))
			{
				temp=arr[j][0];
				arr[j][0]=arr[j+1][0];
				arr[j+1][0]=temp;
            	temp=arr[j][1];
				arr[j][1]=arr[j+1][1];
				arr[j+1][1]=temp;
				temp=arr[j][2];
				arr[j][2]=arr[j+1][2];
				arr[j+1][2]=temp;
				temp=arr[j][6];
				arr[j][6]=arr[j+1][6];
				arr[j+1][6]=temp;

			}
		}
}

void bt_sort(int arr[][7], int n)
{
   int i, j,temp;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
		{
           if ((arr[j][6] < arr[j+1][6]))
			{
				temp=arr[j][0];
				arr[j][0]=arr[j+1][0];
				arr[j+1][0]=temp;
            	temp=arr[j][1];
				arr[j][1]=arr[j+1][1];
				arr[j+1][1]=temp;
				temp=arr[j][2];
				arr[j][2]=arr[j+1][2];
				arr[j+1][2]=temp;
				temp=arr[j][6];
				arr[j][6]=arr[j+1][6];
				arr[j+1][6]=temp;
			}
		}
}

void sort(int arr[][7], int n)
{
   int i, j,temp;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
		{
           if ((arr[j][0] > arr[j+1][0]))
			{
				temp=arr[j][0];
				arr[j][0]=arr[j+1][0];
				arr[j+1][0]=temp;
            	temp=arr[j][1];
				arr[j][1]=arr[j+1][1];
				arr[j+1][1]=temp;
				temp=arr[j][2];
				arr[j][2]=arr[j+1][2];
				arr[j+1][2]=temp;
				temp=arr[j][3];
				arr[j][3]=arr[j+1][3];
				arr[j+1][3]=temp;
				temp=arr[j][4];
				arr[j][4]=arr[j+1][4];
				arr[j+1][4]=temp;
				temp=arr[j][5];
				arr[j][5]=arr[j+1][5];
				arr[j+1][5]=temp;
				temp=arr[j][6];
				arr[j][6]=arr[j+1][6];
				arr[j+1][6]=temp;
			}
		}
}


int main()
{
	int n;
	double avg_tat=0,avg_wt=0;
printf("Enter the number of processes: ");
scanf("%d",&n);
int pro[100][7]={100000},i,j,ideal,k,flag=0,count=0,count1=0,comp_time[101]={0},b_time[101]={0},op_time[101];

for(i=0;i<n;i++)
{
	scanf("%d %d %d %d",&pro[i][0],&pro[i][1],&pro[i][2],&pro[i][6]);
	b_time[pro[i][0]]=pro[i][2];
}
at_sort(pro,n);
j=0;
while(j!=pro[0][1])
	j++;
ideal=j;
bool id[101];
memset(id,true,101*sizeof(id[0]));
if(pro[0][1]!=0)
{
	printf("0->%d\t None\n",j);
}
pro[0][2]--;
comp_time[pro[0][0]]++;
printf("%d->%d\t%d\n",j,j+1,pro[0][0]);
j++;
if(pro[0][2]==0)
            comp_time[pro[i][0]]=j;
if(id[pro[0][0]])
{
    op_time[pro[0][0]]=j-1;
    id[pro[0][0]]=false;
}

i=0;
while(count<n)
{
    bt_sort(pro,n);
    i=0;
    while(i<n)
    {
        if(j>=pro[i][1]&&pro[i][2]!=0)
        {
            pro[i][2]--;
            printf("%d->%d\t%d\n",j,j+1,pro[i][0]);
            j++;
            if(pro[i][2]==0)
            {
                comp_time[pro[i][0]]=j;
                count++;
            }
            if(id[pro[i][0]])
            {
                op_time[pro[i][0]]=j-1;
                id[pro[i][0]]=false;
            }
            break;
        }
        i++;
    }
    at_sort(pro,n);

}
sort(pro,n);
for(i=0;i<n;i++)
{
    pro[i][2]=b_time[pro[i][0]];
	pro[i][3]=comp_time[pro[i][0]];
	pro[i][5]=pro[i][3]-pro[i][2]-pro[i][1];
	pro[i][4]=pro[i][5]+pro[i][2];

}
printf("Process Id\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurn Around Time\tWait Time\n");
for(i=0;i<n;i++)
	printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\n",pro[i][0],pro[i][1],pro[i][2],pro[i][6],pro[i][3],pro[i][4],pro[i][5]);
for(i=0;i<n;i++)
{
	avg_tat+=pro[i][4];
	avg_wt+=pro[i][5];
}
printf("Average wait time is: %f\n",avg_wt/n);
printf("Average turn around time is: %f",avg_tat/n);
}
