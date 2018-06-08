#include<stdio.h>

int main()
{
      int burst_time[20], process[20], waiting_time[20], turnaround_time[20], priority[20];
      int i, j, limit, sum = 0, position, temp;
      float average_wait_time, average_turnaround_time;
      printf("Anzahl der Prozesse:\t");
      scanf("%d", &limit);
      printf("\nAbarbeitungszeit und Prioritäten der Prozesse\n", limit);
      for(i = 0; i < limit; i++)
      {
            printf("\nProzess[%d]\n", i + 1);
            printf("Abarbeitungszeit:\t");
            scanf("%d", &burst_time[i]);
            printf("Priorität:\t");
            scanf("%d", &priority[i]);
            process[i] = i + 1;
      }
      for(i = 0; i < limit; i++)
      {
            position = i;
            for(j = i + 1; j < limit; j++)
            {
                  if(priority[j] > priority[position])
                  {
                        position = j;
                  }
            }
            temp = priority[i];
            priority[i] = priority[position];
            priority[position] = temp;
            temp = burst_time[i];
            burst_time[i] = burst_time[position];
            burst_time[position] = temp;
            temp = process[i];
            process[i] = process[position];
            process[position] = temp;
      }
      waiting_time[0] = 0;
      for(i = 1; i < limit; i++)
      {
            waiting_time[i] = 0;
            for(j = 0; j < i; j++)
            {
                  waiting_time[i] = waiting_time[i] + burst_time[j];
            }
            sum = sum + waiting_time[i];
      }
      average_wait_time = sum / limit;
      sum = 0;
      printf("\nProzess ID\t\tAbarbeitungszeit\t Wartezeit\t Zeit insgesamt\n");
      for(i = 0; i < limit; i++)
      {
            turnaround_time[i] = burst_time[i] + waiting_time[i];
            sum = sum + turnaround_time[i];
            printf("\nProzess[%d]\t\t%d\t\t\t %d\t\t\ %d\n", process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
      }
      average_turnaround_time = sum / limit;
      printf("\nMittlere Verweilzeit\t%f", average_wait_time);
      printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);

      return 0;
}
