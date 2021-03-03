set -e
g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsGenCustom.cpp -o gen.out
g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeamsBrute.cpp -o brute.out
g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG MegaHardTeams.cpp -o code.out

./gen.out > $1
./brute.out < $1 > brute_ans.txt
./code.out < $1 > my_ans.txt

diff -Z brute_ans.txt my_ans.txt