int main() {
    while (true) {
        // Get CPU usage (Platform-specific)
        // For Windows:
        // ... (Use Windows API functions like GetSystemTimes)
        // For Linux:
        FILE *file = fopen("/proc/loadavg", "r");
        if (file == NULL) {
            perror("Error opening /proc/loadavg");
            exit(1);
        }
        float load1, load5, load15;
        fscanf(file, "%f %f %f", &load1, &load5, &load15);
        fclose(file);

        // Get memory usage (Platform-specific)
        // For Windows:
        // ... (Use Windows API functions like GlobalMemoryStatusEx)
        // For Linux:
        FILE *memFile = fopen("/proc/meminfo", "r");
        if (memFile == NULL) {
            perror("Error opening /proc/meminfo");
            exit(1);
        }
        char line[128];
        while (fgets(line, sizeof(line), memFile)) {
            if (strstr(line, "MemTotal:") != NULL) {
                sscanf(line, "MemTotal: %ld kB", &total_memory);
            } else if (strstr(line, "MemAvailable:") != NULL) {
                sscanf(line, "MemAvailable: %ld kB", &available_memory);
            }
        }
        fclose(memFile);

        // Calculate and print usage
        float cpu_usage = load1 * 100;
        float mem_usage = (total_memory - available_memory) / (float)total_memory * 100;

        std::cout << "CPU Usage: " << cpu_usage << "%" << std::endl;
        std::cout << "Memory Usage: " << mem_usage << "%" << std::endl;

        // Adjust the sleep time as needed
        sleep(1); // Sleep for 1 second
    }

    return 0;
}
