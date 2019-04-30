#include <stdio.h>

#define MAX 10
#define TRUE 1
#define FALSE 0

typedef int bool;

int pageQueue[MAX];

bool isPageInMemory(int page, int SLOTS) {
    for (int i = 0; i < SLOTS; ++i) {
        if (pageQueue[i] == page)
            return TRUE;
    }
    return FALSE;
}

int main() {


	int SLOTS,n,i;
	printf("Enter number of frames: ");
	scanf("%d", &SLOTS);
	printf("\nEnter the number of pages: ");
	scanf("%d", &n);
	int pages[n];
	printf("\nEnter reference string: ");
	for(i=0;i<n;i++)
	{
		scanf("%d", &pages[i]);
	}
    int currentPos = 0;

    int pageFaults = 0;

    for (int i = 0; i < SLOTS; ++i) {
        pageQueue[i] = -1;
    }

    for (int j = 0; j < n; ++j) {
 

        if (!isPageInMemory(pages[j], SLOTS)) {
            pageQueue[currentPos] = pages[j];
            currentPos = (currentPos + 1)%SLOTS;
            pageFaults++;

            for (int i = 0; i < SLOTS; ++i) {
                printf(" %d", pageQueue[i]);
            }
			printf("\n");
        }
    }
    printf("Page faults: %d\n", pageFaults);

    return 0;
}
