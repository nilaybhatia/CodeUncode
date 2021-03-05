# Execute as : bash mine.sh
# Eg. bash mine.sh
set -e
mkdir -p tests/feat1
mkdir -p tests/feat2

for feature in {1..2}
do
    # small random files, mostly useless coz contain 0 or 1 queries only
    for file_num in {1..1}
    do
        echo $feature $file_num
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGen.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname_in="tests/feat${feature}/feat${feature}_small_random${file_num}.in"
        fname_out="tests/feat${feature}/feat${feature}_small_random${file_num}.out"
        ./gen.out $feature $file_num 1000 100000 10 > $fname_in
        ./brute.out < $fname_in > brute_ans.txt
        ./code.out < $fname_in > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt
        cp brute_ans.txt $fname_out
    done

    # large random files
    for file_num in {1..2}
    do
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGen.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname_in="tests/feat${feature}/feat${feature}_large_random${file_num}.in"
        fname_out="tests/feat${feature}/feat${feature}_large_random${file_num}.out"
        ./gen.out $feature $file_num 1000000 1000000000 3 > $fname_in
        ./brute.out < $fname_in > brute_ans.txt
        ./code.out < $fname_in > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt
        cp brute_ans.txt $fname_out
    done

    # small custom files, use these instead of random
    for file_num in {1..2}
    do
        echo $feature $file_num
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGenCustom.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname_in="tests/feat${feature}/feat${feature}_small_custom${file_num}.in"
        fname_out="tests/feat${feature}/feat${feature}_small_custom${file_num}.out"
        ./gen.out $feature $file_num 1000 100000 10 > $fname_in
        ./brute.out < $fname_in > brute_ans.txt
        ./code.out < $fname_in > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt
        cp brute_ans.txt $fname_out
    done

    # large custom files
    for file_num in {1..2}
    do
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGenCustom.cpp -o gen.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
        g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

        fname_in="tests/feat${feature}/feat${feature}_large_custom${file_num}.in"
        fname_out="tests/feat${feature}/feat${feature}_large_custom${file_num}.out"
        ./gen.out $feature $file_num 1000000 1000000000 "$((3-$feature))" > $fname_in
        ./brute.out < $fname_in > brute_ans.txt
        ./code.out < $fname_in > my_ans.txt

        diff -Z brute_ans.txt my_ans.txt
        cp brute_ans.txt $fname_out
    done
done


