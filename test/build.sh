mkdir -p bin

g++ -std=gnu++17 hl/field_any_cast.cpp ../src/hl/message.cpp -o field_any_cast
