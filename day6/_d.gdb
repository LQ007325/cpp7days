set pagination off
set print pretty off
break student.cpp:103
run < _in.txt
echo \n--- A: score ---\n
print list._M_impl._M_finish - list._M_impl._M_start
echo \n--- B: score[0] ---\n
print list[0].score
echo \n--- C: score[1] ---\n
print list[1].score
echo \n--- D: name[0].c_str() ---\n
print list[0].name.c_str()