#include<stdio.h>

int main()
{
    int i, limit, total = 0, x, counter = 0, time_quantum, counter2 = 0, o = 0;
    int wait_time = 0, turnaround_time = 0, burst_time[10], temp[10], temp2[10];
    float average_wait_time, average_turnaround_time;
    printf("\nAnzahl an Prozessen:\t");
    scanf("%d", &limit);
    x = limit;
    for(i = 0; i < limit; i++)
    {
        printf("\nProzess[%d]\n", i + 1);
        printf("Laufzeit\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];
    }

    time_quantum = burst_time[0];
    for(i = 1; i < limit; i++)
    {
        if (burst_time[i] < time_quantum)
        {
            time_quantum = burst_time[i];
        }
    }
    printf("\nEs wird an den Jobs zu folgenden Anteilen gearbeitet:\n");
    for(total = 0, i = 0; x != 0;)
    {
        if(temp[i] <= time_quantum && temp[i] > 0)
        {
            total = total + temp[i];
            printf("\nEs wurde %ds an %d gearbeitet.\n", temp[i], i+1);
            temp[i] = 0;
            counter = 1;
            counter2++;

        }
        else if(temp[i] > 0)
        {
            temp[i] = temp[i] - time_quantum;
            total = total + time_quantum;
            printf("\nEs wurde %ds an %d gearbeitet.\n", time_quantum, i+1);
            counter2++;
        }
        if(temp[i] == 0 && counter == 1)
        {
            x--;
            wait_time = wait_time + total - burst_time[i];
            turnaround_time = turnaround_time + total;
            counter = 0;
        }
        if(i == limit - 1)
        {
            i = 0;
            time_quantum = temp[0];
            for(int k = 1; k < limit; k++)
            {
                if (time_quantum > temp[k] && temp[k] != 0)
                {
                    time_quantum = temp[k];
                }

            }
            printf("\nEs wird an den Jobs zu folgenden Anteilen gearbeitet:\n");
        }
        else
        {
            i++;
        }

    }
    average_turnaround_time = turnaround_time * 1.0 / limit;
    printf("\nDurchschnittliche Verweilzeit\t%f\n", average_turnaround_time);
    return 0;
}
