#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t id_val;

    id_val = fork();

    if (id_val < 0) {
        perror("Process creation failed");
        return 1;
    }

    // Mantik Ayni, Sira Degisikligi: Once Ebeveyn (Parent) blogunu yazdik
    if (id_val > 0) {
        // --- PARENT ---
        printf("[Parent] Running. My PID: %d, Created Child: %d\n", getpid(), id_val);
        
        // Parent bitiyor (Child hala calisirken)
        printf("[Parent] My work is done. Terminating execution now.\n");
    }
    else {
        // --- CHILD ---
        // Baslangicta normal ebeveyne sahip
        printf("[Child] Started. My PID: %d, Current Parent: %d\n", getpid(), getppid());

        printf("[Child] Pausing for 5 seconds to let parent finish...\n");
        sleep(5);

        // Uyandiginda parent ölmüş olmalı, isletim sistemi tarafindan evlat edinilmeli
        printf("[Child] Resumed. My PID: %d, New Parent (Adopter): %d\n", getpid(), getppid());
    }

    return 0;
}