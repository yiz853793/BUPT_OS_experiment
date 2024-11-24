./exp1_endless.exe > a.txt & # execute endless in background

sleep 2

ps

echo ""
pstree -h

echo ""
vmstat

echo ""
strace ./exp1.exe

echo ""
ltrace -p $(pidof exp1_endless.exe)

sleep 2 &

jobs

endlessPid=$(pidof exp1_endless.exe)

kill $endlessPid

sleep 1

jobs