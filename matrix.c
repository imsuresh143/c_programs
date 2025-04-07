#include<stdio.h>
int main()
{
    int a[10][10],r,c,i,j;
    printf("Enter the row");
    scanf("%d" ,&r);
    printf("enter the colomn");
    scanf("%d",&c);
    
    for(i=0;i<c;i++)
    {
        for(j=0;j<r;j++)
        {
            printf("Enter the value of element[%d][%d]",i,j);
            scanf("%d",&a[i][j]);

        }
    }
    for(i=0;i<c;i++)
    {
        for(j=0;j<r;j++)
        {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
     return 0; 
}
