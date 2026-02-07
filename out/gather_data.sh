cd /home/lukasz/CLionProjects/aizo_1/out
../build/src/main --auto > out_raw.txt
grep "quick_sort" out_raw.txt > out_quick_sort.csv
grep "shell_sort" out_raw.txt > out_shell_sort.csv
grep "insertion_sort" out_raw.txt > out_insertion_sort.csv
grep "heap_sort" out_raw.txt > out_heap_sort.csv
