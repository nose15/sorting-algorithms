cd /home/lukasz/CLionProjects/aizo_1/out
../build/src/main --auto > out_raw.txt
grep "quick_sort" out_raw.txt > out_quick_sort.txt
grep "shell_sort" out_raw.txt > out_shell_sort.txt
grep "insertion_sort" out_raw.txt > out_insertion_sort.txt
grep "heap_sort" out_raw.txt > out_heap_sort.txt
