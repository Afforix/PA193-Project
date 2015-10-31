#!/usr/bin/env bash

__RAINBOWPALETTE="1"
function __colortext()
{
  echo -e " \e[$__RAINBOWPALETTE;$2m$1\e[0m"
}

function pass()
{
  echo -n $(__colortext "PASS\t" "32")
  echo "$@"
}

function fail()
{
  echo -n $(__colortext "FAIL\t" "31")
  echo "$@"
}


for i in fail*.json ;
do
    ../parser "$i" &> /dev/null
    if [[ "$?" == 2 ]]
    then
        pass "$i"
    else
        fail "$i"
    fi
done

res="$(../parser pass.json | diff -y pass.ref -)"

if [[ -z "$res" ]]
then
    pass "pass.json"
else
    fail "pass.json      see ./pass.diff"
    echo "$res" > pass.diff
fi
