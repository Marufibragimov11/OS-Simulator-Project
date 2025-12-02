#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int start;
    int finish;
    int waiting;
    int turnaround;
} Process;

void fcfs(Process p[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;
    float total_wait = 0, total_tat = 0;

    printf("\n--- FCFS Scheduling ---\n");
    printf("\nGantt chart (start-end):\n");

    for (i = 0; i < n; i++) {
        if (time < p[i].arrival) {
            time = p[i].arrival;
        }

        p[i].start = time;
        time += p[i].burst;
        p[i].finish = time;

        p[i].turnaround = p[i].finish - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        total_wait += p[i].waiting;
        total_tat += p[i].turnaround;

        printf("| P%d (%d-%d) ", p[i].id, p[i].start, p[i].finish);
    }
    printf("|\n");

    printf("\n%-5s %-8s %-8s %-8s %-10s %-10s\n",
           "PID", "Arr", "Burst", "Start", "Waiting", "Turnaround");

    for (i = 0; i < n; i++) {
        printf("%-5d %-8d %-8d %-8d %-10d %-10d\n",
               p[i].id, p[i].arrival, p[i].burst,
               p[i].start, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / n);
    printf("Average turnaround time = %.2f\n", total_tat / n);
}

void sjf(Process p[], int n) {
    int completed = 0;
    int time = 0;
    int done[MAX] = {0};
    float total_wait = 0, total_tat = 0;
    int i;

    printf("\n--- SJF (Non-preemptive) Scheduling ---\n");
    printf("\nGantt chart (start-end):\n");

    int min_arr = p[0].arrival;
    for (i = 1; i < n; i++) {
        if (p[i].arrival < min_arr) {
            min_arr = p[i].arrival;
        }
    }
    time = min_arr;

    while (completed < n) {
        int idx = -1;
        int min_burst = 1000000000;

        for (i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (p[i].burst < min_burst) {
                    min_burst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].start = time;
        time += p[idx].burst;
        p[idx].finish = time;

        p[idx].turnaround = p[idx].finish - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        total_wait += p[idx].waiting;
        total_tat += p[idx].turnaround;
        done[idx] = 1;
        completed++;

        printf("| P%d (%d-%d) ", p[idx].id, p[idx].start, p[idx].finish);
    }
    printf("|\n");

    printf("\n%-5s %-8s %-8s %-8s %-10s %-10s\n",
           "PID", "Arr", "Burst", "Start", "Waiting", "Turnaround");

    for (i = 0; i < n; i++) {
        printf("%-5d %-8d %-8d %-8d %-10d %-10d\n",
               p[i].id, p[i].arrival, p[i].burst,
               p[i].start, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / n);
    printf("Average turnaround time = %.2f\n", total_tat / n);
}

void priority_scheduling(Process p[], int n) {
    int completed = 0;
    int time = 0;
    int done[MAX] = {0};
    float total_wait = 0, total_tat = 0;
    int i;

    printf("\n--- Priority (Non-preemptive) Scheduling ---\n");
    printf("\nGantt chart (start-end):\n");

    int min_arr = p[0].arrival;
    for (i = 1; i < n; i++) {
        if (p[i].arrival < min_arr) {
            min_arr = p[i].arrival;
        }
    }
    time = min_arr;

    while (completed < n) {
        int idx = -1;
        int best_prio = 1000000000;

        for (i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (p[i].priority < best_prio) {
                    best_prio = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].start = time;
        time += p[idx].burst;
        p[idx].finish = time;

        p[idx].turnaround = p[idx].finish - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        total_wait += p[idx].waiting;
        total_tat += p[idx].turnaround;
        done[idx] = 1;
        completed++;

        printf("| P%d (%d-%d) ", p[idx].id, p[idx].start, p[idx].finish);
    }
    printf("|\n");

    printf("\n%-5s %-8s %-8s %-8s %-10s %-10s %-8s\n",
           "PID", "Arr", "Burst", "Start", "Waiting", "Turnaround", "Prio");

    for (i = 0; i < n; i++) {
        printf("%-5d %-8d %-8d %-8d %-10d %-10d %-8d\n",
               p[i].id, p[i].arrival, p[i].burst,
               p[i].start, p[i].waiting, p[i].turnaround, p[i].priority);
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / n);
    printf("Average turnaround time = %.2f\n", total_tat / n);
}

void round_robin(Process p[], int n, int quantum) {
    int i;
    int time = 0;
    int completed = 0;
    int queue[MAX];
    int in_queue[MAX] = {0};
    int front = 0, rear = 0;
    float total_wait = 0, total_tat = 0;

    printf("\n--- Round Robin Scheduling (q = %d) ---\n", quantum);
    printf("\nGantt chart (start-end):\n");

    int min_arr = p[0].arrival;
    for (i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].start = -1;
        p[i].finish = 0;
        if (p[i].arrival < min_arr) {
            min_arr = p[i].arrival;
        }
    }
    time = min_arr;

    for (i = 0; i < n; i++) {
        if (p[i].arrival <= time && !in_queue[i] && p[i].remaining > 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            int next_arr = -1;
            for (i = 0; i < n; i++) {
                if (p[i].remaining > 0) {
                    if (next_arr == -1 || p[i].arrival < next_arr) {
                        next_arr = p[i].arrival;
                    }
                }
            }
            if (next_arr == -1) break;
            if (time < next_arr) time = next_arr;

            for (i = 0; i < n; i++) {
                if (p[i].arrival <= time && !in_queue[i] && p[i].remaining > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        in_queue[idx] = 0;

        if (p[idx].start == -1) {
            p[idx].start = time;
        }

        int exec_time = quantum;
        if (p[idx].remaining < quantum) {
            exec_time = p[idx].remaining;
        }

        int start_time = time;
        time += exec_time;
        p[idx].remaining -= exec_time;

        printf("| P%d (%d-%d) ", p[idx].id, start_time, time);

        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && !in_queue[i] &&
                p[i].remaining > 0 && i != idx) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (p[idx].remaining > 0) {
            queue[rear++] = idx;
            in_queue[idx] = 1;
        } else {
            p[idx].finish = time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            total_wait += p[idx].waiting;
            total_tat += p[idx].turnaround;
            completed++;
        }
    }
    printf("|\n");

    printf("\n%-5s %-8s %-8s %-8s %-10s %-10s\n",
           "PID", "Arr", "Burst", "Start", "Waiting", "Turnaround");

    for (i = 0; i < n; i++) {
        printf("%-5d %-8d %-8d %-8d %-10d %-10d\n",
               p[i].id, p[i].arrival, p[i].burst,
               p[i].start, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / n);
    printf("Average turnaround time = %.2f\n", total_tat / n);
}

int main(void) {
    int n, i, choice, quantum;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess %d arrival time: ", i + 1);
        scanf("%d", &p[i].arrival);

        printf("Process %d burst time: ", i + 1);
        scanf("%d", &p[i].burst);

        printf("Process %d priority (1 = highest): ", i + 1);
        scanf("%d", &p[i].priority);

        p[i].remaining = p[i].burst;
        p[i].start = -1;
        p[i].finish = 0;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    printf("\nChoose scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF (Non-preemptive)\n");
    printf("3. Priority (Non-preemptive)\n");
    printf("4. Round Robin\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        fcfs(p, n);
    } else if (choice == 2) {
        sjf(p, n);
    } else if (choice == 3) {
        priority_scheduling(p, n);
    } else if (choice == 4) {
        printf("Enter time quantum: ");
        scanf("%d", &quantum);
        if (quantum <= 0) {
            printf("Invalid quantum.\n");
            return 0;
        }
        round_robin(p, n, quantum);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
