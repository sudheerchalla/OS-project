#include<stdio.h>
typedef struct{
    int process_id, arrival_time, burst_time, priority;
    int q, ready;
    int queue;
}process_structure;
void findWaitingTime(int processes[], int n,int bt[], int wt[], int quantum){
    int rem_bt[n],i;
    for ( i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
    int t = 0;
    while (1)
    {
        int done = 1;
        for ( i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0;
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
}
void findTurnAroundTime(int processes[], int n,int bt[], int wt[], int tat[]){
    int i;
    for (i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
void findavgTime(int processes[], int n, int bt[],int quantum){
    int wt[n], tat[n], total_wt = 0, total_tat = 0,i;
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);
    printf("Processes    Burst time  Waiting time    Turn around time\n");
    for (i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("  %d\t\t%d\t\t%d\t\t%d\n", i+1 ,bt[i] ,wt[i],tat[i]);
    }
    printf("Average waiting time = %f\nAverage turn around time =%f" ,(float)total_wt / (float)n,(float)total_tat / (float)n);
}
int Queue(int t1){
    if (t1 == 0 || t1 == 1 || t1 == 2 || t1 == 3){
        return 1;
    }
    else{
        return 2;
    }
}
void RoundRobin(process_structure process[],int processes[],int size){
    int BurstTime[size],pid[size];
    int quantum,i;
    printf("Enter time quantum:");
    scanf("%d",&quantum);
    for(i=0;i<size;i++){
        pid[i] = process[processes[i]].process_id;
        BurstTime[i] = process[processes[i]].burst_time;
    }
    findavgTime(pid,size,BurstTime,quantum);
}
int main(){
    int limit, count, temp_process, time, j, y;
    process_structure temp;
    printf("Enter Total Number of Processes:\t");
    scanf("%d", &limit);
    int RoundQueue[limit],RoundSize=0;
    int PriorityQueue[limit],PrioritySize=0;
    process_structure process[limit];
    for(count = 0; count < limit; count++){
        printf("\nProcess ID:\t");
        scanf("%d", &process[count].process_id);
        printf("Arrival Time:\t");
        scanf("%d", &process[count].arrival_time);
        printf("Burst Time:\t");
        scanf("%d", &process[count].burst_time);
        printf("Process Belongs to which Queue:\n1.Priority Queue\n2.Round Robin\n");
        scanf("%d",&process[count].queue);
        if(process[count].queue == 1){
            printf("Process Priority:\t");
            scanf("%d", &process[count].priority);
            temp_process = process[count].priority;
            process[count].q = Queue(temp_process);
            process[count].ready = 0;
            PriorityQueue[PrioritySize++] = count;
        }
        else{
            RoundQueue[RoundSize++] = count;
        }
    }
    time = process[PriorityQueue[0]].burst_time;
    for(y = 0; y < PrioritySize; y++){
        for(count = y; count < PrioritySize; count++){
            if(process[PriorityQueue[count]].arrival_time < time)   {
                process[PriorityQueue[count]].ready = 1;
            }
        }
        for(count = y; count < PrioritySize - 1; count++){
            for(j = count + 1; j < PrioritySize; j++){
                if(process[PriorityQueue[count]].ready == 1 && process[PriorityQueue[j]].ready == 1){
                    if(process[PriorityQueue[count]].q == 2 && process[PriorityQueue[j]].q == 1){
                        temp = process[PriorityQueue[count]];
                        process[PriorityQueue[count]] = process[PriorityQueue[j]];
                        process[PriorityQueue[j]] = temp;
                    }
                }
            }
        }
        for(count = y; count < PrioritySize - 1; count++){
            for(j = count + 1; j < PrioritySize; j++)
            {
                if(process[PriorityQueue[count]].ready == 1 && process[PriorityQueue[j]].ready == 1)
                {
                    if(process[PriorityQueue[count]].q == 1 && process[PriorityQueue[j]].q == 1)
                    {
                        if(process[PriorityQueue[count]].burst_time > process[PriorityQueue[j]].burst_time)
                        {
                            temp = process[PriorityQueue[count]];
                            process[PriorityQueue[count]] = process[PriorityQueue[j]];
                            process[PriorityQueue[j]] = temp;
                        }
                        else{
                            break;
                        }
                    }
                }
            }
        }
        printf("\nProcess[%d]:\tTime:\t%d To %d\n", process[PriorityQueue[y]].process_id, time, time + process[PriorityQueue[y]].burst_time);
        time = time + process[PriorityQueue[y]].burst_time;
        for(count = y; count < PrioritySize; count++){
            if(process[PriorityQueue[count]].ready == 1){
                process[PriorityQueue[count]].ready = 0;
            }
        }
    }
    RoundRobin(process,RoundQueue,RoundSize);
}
