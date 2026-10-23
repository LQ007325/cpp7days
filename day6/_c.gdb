set pagination off
set print pretty off
break student.cpp:103
run < _in.txt
echo \n--- size ---\n
print list.size()
echo \n--- score[0] ---\n
print list[0].score
echo \n--- id[0] ---\n
print list[0].id
echo \n--- name[0] ---\n
print list[0].name
echo \n--- name[0].c_str() ---\n
print list[0].name.c_str()
echo \n--- name[1].c_str() ---\n
print list[1].name.c_str()