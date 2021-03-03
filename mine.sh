# Execute as : bash mine.sh
# Eg. bash mine.sh
set -e
for feature in {1..2}
do
    # small files
    for file_num in {1..3}
    do
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGen.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname="feat${feature}_small_random${file_num}.txt"
        ./gen.out $feature $file_num 1000 100000 > $fname
        ./brute.out < $fname > brute_ans.txt
        ./code.out < $fname > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt > /dev/null || break
    done

    # large files
    for file_num in {1..3}
    do
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGen.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname="feat${feature}_large_random${file_num}.txt"
        ./gen.out $feature $file_num 1000000 1000000000 > $fname
        ./brute.out < $fname > brute_ans.txt
        ./code.out < $fname > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt > /dev/null || break
    done

    # custom files
    for file_num in {1..1}
    do
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGenCustom.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname="feat${feature}_large_custom${file_num}.txt"
        ./gen.out $feature $file_num 1000000 1000000000 > $fname
        ./brute.out < $fname > brute_ans.txt
        ./code.out < $fname > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt > /dev/null || break
    done
done


