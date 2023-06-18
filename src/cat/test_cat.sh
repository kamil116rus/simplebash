#!/bin/bash
SUCCESS_COUNT=0;
ERROR_COUNT=0;

declare -a FLAGS_PARAMS=(
  "-v"
  "-A"
  "-b"
  "-n"
  "-t"
  "-T"
  "-e"
  "-s"
  "-E"
  "--number-nonblank"
  "--number"
  "--squeeze-blank"
)

declare -a TEXT_FILES=(
  "../tests/1.txt"
  "../tests/2.txt"
  "../tests/3.txt"

)

for flags in ${FLAGS_PARAMS[@]}; do
  for files in ${TEXT_FILES[@]}; do
      cat $flags  $files > test_cat.log
      ./cat $flags  $files > test_my_cat.log

      echo "TEST FOR: $flags $files"
      if cmp -s test_my_cat.log test_cat.log ; then
        ((SUCCESS_COUNT++))
        
        echo "SUCCESS"
      else 
        ((ERROR_COUNT++))
        echo "FAILS"
      fi
      rm *.log
  done
done

echo "TOTAL SUCCESSES: $SUCCESS_COUNT"
echo "TOTAL FAILS: $ERROR_COUNT"
# echo "ALL: $COUNT"