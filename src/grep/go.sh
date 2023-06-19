
#!/bin/bash

parametr1=$1

parametr2=$2

script_name=$0 #присваиваем переменной script_name значение имени скрипта

echo "Вы запустили скрипт с именем $script_name и параметр $@"
clang-format -style=Google -i *.c *.h

git add . 
git commit -m"$parametr1 $2 $3 $4 $5 $6 $7"
git push origin main

#gcc -Wall -Werror -Wextra 