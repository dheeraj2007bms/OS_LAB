#include<stdio.h>

int main(){
    int n;
    printf("Priority Scheduling Algorithm (non-Preemptive)\n");
    printf("enter number of process:");
    scanf("%d",&n);
    int at[n],bt[n],ct[n],tat[n],wt[n],p[n],pri[n];
    int completed[n];
    for (int i=0;i<n;i++){
        printf("enter at of p %d\n",i+1);
        scanf("%d",&at[i]);
        printf("enter bt of p %d\n",i+1);
        scanf("%d",&bt[i]);
        printf("enter priority of p %d\n",i+1);
        scanf("%d",&pri[i]);

        p[i]=i+1;
        completed[i]=0;
    }

    int total=0,time=0;
    float avg_tat,avg_wt;
    int highp=99,idx;
    while (total<n){
            highp=999;
            idx=-1;
        for (int i=0;i<n;i++){
            if (at[i]<=time && p[i]<highp && completed[i]==0){
                highp=pri[i];
                idx=i;
            }
        }
        if (idx==-1){
            time=time+1;
            continue;
        }
        time=time+bt[idx];
        completed[idx]=1;
        ct[idx]=time;
        total=total+1;
    }

    for (int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        avg_tat=avg_tat+tat[i];
        avg_wt=avg_wt+wt[i];
    }
 printf("\nP\tAT\tBT\tPRI\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pri[i],ct[i],tat[i],wt[i]);
    }
    avg_wt=avg_wt/n;
    avg_tat=avg_tat/n;
    printf("the average wt:%f \n",avg_wt);
    printf("the average tat:%f \n",avg_tat);

}

