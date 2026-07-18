#include <stdio.h>

int main()
{
int numberSet[100];
int resultantSet[100];
int numOfElements;

printf("Enter the number of elements: ");
scanf("%d",&numOfElements);
printf("Enter the elements: ");
for(int i=0; i<numOfElements; i++)
{
scanf("%d",&numberSet[i]);
}

for(int i=0; i<numOfElements; i++)
{
    for(int j=i+1; j<numOfElements-1; j++)
    {
        if(numberSet[i] == numberSet[j])
        {
            for(int k=j; k<numOfElements; k++)
            {
                numberSet[k] = numberSet[k+1];
            }
            numOfElements--;
            j--;
        }
    }
}
printf("\nUpdated array with unique elements:\n");
for (int i = 0; i < numOfElements; i++) 
{
printf("%d ", numberSet[i]);
}
printf("\n");
return 0;
}