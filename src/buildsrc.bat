g++ -std=c++17 -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og modules/*.cpp main.cpp -o mizi

echo "Generated Mizi.exe"

mizi.exe -t
echo "Ran Tests Successfully"

